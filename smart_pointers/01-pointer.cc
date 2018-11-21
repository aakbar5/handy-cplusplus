//
// Program
//  This program simply creates auto pointer.
//
// Compile
//  g++ -std=c++17 -o 01-pointer 01-pointer.cc
//
// Execution
//  ./01-pointer
//

#include <iostream>
#include <memory>

//
// Entry function
//
int main() {
  std::cout << "--- std::auto_ptr ---" << '\n';

  // Handling of Test object via shared pointer
  std::cout << "--- simple auto_pointer ---" << '\n';
  {
    std::auto_ptr<unsigned int> aptr(new unsigned int(786));
    std::cout << "aptr @ value: " << *aptr << '\n';

    {
      std::auto_ptr<unsigned int> wptr(aptr);

      *wptr.get() = 100;
      std::cout << "wptr > aptr @ value: " << *wptr << '\n';
    }

    // seg fault as ownership was wptr and
    // it has ended its life due to scoped rule
    std::cout << "aptr @ value: " << *aptr << '\n';
  }

  return 0;
}
