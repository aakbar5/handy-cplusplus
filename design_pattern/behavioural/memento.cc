//
// Design pattern # memento
//  Let's you save state of the object which can be
//  retored later on.
//
// g++ -std=c++17 -Wall -Wextra -o memento memento.cc
//
#include <iostream>

struct Memento {
  virtual void save() = 0;
  virtual void restore() = 0;
};


struct Object: Memento {
  void save() { std::cout << "serialize object...\n"; };
  void restore() { std::cout << "de-serialize object...\n"; };
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # memento\n";

  Object obj;
  obj.save();
  obj.restore();

  return 0;
}
