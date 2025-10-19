#include <string>

#if __cplusplus >= 202302L
#include <print>
#else
#include <iostream>
#endif

class Foo {

public:
  void print(const std::string &value) {

#if __cplusplus >= 202302L
    printWithFmt(value);
#else
    printWithCout(value);
#endif
  }


private:

#if __cplusplus >= 202302L
  void printWithFmt(const std::string &value);
#else
  void printWithCout(const std::string &value);
#endif
  void crash();
};