//
// Design pattern # iterator
// Lets you iterator the object without exposing how it stored
//
// g++ -std=c++17 -Wall -Wextra -o iterator iterator.cc
//
#include <iostream>
#include <array>

constexpr int size = 3;

struct stack {
  std::array<int, size> vec;
  int curr = 0;
  bool is_empty() { return curr == 0; }
  bool is_full() { return curr == size; }
  void push(int num) {
    if (!is_full())
      vec[curr++] = num;
    else
      throw std::length_error("full");
  }
  int top() {
    if (!is_empty())
      return vec[curr - 1];

    throw std::out_of_range("nothing to pop");
  }
  int pop() {
    if (!is_empty()) {
      int ret = vec[curr - 1];
      --curr;
      return ret;
    }

    throw std::out_of_range("nothing to pop");
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # iterator\n";

  stack st;
  std::cout << "Full: " << std::boolalpha << st.is_full() << '\n';
  std::cout << "Empty: " << std::boolalpha << st.is_empty() << '\n';

  std::cout << "Push 2 elements\n";
  st.push(1);
  st.push(2);
  st.push(3);
  std::cout << "Full: " << std::boolalpha << st.is_full() << '\n';
  std::cout << "Empty: " << std::boolalpha << st.is_empty() << '\n';

  std::cout << "Pop 2 elements\n";
  st.pop();
  st.pop();
  std::cout << "Full: " << std::boolalpha << st.is_full() << '\n';
  std::cout << "Empty: " << std::boolalpha << st.is_empty() << '\n';

  return 0;
}
