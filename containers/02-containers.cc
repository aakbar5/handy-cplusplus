//
// Program
//  Containers: std::queue usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 02-containers 02-containers.cc
//
// Execution
//  ./02-containers
//

#include <iostream>
#include <queue>

// std::stack does not expose iterator so it
// has been extended to expose iterator
template <typename T>
class my_queue : public std::queue<T> {
public:
  auto begin() { return this->c.begin(); }
  auto end() { return this->c.end(); }
};

//
// Entry function
//
int main() {
  // Simple queue
  std::cout << "std::queue ---" << '\n';
  {
    std::queue<char> qu;
    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';

    // push elements now
    qu.push('a');
    qu.push('b');
    qu.push('c');
    qu.push('d');
    qu.push('e');
    qu.push('f');

    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';

    std::cout << "Front element: " << qu.front() << '\n';
    std::cout << "Back element: " << qu.back() << '\n';
  }

  // Show all elements of queue without removing elements
  std::cout << "custom queue ---" << '\n';
  {
    my_queue<char> qu;
    qu.push('a');
    qu.push('b');
    qu.push('c');
    qu.push('d');
    qu.push('e');
    qu.push('f');

    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';

    std::cout << "Front element: " << qu.front() << '\n';
    std::cout << "Back element: " << qu.back() << '\n';

    for (auto &item: qu) {
      std::cout << item << '\n';
    }
  }

  return 0;
}
