#include <electrostatic/algorithm/arithmos/adt/list.h>
#include <electrostatic/util/unit-testing/unit_test.h>
#include <electrostatic/util/console/colors.h>
#include <errno.h>
#include <stdio.h>

static inline int64_t execute(void **inputs) {
    return 0xFFFF; // wraps a number   
}

static inline uint8_t assert(int64_t prop0, int64_t prop1) {
    return prop0 == prop1;
}

static inline void on_assertion_success(unit_test *test) {
    fprintf(stdout, GREEN "Test predicate %p holds!\n" RESET, test->assert);
}

static inline void on_assertion_failure(unit_test *test) {
    fprintf(stderr, RED "Test predicate %p isn't existential!\n" RESET, test->assert);
}

int main() {
    list_function_table table = {
    };
    
    list buffer = {
        .type = CONTIGUOUS_BUFFER,
        .function_table = &table,
        .limit = 8 << 2
    };
    
    list buffer2 = {
    .type = CONTIGUOUS_BUFFER,
    .function_table = &table,
    .limit = 8 << 2
};
    
    // dynamically heap-allocate block for pointers
    list_element **elements = calloc(buffer.limit, sizeof(list_element**));
    
    // automatically stack-allocate a block for the unit test data
    list_element element = {
    };
    
    if (init_list_function_table(&buffer, elements, &table) == 0) {
        fprintf(stdout, GREEN "Unit tests buffer init has succeeded!\n" RESET);
    } else {
        fprintf(stderr, RED "Unit tests buffer init has failed with error = %i\n" RESET, buffer.error.value);
    }
    
    unit_test test = {
      .inputs = NULL,
      .on_assertion_success = &on_assertion_success,
      .on_assertion_failure = &on_assertion_failure,
      .assert = &assert,
      .execute = &execute,
      .proposition = 0xFFF,
      .error = {
        .value = 0
      }
    };
    
    add_unit_test(&buffer, &test, &element);

    assert_test_units(&buffer);

    printf("Type = %zu\n", element.size);
    
    remove_unit_test(&buffer, &element);

    free(elements);
    
    return 0;
}