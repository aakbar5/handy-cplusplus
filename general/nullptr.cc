#include <iostream>
using namespace std;

void foo(int a) { std::cout << a << '\n'; }
void foo(int *a) {
  if (a)
    std::cout << "a is true";
  else
    std::cout << "a is false";
}

int main() {
  {
    int a = 0;          // Call foo(int) func
    foo(a);
  }

  {
    // int b = nullptr;   // comiler error std::nullptr can not convert to int
    // foo(b);
  }

  {
    int *c = std::nullptr; // Call foo(int *a) func
  }

  return 0;
}
