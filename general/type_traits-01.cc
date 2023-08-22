//
// Program
//  Type traits - a basic implementation to check
//  variables of the same datatype
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o type_traits-01 type_traits-01.cc
//
// Execution
//  ./type_traits-01
//

#include <iostream>

// Define a template-ized structure which
// accepts two elements of datatype T and S
template<typename T, typename S>
struct is_same {

  // static: To access it without creating object of struct
  // const: Once assigned, don't change its value
  // value: Recommended variable name to expose value
  static const bool value = false;
};

// Specialization of the above template-ized structure
// which takes elements of the same datatype T and
// have true value if both are of the the same datatype.
template<typename T>
struct is_same<T, T> {
  static const bool value = true;
};

//
// Entry function
//
int main() {

  {
    static_assert(is_same<int, int>::value);
    static_assert(not is_same<int, float>::value);
  }

  {
    int vari = 10;
    int varii = 20;
    float varf = 10.0f;

    static_assert(is_same<decltype(vari), decltype(varii)>::value);
    static_assert(not is_same<decltype(vari), decltype(varf)>::value);
  }

  return 0;
}
