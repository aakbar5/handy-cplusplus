//
// Program
//  Access std::unordered_map with index.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 10-containers 10-containers.cc
//
// Execution
//  ./10-containers
//

#include <iostream>
#include <unordered_map>
#include <iterator>

//
// Entry function
//
int main() {
  std::unordered_map<std::string, std::string> umap {
    {"key1", "value1"},
    {"key2", "value2"},
    {"key3", "value3"},
  };

  for (uint32_t idx = 0; idx < umap.size(); ++idx) {
    auto it = std::begin(umap);
    std::advance(it, idx);
    std::cout << "{" << it->first << "," << it->second << "}" << "\n";
  }

  return 0;
}
