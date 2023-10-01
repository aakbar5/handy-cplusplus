//
// Program
//  Containers: std::priority_queue usage
//   - Simple priority_queue
//   - priority_queue with custom compare
//   - priority_queue for a custom object
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
#include <cassert>

//
// Entry function
//
int main() {
  // Simple priority_queue
  std::cout << "std::priority_queue ---" << '\n';
  {
    std::priority_queue<int> pq;
    std::cout << "Is empty: " << std::boolalpha << pq.empty() << '\n';
    std::cout << "Size: " << pq.size() << '\n';

    assert(true == pq.empty());
    assert(0 == pq.size());

    // push elements now
    pq.push(50);
    pq.push(45);
    pq.push(65);
    pq.push(25);
    pq.push(10);
    pq.push(5);

    std::cout << "Is empty: " << std::boolalpha << pq.empty() << '\n';
    std::cout << "Size: " << pq.size() << '\n';
    std::cout << "Top element: " << pq.top() << '\n';

    assert(false == pq.empty());
    assert(6 == pq.size());
    assert(65 == pq.top());
  }

  // priority_queue with custom compare
  std::cout << "std::priority_queue with custom compare ---" << '\n';
  {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    std::cout << "Is empty: " << std::boolalpha << pq.empty() << '\n';
    std::cout << "Size: " << pq.size() << '\n';

    assert(true == pq.empty());
    assert(0 == pq.size());

    // push elements now
    pq.push(50);
    pq.push(45);
    pq.push(65);
    pq.push(25);
    pq.push(10);
    pq.push(5);

    std::cout << "Is empty: " << std::boolalpha << pq.empty() << '\n';
    std::cout << "Size: " << pq.size() << '\n';
    std::cout << "Top element: " << pq.top() << '\n';

    assert(false == pq.empty());
    assert(6 == pq.size());
  }

  // priority_queue for a custom object
  std::cout << "std::priority_queue for a custom object ---" << '\n';
  {
    struct pack {
      std::string name;
      uint32_t val;
    };

    struct Comparator {
      bool operator () (const pack &lhs, const pack &rhs) {
        return (lhs.val < rhs.val);
      }
    };

    // Define custom type of priority_queue
    using priority_queue = std::priority_queue<pack, std::vector<pack>, Comparator>;

    // Push elements
    priority_queue pq;
    pq.push({"value2", 2});
    pq.push({"value3", 3});
    pq.push({"value4", 4});
    pq.push({"value1", 1});
    pq.push({"value0", 0});

    std::cout << "Is empty: " << std::boolalpha << pq.empty() << '\n';
    std::cout << "Size: " << pq.size() << '\n';
    std::cout << "Top element: " << "{" << pq.top().name << "," << pq.top().val << "}" << '\n';

    assert(false == pq.empty());
    assert(5 == pq.size());
    assert(4 == pq.top().val);
  }

  return 0;
}
