//
// Program
//  Containers: std::stack usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-containers 01-containers.cc
//
// Execution
//  ./01-containers
//

#include <iostream>
#include <stack>

// std::stack does not expose iterator so it
// has been extended to expose iterator
template <typename T>
class my_stack : public std::stack<T> {
public:
  auto begin() { return this->c.begin(); }
  auto end() { return this->c.end(); }
};

//
// Entry function
//
int main() {
  // Simple stack
  std::cout << "std::stack ---" << '\n';
  {
    std::stack<int> st;
    std::cout << "Is empty: " << std::boolalpha << st.empty() << '\n';
    std::cout << "Size: " << st.size() << '\n';

    // push elements now
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(40);
    st.push(50);
    std::cout << "Is empty: " << std::boolalpha << st.empty() << '\n';
    std::cout << "Size: " << st.size() << '\n';

    std::cout << "Top element: " << st.top() << '\n';
  }

  // Show all elements of stack without removing elements
  std::cout << "custom stack ---" << '\n';
  {
    my_stack<char> st;
    st.push('a');
    st.push('b');
    st.push('c');
    st.push('d');
    st.push('e');
    st.push('f');

    std::cout << "Is empty: " << std::boolalpha << st.empty() << '\n';
    std::cout << "Size: " << st.size() << '\n';
    std::cout << "Top element: " << st.top() << '\n';

    for (auto &item: st) {
      std::cout << item << '\n';
    }
  }

  return 0;
}
