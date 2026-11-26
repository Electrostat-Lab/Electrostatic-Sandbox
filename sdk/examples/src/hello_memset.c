#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct test__ {
    int x;
    int y;
} test__;

typedef struct test {
    char *name;
    int size;
    test__ t;
} test;

int main(void) {

    test *_test = malloc(10 * sizeof(test));

    // some garbage values
    _test->name = "##1891";
    _test->size = 0x001201412;
    _test->t.x = 222;

    *_test = (test) {0};
    
    memset(_test, 0, sizeof(test));

    printf("(%s, %d, x = %d, y = %d) \n", _test->name, _test->size, _test->t.x, _test->t.y);
    printf("%d\n", _test->name == NULL);
    free(_test);
    return 0;
}
