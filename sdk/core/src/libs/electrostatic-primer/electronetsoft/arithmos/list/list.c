#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/arithmos/list/contiguous_buffer.h>
#include <electronetsoft/arithmos/list/linked_buffer.h>

status_code init_list_function_table(list *list, list_element **elements, list_function_table *table,
                                        api_lifecycle *lifecycle) {
    if (rvalue(list) == NULL || rvalue(elements) == NULL
                || rvalue(table) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    if (list->type == CONTIGUOUS_BUFFER) {
        return init_contiguous_buffer(list, elements, table, lifecycle);
    } else if (list->type == LINKED_BUFFER) {
        // NOT IMPLEMENTED YET!
        return init_linked_buffer(list, elements, table, lifecycle);
    }
    
    return EINCOMPATTYPE;
}

