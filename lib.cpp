#include "lib.h"

void Foo::print(const std::string &value) {
  printWithCout(value);
}

void Foo::printWithCout(const std::string &value) {
    std::cout << value << std::endl;
    crash();
}

void Foo::crash() {
  int *x = nullptr;
  *x = 10;
}


