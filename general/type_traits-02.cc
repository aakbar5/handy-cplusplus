//
// Program
//  Type traits - a basic implementation to check
//  variable is const qualified or not.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o type_traits-02 type_traits-02.cc
//
// Execution
//  ./type_traits-02
//

#include <iostream>

// Define a template-ized structure which
// accepts an element of datatype T
template<typename T>
struct is_const {

  // static: To access it without creating object of struct
  // const: Once assigned, don't change its value
  // value: Recommended variable name to expose value
  static const bool value = false;
};

// Specialization of the above template-ized structure
// which takes an element and have true value if given
// element is const qualified.
template<typename T>
struct is_const<const T> {
  static const bool value = true;
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
