//
// Program
//  Find a pair in std::vector
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 09-containers 09-containers.cc
//
// Execution
//  ./09-containers
//

#include <iostream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <algorithm>
#include <optional>

using element = std::pair<uint32_t, float>;

// Checks if the container contains given element
bool contains(const std::vector<element>& vec, uint32_t key) {
  auto it = std::find_if(vec.begin(), vec.end(), [key](const element& elem) {
    return (elem.first == key);
  });

  return (it != vec.end());
}

// Checks if the container contains given element
std::optional<element> find(const std::vector<element>& vec, uint32_t key) {
  auto it = std::find_if(vec.begin(), vec.end(), [key](const element& elem) {
    return (elem.first == key);
  });

  if (it == vec.end()) {
    return std::nullopt;
  }

  int distance = std::distance(vec.begin(), it);
  return vec.at(distance);
}

//
// Entry function
//
int main() {
  std::vector<element> vec {
    {1, 1.0f},
    {2, 2.0f},
    {3, 3.0f},
  };

  // Check whether key is in container
  assert(contains(vec, 1) == true);
  assert(contains(vec, 3) == true);
  assert(contains(vec, 5) == false);

  // Find pair in container
  for (auto key: {1, 2, 4, 5}) {
    auto f = find(vec, key);
    if (f.has_value()) {
      auto pair = f.value();
      std::cout << key << " -> " << "{" << pair.first << "," << pair.second << "}\n";
    }
    else {
      std::cout << key << " -> " << "{ not found }\n";
    }
  }

  return 0;
}
