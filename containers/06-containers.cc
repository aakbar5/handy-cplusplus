//
// Program
//  Containers: std::unordered_map, std::unordered_multimap usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 06-containers 06-containers.cc
//
// Execution
//  ./06-containers
//

#include <iostream>
#include <unordered_map>

// Print map
template <typename UserMap>
static void print_map(const UserMap& m) {
  for (const auto& item: m) {
    std::cout << item.first << " : " << item.second << '\n';
  }
}

//
// Entry function
//
int main() {
  // std::unordered_map declaration
  std::cout << "std::unordered_map ---" << '\n';
  {
    // Same as std::unordered_map but it will be unordered
    std::unordered_map<int, std::string> m;

    m.insert(std::make_pair(3, "entry3"));
    m.insert(std::make_pair(1, "entry1"));
    m.insert(std::make_pair(2, "entry2"));
    m.insert(std::make_pair(6, "entry6"));
    m.insert(std::make_pair(4, "entry4"));
    m.insert(std::make_pair(5, "entry5"));
    m.insert(std::make_pair(3, "entry3_2")); // it will fail

    std::cout << "Show items of the std::unordered_map " << m.size() << '\n';
    print_map(m);
  }

  // std::unordered_multimap declaration
  std::cout << "std::unordered_multimap ---" << '\n';
  {
    // Same as std::unordered_multimap but it will be unordered
    std::unordered_multimap<int, std::string> m;

    m.insert(std::make_pair(3, "entry3"));
    m.insert(std::make_pair(1, "entry1"));
    m.insert(std::make_pair(2, "entry2"));
    m.insert(std::make_pair(6, "entry6"));
    m.insert(std::make_pair(4, "entry4"));
    m.insert(std::make_pair(5, "entry5"));
    m.insert(std::make_pair(3, "entry3_2"));

    std::cout << "Show items of the std::unordered_multimap " << m.size() << '\n';
    print_map(m);
  }

  return 0;
}
