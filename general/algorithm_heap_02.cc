//
// Program
//  <algorithm> @ push_heap
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o algorithm_heap_02 algorithm_heap_02.cc
//
// Execution
//  ./algorithm_heap_02
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

  std::cout <<"\n--- [push_heap] ---\n";
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

    // push an element
    // Technically push_heap should push an element
    // by keeping the heap state so you don't have
    // to call separate push_heap or make_heap call
    std::cout << "Push an element..\n";
    vec.push_back(15);

    // Our heap property is false now
    std::cout << "is_heap @ full    (push):  " << std::boolalpha
                                               << std::is_heap(vec.begin(), vec.end())
                                               << '\n';
    std::cout << "is_heap @ len - 1 (push):  " << std::boolalpha
                                               << std::is_heap(vec.begin(), vec.end() - 1)
                                               << '\n';

    // Only last element is not following max heap property
    // we can make_heap or push_heap to make sure that
    // our vector is of the correct property

    std::cout << "Call push_heap...\n";
    std::push_heap(vec.begin(), vec.end());
    std::cout << "is_heap @ full    (push):  " << std::boolalpha
                                               << std::is_heap(vec.begin(), vec.end())
                                               << '\n';
    std::cout << "is_heap @ len - 1 (push):  " << std::boolalpha
                                               << std::is_heap(vec.begin(), vec.end() - 1)
                                               << '\n';
  }

  return 0;
}

/*
--- [push_heap] ---
Input:           2 5 3 6 1 9 0
is_heap:         false
After make_heap: 9 6 3 5 1 2 0
is_heap:         true
Push an element..
is_heap @ full    (push):  false
is_heap @ len - 1 (push):  true
Call push_heap...
is_heap @ full    (push):  true
is_heap @ len - 1 (push):  true
*/
