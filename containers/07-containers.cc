//
// Program
//  Containers: std::unordered_map with enum class
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 07-containers 07-containers.cc
//
// Execution
//  ./07-containers
//

#include <iostream>
#include <functional>
#include <unordered_map>

enum class Hardware {
  TARGET_A = 0,
  TARGET_B,
  TARGET_C,
  TARGET_D,
  TARGET_E,
};

// Print map
template <typename UserMap>
static void print_map(const UserMap& m) {
  for (const auto& item: m) {
    std::cout << static_cast<int>(item.first) << " : " << item.second << '\n';
  }
}

//
// Entry function
//
int main() {
  // std::unordered_map declaration
  std::cout << "std::unordered_map with enum_class ---" << '\n';
  {
    // Same as std::unordered_map but it will be unordered
    std::unordered_map<Hardware, std::string> m;

    m.insert(std::make_pair(Hardware::TARGET_A, "target1"));
    m.insert(std::make_pair(Hardware::TARGET_B, "target2"));
    m.insert(std::make_pair(Hardware::TARGET_C, "target3"));
    m.insert(std::make_pair(Hardware::TARGET_D, "target4"));
    m.insert(std::make_pair(Hardware::TARGET_E, "target5"));

    std::cout << "Show items of the std::unordered_map " << m.size() << '\n';
    print_map(m);
  }

  std::cout << "std::unordered_map with enum_class (custom hash function) ---" << '\n';
  {
    struct KeyHash {
      std::size_t operator()(const Hardware& key) const {
        return std::hash<std::size_t>{}(static_cast<std::size_t>(key));
      }
    };
    struct KeyEqual {
      size_t operator()(const Hardware& lhs, const Hardware& rhs) const {
        return static_cast<size_t>(lhs) == static_cast<size_t>(rhs);
      }
    };

    // Same as std::unordered_map but it will be unordered
    std::unordered_map<Hardware, std::string, KeyHash, KeyEqual> m;

    m.insert(std::make_pair(Hardware::TARGET_A, "target1"));
    m.insert(std::make_pair(Hardware::TARGET_B, "target2"));
    m.insert(std::make_pair(Hardware::TARGET_C, "target3"));
    m.insert(std::make_pair(Hardware::TARGET_D, "target4"));
    m.insert(std::make_pair(Hardware::TARGET_E, "target5"));

    std::cout << "Show items of the std::unordered_map " << m.size() << '\n';
    print_map(m);
  }

  return 0;
}

// Output
// std::unordered_map with enum_class ---
// Show items of the std::unordered_map 5
// 4 : target5
// 3 : target4
// 2 : target3
// 1 : target2
// 0 : target1
// std::unordered_map with enum_class (custom hash function) ---
// Show items of the std::unordered_map 5
// 4 : target5
// 3 : target4
// 2 : target3
// 1 : target2
// 0 : target1
