//
// Program
//  Type traits - An improved version of type_traits-03
//  The main theme is to use using for value management.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o type_traits-04 type_traits-04.cc
//
// Execution
//  ./type_traits-04
//

#include <iostream>

// A structure takes a bool value
// and assign to value
template<bool val>
struct is_const_base {

  // static: To access it without creating object of struct
  // const: Once assigned, don't change its value
  // value: Recommended variable name to expose value
  static const bool value = val;
};

// Define types rather using struct name
using const_false_type = is_const_base<false>;
using const_true_type = is_const_base<true>;

// Extend is_const_base and have false value
// for everything
template<typename T>
struct is_const: const_false_type  {
};

// Specialization: Extend is_const_base and have true value
// if given element is const qualified.
template<typename T>
struct is_const<const T>: const_true_type  {
};

//
// Entry function
//
int main() {

  {
    static_assert(is_const<const int>::value);
    static_assert(not is_const<int>::value);
  }

  return 0;
}
