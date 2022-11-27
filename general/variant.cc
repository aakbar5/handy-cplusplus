//
// Program
//  std::variant + std::visit usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o variant variant.cc
//
// Execution
//  ./variant
//

#include <iostream>
#include <cassert>
#include <variant>

//
// Entry function
//
int main() {
  std::cout << "--- std::variant ---" << '\n';

  std::variant<int, float> var;
  var = 1.0f;

  std::cout << "Size: " << std::variant_size_v<decltype(var)> << '\n'; // size will be 2

  //-- Reterieve values
  std::cout << "Index: " << var.index() << '\n';
  assert(var.index() == 1); // Index # 1 holds the real value

  var = 5;
  std::cout << "Index: " << var.index() << '\n';
  assert(var.index() == 0); // Index # 0 holds the real value

  std::cout << "Value by index: " << std::get<0>(var) << '\n';
  assert(std::get<0>(var) == 5);

  std::cout << "Value by datatype: " << std::get<int>(var) << '\n';
  assert(std::get<int>(var) == 5);

  //-- Validation
  std::cout << "Is it float? " << std::boolalpha << std::holds_alternative<float>(var) << '\n';
  assert(std::holds_alternative<float>(var) == false);

  std::cout << "Is it int? " << std::boolalpha << std::holds_alternative<int>(var) << '\n';
  assert(std::holds_alternative<int>(var) == true);

  //-- Itererate std::variant

  // Find active element
  switch (var.index()) {
    case 0: std::cout << "type is: int" << '\n'; break;
    case 1: std::cout << "type is: float" << '\n'; break;
    default: std::cout << "type is: unknown" << '\n'; break;
  }

  // Print value of the active element
  if (int *p = std::get_if<int>(&var)) {
    std::cout << "type is: int" << " value is: " << *p << '\n';
  }
  else if (float *p = std::get_if<float>(&var)) {
    std::cout << "type is: float"  << " value is: " << *p << '\n';
  }

  // Output:
  // type is: int
  // type is: int value is: 5

  //-- std::visit
  auto func = [](auto&& elem){
    std::cout << "std::visit: " << elem << '\n';
  };
  std::visit(func, var); // Output: std::visit: 5

  struct visitor {
    void operator() (int i) { std::cout << "type is: int" << " value is: " << i << '\n'; }
    void operator() (float i) { std::cout << "type is: float" << " value is: " << i << '\n'; }
  };
  std::visit(visitor{}, var); // Output: type is: int value is: 5

  return 0;
}
