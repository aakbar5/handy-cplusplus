//
// Design pattern # visitor
//  Lets you add new functionality without changing existing interface.
//
// g++ -std=c++17 -Wall -Wextra -o visitor visitor.cc
//
#include <iostream>

// Forward declaration
struct Cat;
struct Dog;

// Visitor design pattern
struct Visitor {
  virtual void call_cat(Cat *cat) = 0;
  virtual void call_dog(Dog *dog) = 0;
};

struct Animal {
  virtual std::string name() = 0;
  void do_it(Visitor *visitor);
};

struct Cat: Animal {
  std::string name() { return "Cat"; }
  void do_it(Visitor *visitor) { visitor->call_cat(this); }
};

struct Dog: Animal {
  std::string name() { return "Dog"; }
  void do_it(Visitor *visitor) { visitor->call_dog(this); }
};

struct Sound: Visitor {
  void call_cat(Cat *cat)
  {
    std::cout << cat << " # It is cat\n";
  }

  void call_dog(Dog *dog)
  {
    std::cout << dog << " # It is dog\n";
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # visitor\n";

  Dog dog;
  Sound sound;
  dog.do_it(&sound);

  return 0;
}
