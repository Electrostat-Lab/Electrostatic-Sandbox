#include <electrostatic/util/errno/errno.h>
#include <electrostatic/algorithm/arithmos/adt/queue.h>
#include <electrostatic/algorithm/arithmos/queue/linked_queue.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline queue *linked_queue_alloc(size_t size) {
    queue *queue = malloc(size);
    memset(queue, 0, size);
    return queue;
}

static inline queue *linked_queue_alloc_init(size_t size, queue_element **elements) {
    queue *queue = linked_queue_alloc(size);
    queue->elements = elements; // shallow copy
    return queue;
}

static inline uint8_t linked_queue_deallocate(queue *queue) {
    if (queue != NULL) {
        // ensure to clean members first
        if (queue->function_table->is_malloc) {
            free(queue->function_table);
            // nullify the pointer variable to prevent memory access violations
            queue->function_table = NULL;
        }
        // clean the parent resources
        free(queue);
        // nullify the pointer variable to prevent memory access violations
        queue = NULL;
        return 0;
    }
    return 1;
}

static inline uint8_t unsafe_add_on_tail(queue *queue, queue_element *element) {
    // note: this is the common routine
    // add next element to the queue using node-providers
    // add the next element on the tail element
    queue_element *tail = queue->elements[1];

    // delegates the tree to a node provider
    node_provider *tail_node = (node_provider *)tail->element;
    node_provider *node = (node_provider *)element->element;

    if (tail_node->type == SINGLE_ENDED) {
        tail_node->next = element;
    } else if (tail_node->type == DOUBLE_ENDED) {
        tail_node->next = element;
        node->previous = tail;
    } else if (tail_node->type == CLUSTER) {
        // TODO-Later
    }

    // update the tail element to track the adding position for
    // a constant clock-complexity
    queue->elements[1] = element;
    // udpate the queue members
    queue->count += 1;

    return 0;
}

static inline queue_element *unsafe_remove_head_element(queue *linked_queue) {
    // retrieve the head
    queue_element *head = linked_queue->elements[0];
    // sanity-check on the head element
    uint8_t ret = is_linked_queue_element(linked_queue, head);
    if (ret != 0) {
        init_queue_errno(linked_queue); // initialize the errno struct if not initialized
        linked_queue->error.value = EINCOMPATTYPE;
        return NULL;
    }
    node_provider *head_node = ((node_provider *)head->element);
    // update the head element in the linked queue with the next element
    linked_queue->elements[0] = head_node->next;
    // update the head-next interactions according to the linked_queue type
    if (head_node->type == DOUBLE_ENDED) {
        ((node_provider *)linked_queue->elements[0]->element)->previous = NULL;
    } else if (head_node->type == CLUSTER) {
        // TODO-later
    }
    // release the old-head links
    head_node->next = NULL;
    return head;
}

static inline uint8_t linked_queue_add(queue *linked_queue, queue_element *element) {
    if (linked_queue == NULL || element == NULL) {
        return 1;
    }

    // sanity-protection against non-linked elements
    // terminate if the size doesn't match
    // otherwise proceed in the linked-node deterministic routine
    uint8_t ret = is_linked_queue_element(linked_queue, element);
    if (ret != 0) {
        return 1;
    }

    // ignore the count and the limit predicate function
    // use the offer(...) for this feature

    queue_element **elements = linked_queue->elements;

    // initialize the head of the linked list
    // for the first time only!
    if (elements[0] == NULL) {
        elements[0] = elements[1] = element;
        return 0;
    }

    return unsafe_add_on_tail(linked_queue, element);
}

static inline uint8_t linked_queue_offer(queue *linked_queue, queue_element *element) {
    if (linked_queue == NULL || element == NULL) {
        return 1;
    }

    // sanity-protection against non-linked elements
    // terminate if the size doesn't match
    // otherwise proceed in the linked-node deterministic routine
    uint8_t ret = is_linked_queue_element(linked_queue, element);
    if (ret != 0) {
        init_queue_errno(linked_queue);
        linked_queue->error.value = EINCOMPATTYPE;
        return 1;
    }

    // sanity-check for limits and counts
    // terminate if the count is or exceeds the limit value
    // with an error value indicating the cause
    if (linked_queue->count >= linked_queue->limit) {
        init_queue_errno(linked_queue);
        linked_queue->error.value = EFULLBUFFER;
        return 1;
    }

    queue_element **elements = linked_queue->elements;

    // initialize the head of the linked list
    // for the first time only!
    if (elements[0] == NULL) {
        elements[0] = elements[1] = element;
        return 0;
    }

    return unsafe_add_on_tail(linked_queue, element);
}

static inline queue_element *linked_queue_peek(queue *queue) {
    if (queue == NULL) {
        return NULL;
    }
    return queue->elements[0];
}

static inline queue_element *linked_queue_element(queue *queue) {
    queue_element *element = linked_queue_peek(queue);
    if (element == NULL) {
        init_queue_errno(queue); // initialize the errno struct if not initialized
        queue->error.value = EEMPTYBUFFER;
    }
    return element;
}
 
static inline queue_element *linked_queue_poll(queue *linked_queue) {
    if (linked_queue == NULL) {
        return NULL;
    }
    if (linked_queue->elements[0] == NULL) {
        return NULL;
    }

    return unsafe_remove_head_element(linked_queue);
}

static inline queue_element *linked_queue_remove(queue *linked_queue) {
    if (linked_queue == NULL) {
        return NULL;
    }
    // sanity-check the linked list
    if (linked_queue->elements[0] == NULL) {
        init_queue_errno(linked_queue); // initialize the errno struct if not initialized
        linked_queue->error.value = EEMPTYBUFFER;
        return NULL;
    } 
    return unsafe_remove_head_element(linked_queue);
}


uint8_t init_linked_queue(queue *linked_queue) {
    if (linked_queue == NULL) {
        return 1;
    }
    linked_queue->function_table = calloc(1, sizeof(queue_function_table));
    linked_queue->function_table->is_malloc = 0xFF; // assign is-malloc flag
    // designate the function table
    linked_queue->function_table->alloc = &linked_queue_alloc;
    linked_queue->function_table->alloc_init = &linked_queue_alloc_init;
    linked_queue->function_table->deallocate = &linked_queue_deallocate;
    linked_queue->function_table->add = &linked_queue_add;
    linked_queue->function_table->remove = &linked_queue_remove;
    
    linked_queue->function_table->element = &linked_queue_element;
    linked_queue->function_table->poll = &linked_queue_poll;
    linked_queue->function_table->peek = &linked_queue_peek;
    
    return 0;
}

uint8_t init_linked_queue_function_table(queue *linked_queue, queue_function_table *function_table) {
    if (linked_queue == NULL || function_table == NULL) {
        return 1;
    }
    function_table->alloc = &linked_queue_alloc;
    function_table->alloc_init = &linked_queue_alloc_init;
    function_table->deallocate = &linked_queue_deallocate;

    linked_queue->function_table = function_table;
    return 0;
}

uint8_t init_linked_queue_element(queue_element *element, node_provider *node) {
    if (element == NULL || node == NULL) {
        return 1;
    }

    // initialize the queue element with the node provider
    // and the size
    // Since, the element is a generic pointer
    // then, no other ways to test whether it is a linked_queue
    // other implementations may provide a unique hash key for implementations of queues
    element->element = node;
    element->size = sizeof(node_provider);

    return 0;
}

queue_element *allocate_node_provider_queue_element() {
    queue_element *element = (queue_element *)calloc(1, sizeof(queue_element));
    node_provider *node = calloc(1, sizeof(node_provider));
    init_linked_queue_element(element, node);
    return element;
}

uint8_t deallocate_node_provider_queue_element(queue_element *element) {
    if (element == NULL) {
        return 1;
    }

    if (element->element != NULL) {
        free(element->element);
        element->element = NULL;
    }

    free(element);
    element = NULL;

    return 0;
}

uint8_t is_linked_queue_element(queue *queue, queue_element *element) {
    // sanity-protection against non-linked elements
    // terminate if the size doesn't match
    // otherwise proceed in the linked-node deterministic routine
    if (element->size != sizeof(node_provider)) {
        init_queue_errno(queue);
        queue->error.value = EINCOMPATTYPE;
        return 1;
    }
    return 0;
}