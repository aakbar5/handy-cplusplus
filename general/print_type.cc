//
// Program
//  Print type of a variable.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o print_type print_type.cc
//
// Execution
//  ./print_type
//

#include <iostream>
#include <chrono>
#include <typeinfo>

//
// Entry function
//
int main() {
  auto now = std::chrono::high_resolution_clock::now();
  std::cout << typeid(now).name() << '\n';

  return 0;
}
