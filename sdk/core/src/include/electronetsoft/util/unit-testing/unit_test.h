//
// A unit testing API that defines an execute, and an assertion function together with
// some assertion events.
//
// Author: pavl_g.
//

//
// Scientific concepts:
// A unit test is a function composed of {Inputs, a Return value, A predicate, An errno to throw if predicate
// didnot hold}.
//

#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

#include <stdint.h>
#include <electronetsoft/arithmos/adt/list.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct unit_test (unit_test);

struct unit_test {
  void **inputs;
  int64_t (*execute)(void **inputs);
  status_code (*assert)(int64_t, int64_t);
  void (*on_assertion_success)(unit_test *);
  void (*on_assertion_failure)(unit_test *);
  int64_t proposition;
};

// just runs the test without validation
int64_t test(unit_test *test);
status_code test_units(list *units);
status_code add_unit_test(list *units, unit_test *test, list_element *element);
status_code remove_unit_test(list *units, list_element *element);
status_code add_unit_tests(list *units, unit_test **tests, list_element **element);
status_code remove_unit_tests(list *units, list_element **elements);
// asserts against a predicate and throws an error when necessary
status_code assert_test(unit_test *test);
status_code assert_test_units(list *units);

#ifdef __cplusplus
}
#endif
#endif