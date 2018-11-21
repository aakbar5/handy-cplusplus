//
// Design pattern # prototype
// - A wrapper around the creation of object in a single call.
// - Hides the complexity of the object creation dynamically.
//
// g++ -std=c++17 -Wall -Wextra -o prototype prototype.cc
//
#include <iostream>
#include <memory>
#include <map>

enum class Type {
  BLACK, LATTE,
};

struct Coffee {
  virtual Type get_type() = 0;
  virtual void prepare() = 0;
  virtual std::unique_ptr<Coffee> clone() = 0;
};

struct BlackCoffee: Coffee {
private:
  Type type = Type::BLACK;

public:
  BlackCoffee() {}
  Type get_type() override { return type; };
  void prepare() override {
    std::cout << "make coffee # black\n";
  }

  std::unique_ptr<Coffee> clone() override {
    return std::unique_ptr<Coffee>(new BlackCoffee(*this));
  }
};

struct LatteCoffee: Coffee {
private:
  Type type = Type::LATTE;

public:
  LatteCoffee() {}
  Type get_type() override { return type; };
  void prepare() override {
    std::cout << "make coffee # latte\n";
  }
  std::unique_ptr<Coffee> clone() override {
    return std::unique_ptr<Coffee>(new LatteCoffee(*this));
  }
};

// A factory to clone objects
struct Prototype {
  virtual std::unique_ptr<Coffee> make_prototype(Type type) = 0;
};

struct PrototypeFactory: Prototype {
  std::map<Type, std::unique_ptr<Coffee>> factories;
  PrototypeFactory() {
    factories[Type::BLACK] = std::unique_ptr<Coffee>(new BlackCoffee());
    factories[Type::LATTE] = std::unique_ptr<Coffee>(new LatteCoffee());
  }

  std::unique_ptr<Coffee> make_prototype(Type type) {
    return factories[type]->clone();
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # prototype\n";

  auto prototype = std::make_unique<PrototypeFactory>();

  auto obj1 = std::unique_ptr<Coffee>(new BlackCoffee());
  auto obj2 = prototype->make_prototype(obj1->get_type());
  obj1->prepare();
  obj2->prepare();

  return 0;
}
