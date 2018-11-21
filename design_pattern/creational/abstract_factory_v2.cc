//
// Design pattern # Abstract factory
// - A wrapper around the creation of object in a single call.
//
// g++ -std=c++17 -Wall -Wextra -o abstract_factory_v2 abstract_factory_v2.cc
//
#include <iostream>
#include <memory>
#include <map>

enum class Type {
  BLACK, LATTE, ICED, ICED_ESPRESSO,
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

struct IcedCoffee: Coffee {
private:
  Type type = Type::ICED;
  friend class ColdCoffeeFactory;

  // Keep it private to avoid creation of object outside the factory
  IcedCoffee() {}

public:
  Type get_type() override { return type; };
  void prepare() override {
    std::cout << "make coffee # iced\n";
  }
};

struct IcedEspressoCoffee: Coffee {
private:
  Type type = Type::ICED_ESPRESSO;
  friend class ColdCoffeeFactory;

  // Keep it private to avoid creation of object outside the factory
  IcedEspressoCoffee() {}

public:
  Type get_type() override { return type; };
  void prepare() override {
    std::cout << "make coffee # iced espresso\n";
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

struct ColdCoffeeFactory: AbstractFactory {
  std::unique_ptr<Coffee> make(Type type) override {
    if (type == Type::ICED)
      return std::unique_ptr<Coffee>(new IcedCoffee());
    else if (type == Type::ICED_ESPRESSO)
      return std::unique_ptr<Coffee>(new IcedEspressoCoffee());

    return nullptr;
  }
};

struct CoffeeFactory {
  std::map<Type, std::unique_ptr<AbstractFactory>> factories;
  CoffeeFactory() {
    factories[Type::BLACK] = std::make_unique<HotCoffeeFactory>();
    factories[Type::LATTE] = std::make_unique<HotCoffeeFactory>();
    factories[Type::ICED] = std::make_unique<ColdCoffeeFactory>();
    factories[Type::ICED_ESPRESSO] = std::make_unique<ColdCoffeeFactory>();
  }

  std::unique_ptr<Coffee> make_coffee(Type type) {
    return factories[type]->make(type);
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # Abstract factory\n";

  auto factory = std::make_unique<CoffeeFactory>();
  auto cpu1 = factory->make_coffee(Type::BLACK);
  cpu1->prepare();

  return 0;
}
