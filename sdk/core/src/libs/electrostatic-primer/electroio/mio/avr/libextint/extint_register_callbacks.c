#include <electroio/mio/extint/extint.h>

static volatile extint_callbacks *volatile _extint_callbacks = ((void*) 0);

void extint_register_callbacks(volatile extint_callbacks *volatile in_callbacks) {
    _extint_callbacks = in_callbacks;
}