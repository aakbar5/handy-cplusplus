//
// Design pattern # Abstract factory
// - A wrapper around the creation of object in a single call.
//
// g++ -std=c++17 -Wall -Wextra -o abstract_factory_v1 abstract_factory_v1.cc
//
#include <iostream>
#include <memory>

enum class Type {
  BLACK, LATTE
};

struct Coffee {
  virtual Type get_type() = 0;
  virtual void prepare() = 0;
};

struct BlackCoffee: Coffee {
private:
  Type type = Type::BLACK;
  friend class HotCoffeeFactory;

  // Keep it private to avoid creation of object outside the factory
  BlackCoffee() {}

public:
  Type get_type() override { return type; };
  void prepare() override {
    std::cout << "make coffee # black\n";
  }
};

struct LatteCoffee: Coffee {
private:
  Type type = Type::LATTE;
  friend class HotCoffeeFactory;

  // Keep it private to avoid creation of object outside the factory
  LatteCoffee() {}

public:
  Type get_type() override { return type; };
  void prepare() override {
    std::cout << "make coffee # latte\n";
  }
};

// A factory to create objects
struct AbstractFactory {
  virtual std::unique_ptr<Coffee> make(Type type) = 0;
};

struct HotCoffeeFactory: AbstractFactory {
  std::unique_ptr<Coffee> make(Type type) override {
    if (type == Type::BLACK)
      return std::unique_ptr<Coffee>(new BlackCoffee());
    else if (type == Type::LATTE)
      return std::unique_ptr<Coffee>(new LatteCoffee());

    return nullptr;
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # Abstract factory\n";

  auto factory = std::make_unique<HotCoffeeFactory>();
  auto obj1 = factory->make(Type::BLACK);
  obj1->prepare();

  auto obj2 = factory->make(Type::LATTE);
  obj2->prepare();

  return 0;
}
