//
// Program
//  Containers: std::priority_queue usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 03-containers 03-containers.cc
//
// Execution
//  ./03-containers
//

#include <iostream>
#include <queue>
#include <functional>

//
// Entry function
//
int main() {
  // Simple priority_queue
  std::cout << "std::priority_queue ---" << '\n';
  {
    std::priority_queue<int> qu;
    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';

    // push elements now
    qu.push(50);
    qu.push(45);
    qu.push(65);
    qu.push(25);
    qu.push(10);
    qu.push(5);

    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';
    std::cout << "Top element: " << qu.top() << '\n';
  }

  // priority_queue with custom compare
  std::cout << "std::priority_queue with custom compare ---" << '\n';
  {
    std::priority_queue<int, std::vector<int>, std::greater<int>> qu;

    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';

    // push elements now
    qu.push(50);
    qu.push(45);
    qu.push(65);
    qu.push(25);
    qu.push(10);
    qu.push(5);

    std::cout << "Is empty: " << std::boolalpha << qu.empty() << '\n';
    std::cout << "Size: " << qu.size() << '\n';
    std::cout << "Top element: " << qu.top() << '\n';
  }

  return 0;
}
