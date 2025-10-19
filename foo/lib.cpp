#include "lib.h"

// Implementation of Foo class methods (if any)
// Currently empty since Foo only has inline methods.

void Foo::crash() {
    int* x = nullptr;
    *x = 10;
}