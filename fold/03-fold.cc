//
// Program
//  Fold expression: Misc usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 03-fold 03-fold.cc
//
// Execution
//  ./03-fold
//

#include <iostream>
#include <vector>

// Calculate average of the passed numbers
template<typename ... Args>
auto average(Args&&... args) {
  return (args + ... + 0) / sizeof...(args);
}

// Validate numbers are allNonZero
template<typename ... Args>
bool allNonZero(Args&&... args) {
  return (args && ...);
}

// Validate numbers are allNonZero
template<typename ... Args>
bool anyNonZero(Args&&... args) {
  return (args || ...);
}

// Push elements to std::vector
template<typename Type, typename ... Args>
void push(std::vector<Type>& vec, Args&&... args) {
  (vec.push_back(std::forward<Args>(args)), ...);
}

// Check all elements are equal to the first one
template<typename Type, typename ... Args>
bool equal(const Type& val, const Args&... args) {
  return ((val == args) && ...);
}

// Check all elements are greather than the first one
template<typename Type, typename ... Args>
bool gt(const Type& val, const Args&... args) {
  return ((val > args) && ...);
}

// Check all elements are in the range
template<typename Type, typename ... Args>
bool within_range(const Type& min, const Type& max, const Args&... args) {
  return ((args >= min && args <= max) && ...);
}

// Check all elements are even
template<typename ... Args>
bool allEven(const Args&... args) {
  auto func = [&](auto& x) {return (x % 2 == 0);};
  return (func(args) && ... );
}

// Check string is having required all characters
template<typename ... Args>
bool contains(const std::string& input, const Args&... args) {
  auto func = [&](std::string input, auto x) {return (input.find(x) != std::string::npos);};
  return (func(input, args) && ... );
}

//
// Entry function
//
int main() {
  std::cout << "average(2, 4, 6) = " << average(2, 4, 6) << '\n'; // ans should be 5

  std::cout << "allNonZero(2, 4, 6) = " << std::boolalpha << allNonZero(2, 4, 6) << '\n'; // ans should be true
  std::cout << "allNonZero(0, 4, 6) = " << std::boolalpha << allNonZero(0, 4, 6) << '\n'; // ans should be false

  std::cout << "anyNonZero(2, 4, 6) = " << std::boolalpha << anyNonZero(2, 4, 6) << '\n'; // ans should be true
  std::cout << "anyNonZero(0, 4, 6) = " << std::boolalpha << anyNonZero(0, 4, 6) << '\n'; // ans should be true
  std::cout << "anyNonZero(0, 0, 0) = " << std::boolalpha << anyNonZero(0, 0, 0) << '\n'; // ans should be false

  std::vector<int> vec;
  std::cout <<"Vector size (Before): " << vec.size() << '\n';
  push<int>(vec, 1,2,3,4,5);
  std::cout <<"Vector size (After): " << vec.size() << '\n';

  std::cout << "equal(0, 0, 0) = " << std::boolalpha << equal(0, 0, 0) << '\n';
  std::cout << "equal(0, 1, 2) = " << std::boolalpha << equal(0, 1, 2) << '\n';
  std::cout << "equal(5, 6, 7) = " << std::boolalpha << equal(5, 6, 7) << '\n';
  std::cout << "equal(8, 8, 8) = " << std::boolalpha << equal(8, 8, 8) << '\n';

  std::cout << "gt(0, 0, 0) = " << std::boolalpha << gt(0, 0, 0) << '\n';
  std::cout << "gt(2, 1, 0) = " << std::boolalpha << gt(2, 1, 0) << '\n';
  std::cout << "gt(7, 6, 5) = " << std::boolalpha << gt(7, 6, 5) << '\n';
  std::cout << "gt(2, 9, 8) = " << std::boolalpha << gt(2, 9, 8) << '\n';

  std::cout << "within_range(5, 10, 6, 7, 8, 9)  = " << std::boolalpha << within_range(5, 10, 6, 7, 8, 9) << '\n';
  std::cout << "within_range(5, 10, 6, 7, 8, 11) = " << std::boolalpha << within_range(5, 10, 6, 7, 8, 11) << '\n';

  std::cout << "allEven(2, 4) = " << std::boolalpha << allEven(2, 4) << '\n';
  std::cout << "allEven(2, 4, 6) = " << std::boolalpha << allEven(2, 4, 6) << '\n';
  std::cout << "allEven(1, 4, 6) = " << std::boolalpha << allEven(1, 4, 6) << '\n';

  std::cout << "contains: " << std::boolalpha << contains("test", 't', 'e') << '\n';
  std::cout << "contains: " << std::boolalpha << contains("test", 'z', 'x') << '\n';

  return 0;
}
