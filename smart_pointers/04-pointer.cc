//
// Program
//  This program simply creates weak pointer.
//  - You can only create a std::weak_ptr out of a
//     std::shared_ptr or another std::weak_ptr.
//
// Compile
//  g++ -std=c++17 -o 04-pointer 04-pointer.cc
//
// Execution
//  ./04-pointer
//

#include <iostream>
#include <memory>

//
// Entry function
//
int main() {
  std::cout << "--- std::weak_ptr ---" << '\n';

  // Handling of Test object via shared pointer
  std::cout << "--- simple shared_pointer ---" << '\n';
  {
    std::shared_ptr<unsigned int> sptr = std::make_shared<unsigned int>(786);
    std::cout << "sptr @ use_count: " << sptr.use_count() << '\n'; // Use count should be 1
    std::cout << "sptr @ value: " << *sptr << '\n';

    {
      std::weak_ptr<unsigned int> wptr(sptr);
      std::cout << "wptr @ use_count: " << sptr.use_count() << '\n'; // Use count should be 1

      auto t = wptr.lock();
      std::cout << "wptr > sptr @ value: " << *t << '\n';
      std::cout << "wptr @ use_count: " << wptr.use_count() << '\n'; // Use count should be 2
      std::cout << "sptr @ use_count: " << sptr.use_count() << '\n'; // Use count should be 2

      *t = 100;
      std::cout << "wptr > sptr @ value: " << *t << '\n';
    }

    std::cout << "sptr @ use_count: " << sptr.use_count() << '\n'; // Use count should be 1
    std::cout << "sptr @ value: " << *sptr << '\n';

    // dtor should be called
  }

  return 0;
}
