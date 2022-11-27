//
// Program
//  structure_bindings
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o structure_bindings structure_bindings.cc
//
// Execution
//  ./structure_bindings
//

#include <iostream>
#include <cassert>
#include <utility>
#include <set>
#include <map>

//
// Entry function
//
int main() {
  std::cout << "--- Structure bindings ---" << '\n';

  // Simple structure bindings
  {
    struct Test {
      uint32_t field1;
      uint32_t field2;
    };

    // NOTE: -pedantic is stopping it from compilation.
    // In this case you need -std=c++20
    // Test test {
    //   .field1 = 100,
    //   .field2 = 200,
    // };
    Test test {};
    test.field1 = 100;
    test.field2 = 200;

    auto [f1, f2] = test;
    std::cout << "Simple structure bindings...\n";
    std::cout << " - Field # 1: " << test.field1 << ", " << f1 << '\n';
    std::cout << " - Field # 2: " << test.field2 << ", " << f2 << '\n';

    assert(f1 == 100);
    assert(f2 == 200);
    assert(test.field1 == 100);
    assert(test.field2 == 200);
  }

  // std::pair
  {
    std::pair<uint32_t, uint32_t> p {100, 200};
    auto [f1, f2] = p;
    std::cout << "std::pair mapping...\n";
    std::cout << " - Field # 1: " << p.first << ", " << f1 << '\n';
    std::cout << " - Field # 2: " << p.second << ", " << f2 << '\n';

    assert(f1 == 100);
    assert(f2 == 200);
    assert(p.first == 100);
    assert(p.second == 200);
  }

  // std::pair and ignore element
  {
    std::pair<uint32_t, uint32_t> p {100, 200};
    auto [_, f2] = p;
    std::cout << "std::pair mapping and ignore first element...\n";
    std::cout << " - Field # 2: " << p.second << ", " << f2 << '\n';

    assert(f2 == 200);
    assert(p.first == 100);
    assert(p.second == 200);
  }

  // std::set
  {
    std::set<uint32_t> s;
    auto [iterator, inserted] = s.insert(10);

    std::cout << "std::set mapping...\n";
    std::cout << " - Iterator: " << *iterator << '\n';
    std::cout << " - inserted: " << std::boolalpha << inserted << '\n';
  }

  // std::map
  {
      std::map<std::string, std::string> m;
      m.insert(std::make_pair("zz", "entry1"));
      m.insert(std::make_pair("tt", "entry2"));
      m.insert(std::make_pair("dd", "entry4"));

      std::cout << "std::map via std::pair...\n";
      for (const auto& item: m) {
        std::cout << item.first << " : " << item.second << '\n';
      }

      // Loop can be simplified as
      std::cout << "std::map via bindings...\n";
      for (const auto& [key, value]: m) {
        std::cout << key << " : " << value << '\n';
      }
  }

  return 0;
}
