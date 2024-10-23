#include <electrostatic/electronetsoft/util/unit-testing/unit_test.h>
#include <electrostatic/electronetsoft/util/console/colors.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define SPREAD_HASHING(value, type) ((type) #value >> (sizeof(type) / 2) ^ (type) #value)
#define HASHED_TYPE (SPREAD_HASHING(sizeof(unit_test), size_t))

static inline void iterator_callback0(list *units, list_element *element) {
    if (units == NULL || element == NULL || element->data == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return;
    }
    
    unit_test *unit_test_ = element->data;
    
    if (element->size != HASHED_TYPE) {
        return;
    }
    
    test(unit_test_);
}

static inline void iterator_callback(list *units, list_element *element) {
    if (units == NULL || element == NULL || element->data == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return;
    }

    unit_test *unit_test_ = element->data;

    if (element->size != HASHED_TYPE) {
        return;
    }
    
    assert_test(unit_test_);
}

// just runs the test without validation
void test(unit_test *test) {
    if (test == NULL || test->execute == NULL) {
        init_errno(&test->error);
        test->error.value = EUNDEFINEDBUFFER;
        return;
    }
    test->execute(test->inputs);
}

void test_units(list *units) {
    if (units == NULL || units->function_table == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return;
    }
    units->function_table->iterator(units, (list_info) {
       .start_index = 0,
       .length = units->length,
       .rate = 1
    }, &iterator_callback0);
}

void assert_test_units(list *units) {
    if (units == NULL || units->function_table == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return;
    }
    units->function_table->iterator(units, (list_info) {
       .start_index = 0,
       .length = units->length,
       .rate = 1
    }, &iterator_callback);
}

// asserts against a proposition and throws an error when necessary
void assert_test(unit_test *test) {
    if (test == NULL || test->execute == NULL
        || &(test->proposition) == NULL || test->assert == NULL
        || test->on_assertion_success == NULL || test->on_assertion_failure == NULL) {
        
        init_errno(&test->error);
        test->error.value = EUNDEFINEDBUFFER;
        return;
    }
    
    int64_t proposition0 = test->execute(test->inputs);
    // predicates position0 and position1 in a formula
    uint8_t predicate = test->assert(proposition0, test->proposition);
    
    if (!predicate) {
        test->on_assertion_failure(test);
        return;
    }
    
    test->on_assertion_success(test);
}

uint8_t add_unit_test(list *units, unit_test *test, list_element *element) {
    if (units == NULL || units->function_table == NULL || test == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    element->data = test;
    element->size = HASHED_TYPE;
    
    return units->function_table->add(units, element);
}

uint8_t remove_unit_test(list *units, list_element *element) {
    if (units == NULL || units->function_table == NULL
        || element == NULL || element->data == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    unit_test *unit_test_ = element->data;

    if (element->size != HASHED_TYPE) {
        return 1;
    }
    return units->function_table->remove_by_element(units, element);
}

uint8_t add_unit_tests(list *units, unit_test **tests, list_element **elements) {
    if (tests == NULL || elements == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    uint8_t success = 0;
    
    for (uint64_t i = 0; tests[i] != NULL && elements[i] != NULL; i++) {
        success += add_unit_test(units, tests[i], elements[i]);
    }
    return success;
}

uint8_t remove_unit_tests(list *units, list_element **elements) {
    if (elements == NULL) {
        init_errno(&units->error);
        units->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    uint8_t success = 0;
    
    for (uint64_t i = 0; elements[i] != NULL; i++) {
        success += remove_unit_test(units, elements[i]);
    }
    return success;
}