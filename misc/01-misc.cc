//
// Program
//  Generate all possible combinations of elements
//  from the input vectors.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-misc 01-misc.cc
//
// Execution
//  ./01-misc
//

#include <iostream>
#include <tuple>
#include <vector>

// Combine elements of two vectors (Cartesian product)
// save generated tuple using passed inserter iterator.
template<typename T1, typename T2, typename IteratorType>
void combine(const T1& vector1, const T2& vector2, IteratorType backInserter) {
  for (const auto& e1: vector1) {
    for (const auto& e2: vector2) {
      auto tup = std::make_tuple(e1, e2);
      *backInserter++ = tup;
    }
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- Generate combinations ---" << '\n';

  std::cout << " -- vector<int> + vector<char> --" << '\n';
  {
    std::vector<int> v1 { 1, 2 };
    std::vector<char> v2 { 'a', 'b' };

    std::vector<std::tuple<int, char>> v3 {};
    combine(v1, v2, std::back_inserter(v3));
    for (const auto& elem: v3) {
      std::cout << '('
                << std::get<0>(elem)
                << ", "
                << std::get<1>(elem)
                << ')'
                << '\n';
    }

    // Output
    // -- vector<int> + vector<char> --
    // (1, a)
    // (1, b)
    // (2, a)
    // (2, b)
  }

  std::cout << " -- vector<int> + vector<std::string> --" << '\n';
  {
    std::vector<int> v1 { 1, 2 };
    std::vector<std::string> v2 { "stringa", "stringb" };

    std::vector<std::tuple<int, std::string>> v3 {};
    combine(v1, v2, std::back_inserter(v3));
    for (const auto& elem: v3) {
      std::cout << '('
                << std::get<0>(elem)
                << ", "
                << std::get<1>(elem)
                << ')'
                << '\n';
    }

    // Output
    // -- vector<int> + vector<std::string> --
    // (1, stringa)
    // (1, stringb)
    // (2, stringa)
    // (2, stringb)
  }

  std::cout << " -- vector<int> + vector<Object> --" << '\n';
  {
    struct Object {
      int id;
      std::string name;
    };

    std::vector<int> v1 { 1, 2 };
    std::vector<Object> v2 { {10, "string10"}, {20, "string20"} };

    std::vector<std::tuple<int, Object>> v3 {};
    combine(v1, v2, std::back_inserter(v3));
    for (const auto& elem: v3) {
      std::cout << '('
                << std::get<0>(elem)
                << ", {" << std::get<1>(elem).id << ','
                         << std::get<1>(elem).name << "})"
                << '\n';
    }

    // Output
    // -- vector<int> + vector<Object> --
    // (1, {10,string10})
    // (1, {20,string20})
    // (2, {10,string10})
    // (2, {20,string20})
  }

  return 0;
}
