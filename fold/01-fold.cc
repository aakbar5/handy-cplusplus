//
// Program
//  Fold expression: Simple fold expression
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-fold 01-fold.cc
//
// Execution
//  ./01-fold
//

#include <iostream>

// Function accepts variadic arguments
// Keeps the return auto to accomodate different
// data types in the same function
template <typename ... Args>
auto add(Args ... args) {
  return (args + ...);
}

template <typename ... Args>
auto add_2(Args ... args) {
  return (args + ... + 0); // 0 is out identity element
}

//
// Entry function
//
int main() {
  // Variadic template
  {
    // Above function will be expanded something like this
    // for add(1, 2)
    // int add<int, int>(int __ts0, int __ts1)
    // {
    //     return __ts0 + __ts1;
    // }
    std::cout << "1 + 2 = " << add(1, 2) << '\n';

    std::cout << "1 + 2 + 3 = " << add(1, 2, 3) << '\n';

    std::cout << "1.0f + 2.0f = " << add(1.0f, 2.1f) << '\n';

    std::string t1("Test1");
    std::string t2("Test2");
    std::cout << t1 << " + " << t2 << " = " << add(t1, t2) << '\n';
  }

  // no argument
  {
    // Following line will generate compiler error # unary fold expression has empty expansion
    // for operator '+' with no fallback value return (ts + ...);
    // std::cout << "1 + 2 + 3 = " << add() << '\n';
    std::cout << " ... = " << add_2() << '\n'; // It will work
    // because now compiler will generate something like following
    // template<>
    // int sum<>()
    // {
    //     return 0;
    // }
  }

  return 0;
}
