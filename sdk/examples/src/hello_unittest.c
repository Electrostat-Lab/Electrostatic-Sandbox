#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>
#include <electrostatic/electronetsoft/util/unit-testing/unit_test.h>
#include <electrostatic/electronetsoft/util/console/colors.h>
#include <stdio.h>

static inline int64_t execute(void **inputs) {
    return 0xFFFF; // wraps a number
}

static inline status_code assert(int64_t prop0, int64_t prop1) {
    return ((status_code) (prop0 == prop1) && ASSERTION_SUCCESS);
}

static inline void on_assertion_success(unit_test *test) {
    fprintf(stdout, GREEN "Test predicate %p holds!\n" RESET, test->assert);
}

static inline void on_assertion_failure(unit_test *test) {
    fprintf(stderr, RED "Test predicate %p isn't existential!\n" RESET, test->assert);
}

/**
 * Dispatched by the API callers callbacks when a "resize" command
 * is executed to continue operations safely.
 *
 * @param buffer the data buffer of interest
 * @param caller the caller address
 * @return PASS to indicate a pass code, otherwise a failure code
 */
static inline status_code update_buffer_size(list *buffer, void *caller) {
    if (rvalue(buffer) == NULL || rvalue(caller) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    if (caller == buffer->function_table->add) {
        printf("Caller for expansion\n");
        buffer->elements = realloc(buffer->elements, (size_t) buffer->limit * sizeof(list_element*));
    } else if (caller == buffer->function_table->remove_by_index) {
        printf("Caller for remove\n");
        buffer->limit >>= 2; // shrunk the limit by power of 2
        buffer->elements = realloc(buffer->elements, (size_t) (buffer->length << 2) * sizeof(list_element*));
    }
    return PASS;
}

int main() {
    list_function_table table = {
        .update_buffer_size = &update_buffer_size
    };
    
    list buffer = {
        .type = CONTIGUOUS_BUFFER,
        .function_table = &table,
        .limit = 8 << 2
    };

    // dynamically heap-allocate block for pointers
    list_element **elements = calloc(buffer.limit, sizeof(list_element*));
    
    // automatically stack-allocate a block for the unit test data
    list_element element = {
    };

    status_code __code = init_list_function_table(&buffer, elements, &table, NULL);
    if (PASS == __code) {
        fprintf(stdout, GREEN "Unit tests buffer init has succeeded!\n" RESET);
    } else {
        fprintf(stderr, RED "Unit tests buffer init has failed with error = %i\n" RESET, __code);
    }
    
    unit_test test = {
      .inputs = NULL,
      .on_assertion_success = &on_assertion_success,
      .on_assertion_failure = &on_assertion_failure,
      .assert = &assert,
      .execute = &execute,
      .proposition = 0xFFFF,
    };
    
    status_code _code0 = add_unit_test(&buffer, &test, &element);
    if (PASS != _code0) {
        fprintf(stderr,
                RED "Unit tests adding buffer has failed with error = %i\n" RESET, _code0);
    }

    status_code _code1 = assert_test_units(&buffer);
    if (PASS != _code1) {
        fprintf(stderr,
                RED "Unit tests assertion dispatch has failed with error = %i\n" RESET, _code1);
    }

    printf("Type = %zu\n", element.size);
    
    status_code _code2 = remove_unit_test(&buffer, &element);
    if (PASS != _code2) {
        fprintf(stderr, RED
        "Unit tests removing buffer element has failed with error = %i\n" RESET, _code2 == EUNDEFINEDBUFFER);
    }

    free(buffer.elements);
    
    return 0;
}