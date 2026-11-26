#include "electronetsoft/util/types.h"
#include <electronetsoft/arithmos/map/map_companion.h>
#include <electronetsoft/arithmos/map/collision_handler.h>

status_code init_chain(list *buffer, list_element *header,
                                 list_element *next,
                                 uint64_t index) {

    status_code __code;

    list *__separate_chain = NULL;
    __code = init_adt_list(&__separate_chain, (8 << 2) + 1);
    if (PASS != __code || NULL == __separate_chain) {
        return __code;
    }

    // copy it to the buffer
    __code = __separate_chain->operations->add(__separate_chain, header);
    if (PASS != __code) {
        return __code;
    }

    __code = __separate_chain->operations->add(__separate_chain, next);
    if (PASS != __code) {
        return __code;
    }

    // add the secondary buffer instead
    list_element __chain_element = {
        .data = __separate_chain,
        .metadata = (buffer->elements + index)->metadata,
        .type = ELEMENT_LIST,
        .size = sizeof (list)
    };

    __code = buffer->operations->insert_overwrite(buffer, &__chain_element, index);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}