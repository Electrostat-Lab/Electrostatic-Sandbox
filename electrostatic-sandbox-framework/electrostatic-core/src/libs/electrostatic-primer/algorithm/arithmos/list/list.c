#include <electrostatic/algorithm/arithmos/adt/list.h>
#include <electrostatic/algorithm/arithmos/list/contiguous_buffer.h>

uint8_t init_list_function_table(list *list, list_element **elements, list_function_table *table) {
    if (list == NULL || elements == NULL || table == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    if (list->type == CONTIGUOUS_BUFFER) {
        init_contiguous_buffer(list, elements, table);
        return 0;
    } else if (list->type == LINKED_NODES) {
        // NOT IMPLEMENTED YET!
        return 0;
    }
    
    return 0;
}

