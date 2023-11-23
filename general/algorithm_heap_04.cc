//
// Program
//  <algorithm> @ make_heap for a custom object.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o algorithm_heap_04 algorithm_heap_04.cc
//
// Execution
//  ./algorithm_heap_04
//

#include <algorithm>
#include <iostream>
#include <vector>

constexpr int size = 5;

struct pack {
  int ival;
  float fval;
};

static std::ostream& operator<< (std::ostream& out, const pack& p) {
  out << "{" << p.ival << "," << p.fval << "}";
  return out;
}

// Return true if lhs is smaller than rhs
struct Comparator {
  bool operator () (const pack &lhs, const pack &rhs) {
    return (lhs.fval < rhs.fval);
  }
};

//
// Entry function
//
int main() {

  std::cout <<"\n--- [make_heap] ---\n";
  {
    std::vector<pack> vec(size);
    for (int i = 0; i < size; ++i) {
      vec[i].ival = i + 1;
      vec[i].fval = i + 2.1f;
    }

    std::cout << "[Input]\n";
    for (const auto& item: vec) {
      std::cout << "  " << item << '\n';
    }

    std::cout << "is_heap:         " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end(), Comparator{})
                                     << '\n';

    std::cout << "Call make_heap...\n";

    // Arrange our vector into Max Heap arrangement
    std::make_heap(vec.begin(), vec.end(), Comparator{});

    std::cout << "[Input]\n";
    for (const auto& item: vec) {
      std::cout << "  " << item << '\n';
    }

    std::cout << "is_heap:         " << std::boolalpha
                                     << std::is_heap(vec.begin(), vec.end(), Comparator{})
                                     << '\n';
  }

  return 0;
}

/*
--- [make_heap] ---
[Input]
  {1,2.1}
  {2,3.1}
  {3,4.1}
  {4,5.1}
  {5,6.1}
is_heap:         false
Call make_heap...
[Input]
  {5,6.1}
  {4,5.1}
  {3,4.1}
  {1,2.1}
  {2,3.1}
is_heap:         true
*/
