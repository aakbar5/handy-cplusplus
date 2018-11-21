//
// Program
//  Fold expression: associativity test in fold expression
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 02-fold 02-fold.cc
//
// Execution
//  ./02-fold
//

#include <iostream>

// right associativity
template <typename ... Args>
auto subtract_1(Args ... args) {
  return (args - ... - 0);
}

// left associativity
template <typename ... Args>
auto subtract_2(Args ... args) {
  return (0 - ... - args);
}

//
// Entry function
//
int main() {
  // associativity
  {
    std::cout << " 1 - (2 - 3) = " << subtract_1(1, 2, 3) << '\n'; // ans is  2
    std::cout << "(1 - 2) - 3  = " << subtract_2(1, 2, 3) << '\n'; // ans is -4
  }

  // no argument
  {
    std::cout << " ... = " << subtract_1() << '\n'; // ans is 0
    std::cout << " ... = " << subtract_2() << '\n'; // ans is 0
  }

  return 0;
}
