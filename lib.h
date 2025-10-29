#include <iostream>
#include <string>

class Foo {

public:
  void print(const std::string &value);

private:
  void printWithCout(const std::string &value);
  void crash();
};