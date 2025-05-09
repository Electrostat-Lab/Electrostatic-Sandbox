#include <electrostatic/electronetsoft/util/unit-testing/unit_test.h>
#include <electrostatic/electronetsoft/util/utilities.h>
#include <electrostatic/electronetsoft/util/console/colors.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define SPREAD_HASHING(value, type) ((type) #value >> (sizeof(type) / 2) ^ (type) #value)
#define HASHED_TYPE (SPREAD_HASHING(sizeof(unit_test), size_t))

static inline void iterator_callback0(list *units, list_element *element) {
    if (rvalue(units) == NULL || rvalue(element) == NULL
            || rvalue(element->data) == NULL) {
        return ;
    }
    
    unit_test *unit_test_ = element->data;
    
    if (element->size != HASHED_TYPE) {
        return ;
    }
    
    test(unit_test_);
}

static inline void iterator_callback(list *units, list_element *element) {
    if (units == NULL || element == NULL || element->data == NULL) {
        return ;
    }

    unit_test *unit_test_ = element->data;

    if (element->size != HASHED_TYPE) {
        return ;
    }

    assert_test(unit_test_);
}

// just runs the test without validation
int64_t test(unit_test *test) {
    if (rvalue(test) == NULL
        || rvalue(test->execute) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    return test->execute(test->inputs);
}

status_code test_units(list *units) {
    if (rvalue(units) == NULL
        || rvalue(units->function_table) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    return units->function_table->iterator(units, (list_info) {
       .start_index = 0,
       .length = units->length,
       .rate = 1
    }, &iterator_callback0);
}

status_code assert_test_units(list *units) {
    if (units == NULL || units->function_table == NULL) {
        return EUNDEFINEDBUFFER;
    }
    return units->function_table->iterator(units, (list_info) {
       .start_index = 0,
       .length = units->length,
       .rate = 1
    }, &iterator_callback);
}

// asserts against a proposition and throws an error when necessary
status_code assert_test(unit_test *test) {
    if (test == NULL || test->execute == NULL
        || &(test->proposition) == NULL || test->assert == NULL
        || test->on_assertion_success == NULL || test->on_assertion_failure == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    int64_t proposition0 = test->execute(test->inputs);
    // predicates position0 and position1 in a formula
    status_code predicate = test->assert(proposition0, test->proposition);
    
    if (ASSERTION_FAILURE == predicate) {
        test->on_assertion_failure(test);
        return ASSERTION_FAILURE;
    }

    test->on_assertion_success(test);

    return ASSERTION_SUCCESS;
}

status_code add_unit_test(list *units, unit_test *test, list_element *element) {
    if (units == NULL || units->function_table == NULL || test == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    element->data = test;
    element->size = HASHED_TYPE;
    
    return units->function_table->add(units, element);
}

status_code remove_unit_test(list *units, list_element *element) {
    if (units == NULL || units->function_table == NULL
        || element == NULL || element->data == NULL) {
        return EUNDEFINEDBUFFER;
    }
    if (element->size != HASHED_TYPE) {
        return EINCOMPATTYPE;
    }

    unit_test *unit_test_ = element->data;
    return units->function_table->remove_by_element(units, element);
}

status_code add_unit_tests(list *units, unit_test **tests, list_element **elements) {
    if (tests == NULL || elements == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    status_code __code = PASS;
    
    for (uint64_t i = 0; tests[i] != NULL && elements[i] != NULL; i++) {
        if (PASS != __code) {
            return __code;
        }
        __code = add_unit_test(units, tests[i], elements[i]);
    }
    return __code;
}

status_code remove_unit_tests(list *units, list_element **elements) {
    if (elements == NULL) {
        return EUNDEFINEDBUFFER;
    }
    status_code __code = PASS;
    
    for (uint64_t i = 0; elements[i] != NULL; i++) {
        if (PASS != __code) {
            return __code;
        }
        __code = remove_unit_test(units, elements[i]);
    }
    return __code;
}