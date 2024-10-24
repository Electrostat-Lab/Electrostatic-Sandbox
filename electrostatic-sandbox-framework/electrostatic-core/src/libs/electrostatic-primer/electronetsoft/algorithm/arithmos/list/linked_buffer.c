#include <electrostatic/electronetsoft/util/errno/errno.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/list/linked_buffer.h>
#include <stdlib.h>
#include <string.h>

static inline uint8_t linked_buffer_add(list *buffer, list_element *element) {
    if (buffer == NULL || element == NULL) {
        init_errno(&buffer->error);
        buffer->error.value = EUNDEFINEDBUFFER;
        return 0;
    }
    
    // type-safety checks
    if (buffer->type != LINKED_NODES) {
        init_errno(&buffer->error);
        buffer->error.value = EINCOMPATTYPE;
        return 0;
    }
    
    if (buffer->limit != 0 && buffer->length >= buffer->limit) {
        // resize
    }
    
    // assign the next node for single and double ended linked buffers
    list_element *chain = buffer->elements[0]->data;
    linked_node *head = chain->data;
    head->next = element;
    
    // assign the previous node
    if (head->type == DOUBLE_ENDED) {
        linked_node *next = element->data;
        next->previous = chain;
    }
    
    // increment the length counter
    buffer->length += 1;
    return 1;
}

uint8_t init_linked_buffer(list *list, list_element **elements, list_function_table *table) {
    if (list == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    table->iterator = NULL; // tested!
    table->add = &linked_buffer_add; // tested!
    table->add_all = NULL; // tested!
    table->remove_by_element = NULL;
    table->remove_by_index = NULL;
    table->remove_all = NULL;
    table->retains_all = NULL;
    table->contains = NULL;
    table->contains_all = NULL;
    table->resize = NULL;
    table->get = NULL;
    table->indexof = NULL;
    table->get_start_address = NULL;
    table->get_end_address = NULL;
    
    list->function_table = table;
    list->elements = elements;
    memset(list->elements, 0, list->length);
    
    list->length = 0;
    list->limit = 8 << 2;
    list->error = (errno) {
        .value = 0
    };
  
    list->elements_memory = (memory_partition) {
        .start_address = &(list->elements[0]),
        .end_address = 0 // this is dynamic and it needs to be updated on each WRITE operation!
    };
    
    return 0;
}