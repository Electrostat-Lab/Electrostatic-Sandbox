#include <electronetsoft/arithmos/map/collision_handler.h>

status_code no_duplicates_handler(list *buffer, list_element *item, list_element *element) {
    if (NO_DUPLICATES != buffer->col_scheme) {
        return EINCOMPATTYPE;
    }
    // test if they are identical items
    // replace the map element with the new
    // map_element carried on the element
    // de-allocate the carrier structure
    typed_pointer __key0 = item->metadata;
    typed_pointer __key1 = element->metadata;

    if (__key0.type == __key1.type && __key0.type == TYPE_STR) {
        if (strcmp(__key0.address.str, __key1.address.str) == 0) {
            item->data = element->data;
            item->type = element->type;
            item->size = element->size;
            return EBUFFER_EXISTS;
        }
    } else if (__key0.type == __key1.type && __key0.type == TYPE_ID) {
        if (*__key0.address.id == *__key1.address.id) {
            item->data = element->data;
            item->type = element->type;
            item->size = element->size;
            return EBUFFER_EXISTS;
        }
    } else {
        return EINCOMPATTYPE;
    }

    return PASS;
}
