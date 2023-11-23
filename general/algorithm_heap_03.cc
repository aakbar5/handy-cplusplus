//
// Program
//  <algorithm> @ pop_heap
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o algorithm_heap_03 algorithm_heap_03.cc
//
// Execution
//  ./algorithm_heap_03
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

  std::cout <<"\n--- [pop_heap] ---\n";
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

    std::cout << "Call pop_heap...\n";
    std::pop_heap(vec.begin(), vec.end());
    int num = vec.back();
    vec.pop_back();

    std::cout << "Input:           " << vec << '\n';
    std::cout << "Pop element:     " << num << '\n';
    std::cout << "is_heap @ full:  " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end())
                                     << '\n';
  }

  return 0;
}

/*
--- [pop_heap] ---
Input:           2 5 3 6 1 9 0
is_heap:         false
After make_heap: 9 6 3 5 1 2 0
is_heap:         true
Call pop_heap...
Input:           6 5 3 0 1 2
Pop element:     9
is_heap @ full:  true
*/
