#include <electrostatic/electronetsoft/util/errno/errno.h>
#include <alloca.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>

void iterator(list *buffer, list_element *element) {
    uint64_t index = 0;
    if (element < 0) {
        return;
    }
    buffer->function_table->indexof(buffer, element, &index);
    printf("Index at %llud = %p\n", index, element->data);
}

uint8_t update_buffer_size(list *buffer, void *caller) {
    if (caller == buffer->function_table->add) {
        buffer->elements = realloc(buffer->elements, (size_t) buffer->limit * sizeof(list_element*));
    } else if (caller == buffer->function_table->remove_by_index) {
        printf("Caller for remove\n");
        buffer->limit >>= 2; // shrunk the limit by power of 2
        buffer->elements = realloc(buffer->elements, (size_t) (buffer->length << 2) * sizeof(list_element*));
    }
    return 0;
}

list_function_table table = {
    .update_buffer_size = &update_buffer_size
};

int main() {
    
    list buffer_ = {
        .type = CONTIGUOUS_BUFFER,
        .function_table = &table,
        .limit = 8 << 2
    };
    
    list_element **elements = calloc(buffer_.limit, sizeof(list_element**));
    
    list *buffer = &buffer_; 
    
    if (init_list_function_table(buffer, elements, &table) == 0) {
        printf("Init Succeeded!\n");
    } else {
        printf("%i\n", buffer->error.value);
    }
    
    int x = 20;
    list_element ielement = {
        .data = &x,
    };
    
    int y = 30;
    list_element iielement = {
        .data = &y,
    };
    
    printf("%llud\n", buffer->length);
    printf("%llud\n", buffer->limit);
    
    list_element **ebuffer = calloc(buffer->limit, sizeof(void**));
    ebuffer[0] = &ielement;
    ebuffer[1] = &iielement;

    for (int i = 0; i < 16 << 2; i++) {
        buffer->function_table->add(buffer, ebuffer[0]);
    }
    
    if (buffer->function_table->contains(buffer, &ielement) != 0) {
        printf("Element Not Found, E = %d\n", buffer->error.value);
    } else {
        uint64_t index = 0;
        buffer->function_table->indexof(buffer, &iielement, &index);
        printf("Element Found at index = %llud\n", index);
    }
    
    if (buffer->function_table->remove_by_index(buffer, 0) != 0) {
        printf("Remove failed, E = %d\n", buffer->error.value);
    }
    
    list_element *e = buffer->function_table->get_end_address(buffer);
    printf("Fetch by address: %d\n", *((int*) e->data));
    
    buffer->function_table->add(buffer, ebuffer[0]);
    buffer->function_table->add(buffer, ebuffer[0]);
    
    if (buffer->function_table->contains_all(buffer, ebuffer) != 0) {
        printf("Elements Not Found, E = %d\n", buffer->error.value);
    } else {
        uint64_t index = 0;
        buffer->function_table->indexof(buffer, &iielement, &index);
        buffer->function_table->indexof(buffer, &ielement, &index);
        printf("Elements Found at index = %llud\n", index);
    }
    
    buffer->function_table->add_all(buffer, ebuffer);
    buffer->function_table->add_all(buffer, ebuffer);
    buffer->function_table->add_all(buffer, ebuffer);
    
    buffer->function_table->iterator(buffer, (list_info) {
        .start_index = 0,
        .length = buffer->length,
        .rate = 1
    }, &iterator);

    printf("Last Index = %llud\n", buffer->length);
    printf("%llud\n", buffer->limit);
    
    free((void*) ebuffer);
    free((void*) buffer->elements);

    return 0;
}
