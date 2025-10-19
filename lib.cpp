#include "lib.h"

#if __cplusplus >= 202302L
void Foo::printWithFmt(const std::string &value) {
  std::println("{}", value);
  crash();
}
#else
void Foo::printWithCout(const std::string &value) {
    std::cout << value << std::endl;
    crash();
}
#endif

void Foo::crash() {
  int *x = nullptr;
  *x = 10;
}


