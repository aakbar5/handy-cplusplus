//
// Design pattern # singleton
// - To make sure that there is only one copy of the underlying
//   resource managed by the singleton.
//
// g++ -std=c++17 -Wall -Wextra -o singleton singleton.cc
//
#include <iostream>
#include <memory>

struct CoffeeMachine {
private:

  // Keep it private to avoid creation of object outside the get_instance
  CoffeeMachine() {}
  CoffeeMachine (const CoffeeMachine &) = delete;
  CoffeeMachine (const CoffeeMachine &&) = delete;
  CoffeeMachine& operator= (const CoffeeMachine) = delete;

public:
  static CoffeeMachine& get_instance() {
    static const auto ptr = std::unique_ptr<CoffeeMachine>(new CoffeeMachine());
    return *ptr;
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # singleton\n";

  CoffeeMachine& ptr1 = CoffeeMachine::get_instance();
  CoffeeMachine& ptr2 = CoffeeMachine::get_instance();

  std::cout << "Ptr1: " << &ptr1 << std::endl;
  std::cout << "Ptr2: " << &ptr2 << std::endl;

  if (&ptr1 == &ptr2)
    std::cout << "Both instances are equal\n";
  else
    std::cout << "Both instances are different\n";

  return 0;
}
