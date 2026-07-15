/**
 * @brief A techdemo showcasing the use of dynamic contiguous buffers of the ElectroNetSoft Arithmos Framework.
 * @copyright BSD-3 Clause License ElectroNetSoft, Arithmos, The Electrostatic-Sandbox SDK project.
 * @author pavl_g
 */
#include <alloca.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <electronetsoft/arithmos/adt/list.h>

/**
 * Dispatched by the API callers callbacks when an "iterate" command
 * is executed to examine the data buffer items.
 *
 * @param buffer the data buffer of interest
 * @param element the current item of iteration
 */
status_code iterator_callback(list *buffer, list_info info, list_element *element) {
    printf("Index at %lud = %p\n", info.index, element->data);
    return PASS;
}

int main() {

    // Preprocessing automata (pre-init phase) -- memory allocation
    list_function_table table = {
    };
    list buffer_ = {
            .type = CONTIGUOUS_BUFFER,
            .function_table = &table,
            .limit = (8 << 2) + 1,
    };
    list_element **elements = calloc(buffer_.limit, sizeof(list_element*));
    list *buffer = &buffer_;

    // Preprocessing automata (initialization phase) -- list initialization
    status_code _code0 = init_list_function_table(buffer, elements, &table, NULL);
    if (PASS == _code0) {
        printf("Init Succeeded!\n");
    } else {
        printf("%i\n", _code0);
    }

    // Processing automata -- Data Write (adding items)
    status_code _code1 = PASS;
    for (int i = 0; i < 100; i++) {
        list_element *element = alloca(sizeof(list_element));
        int *test_data = alloca(sizeof(int));
        *test_data = 260 + i;
        element->data = test_data;

        _code1 = buffer->function_table->add(buffer, element);
        if (PASS == _code1) {
            printf("Added Item!\n");
        } else {
            printf("%i\n", _code1);
        }
    }

    // Processing automata -- Data Read and Printing items
    status_code _code2 = buffer->function_table->iterator(buffer,
                                                    (list_info) {
                                                        .index = 0,
                                                        .length = buffer->limit,
                                                        .rate = 2
                                                    }, &iterator_callback);
    if (PASS != _code2) {
        perror("Failure to iterate\n");
    }

    // Processing automata -- Test remove
    status_code _code3 = buffer->function_table->remove_by_index(buffer, 100);
    if (PASS != _code3) {
        perror("Failure to remove item\n");
    } else {
        buffer->function_table->iterator(buffer,
                                         (list_info) {
                                                 .index = 0,
                                                 .length = buffer->limit,
                                                 .rate = 1
                                         }, &iterator_callback);
    }

    // post-processing automata -- Buffer destruction and memory release
    // use the updated address of the elements buffer.
    // Warning: free (elements) wrong! Because of reallocation callback processors.
    free(buffer->elements);

    // run:  valgrind -v -s ./sdk/examples/cmake-build/linux/x86-64/hello_lists.elf
    // to examine for memory leaks.

    return 0;
}
