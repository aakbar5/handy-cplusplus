//
// Program
//  <algorithm> @ make_heap, sort_heap usage.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o algorithm_heap_01 algorithm_heap_01.cc
//
// Execution
//  ./algorithm_heap_01
//

#include <iostream>
#include <vector>
#include <algorithm>

static std::ostream& operator<< (std::ostream& out, const std::vector<int>& vec) {
  for (const auto& num: vec) {
    out << num << " ";
  }
  return out;
}

//
// Entry function
//
int main() {

  std::cout <<"\n--- [make_heap] ---\n";
  {
    std::vector<int> vec { 2, 5, 3, 6, 1, 9, 0 };

    std::cout << "Input:           " << vec << '\n';
    std::cout << "is_heap:         " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end())
                                     << '\n';

    // Arrange our vector into Max Heap arrangement
    std::make_heap(vec.begin(), vec.end());

    std::cout << "After make_heap: " << vec << '\n';
    std::cout << "is_heap:         " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end())
                                     << '\n';
  }

  std::cout <<"\n--- [sort_heap] ---\n";
  {
    std::vector<int> vec { 2, 5, 3, 6, 1, 9, 0 };

    std::cout << "Input:           " << vec << '\n';
    std::cout << "is_heap:         " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end())
                                     << '\n';

    // Arrange ascending order - heap property is lost
    std::sort_heap(vec.begin(), vec.end());

    std::cout << "After sort_heap: " << vec << '\n';
    std::cout << "is_heap:         " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end())
                                     << '\n';
  }

  return 0;
}

/*
--- [make_heap] ---
Input:           2 5 3 6 1 9 0
is_heap:         false
After make_heap: 9 6 3 5 1 2 0
is_heap:         true

--- [sort_heap] ---
Input:           2 5 3 6 1 9 0
is_heap:         false
After sort_heap: 0 1 3 6 9 5 2
is_heap:         false
*/

