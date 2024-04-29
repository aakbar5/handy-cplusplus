//
// Program
//  Container usage of reserve, size and capacity.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 11-containers 11-containers.cc
//
// Execution
//  ./11-containers
//

#include <iostream>
#include <vector>

//
// Entry function
//
int main() {

  // NOTE:
  // - size() function is showing real count of the elements pushed to the container
  // - reserve() changes container capacity not size
  // - A number passed to ctor will change its capaticty not the size

  {
    std::cout << "--- Container default init --- \n";

    std::vector<int> vec {};
    std::cout << "  Size: " << vec.size() << '\n';          // Output: 0
    std::cout << "  Capacity: " << vec.capacity() << '\n';  // Output: 0

    std::cout << " --- push_back an element\n";
    vec.push_back(10);
    std::cout << "  Size: " << vec.size() << '\n';          // Output: 1
    std::cout << "  Capacity: " << vec.capacity() << '\n';  // OUtput: 1
  }

  {
    std::cout << "--- Container initialized with a size --- \n";

    std::vector<int> vec (10);
    std::cout << "  Size: " << vec.size() << '\n';          // Output: 10
    std::cout << "  Capacity: " << vec.capacity() << '\n';  // Output: 10

    std::cout << " --- push_back an element\n";
    vec.push_back(10);
    std::cout << "  Size: " << vec.size() << '\n';          // Output: 11
    std::cout << "  Capacity: " << vec.capacity() << '\n';  // Output: 20
  }

  {
    std::cout << "--- Container default init --- \n";

    std::vector<int> vec {};
    std::cout << " Size: " << vec.size() << '\n';            // Output: 0
    std::cout << " Capacity: " << vec.capacity() << '\n';    // Output: 0

    std::cout << " --- Call reserve\n";
    vec.reserve(10);
    std::cout << " Size: " << vec.size() << '\n';           // Output: 0
    std::cout << " Capacity: " << vec.capacity() << '\n';   // Output: 10

    std::cout << " --- push_back an element\n";
    vec.push_back(10);
    std::cout << "Size: " << vec.size() << '\n';            // Output: 1
    std::cout << "Capacity: " << vec.capacity() << '\n';    // Output: 10
  }

  return 0;
}
