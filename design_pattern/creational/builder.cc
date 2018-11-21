//
// Design pattern # builder
// - A wrapper to outsource the piecewise construction of
//   an object into a separate class.
//
// g++ -std=c++17 -Wall -Wextra -o builder builder.cc
//
#include <iostream>
#include <memory>
#include <vector>

enum class Type {
  BLACK,
};

enum class Sweet {
  HONEY, SUGAR_WHITE, SUGAR_BROWN
};

enum class Espresso {
  BRAND_A, BRAND_B, BRAND_C
};

struct Coffee {
  virtual Type get_type() = 0;
  virtual void prepare() = 0;
};

struct BlackCoffee: Coffee {
private:
  Type type = Type::BLACK;
  Sweet sweet_;
  bool cinnamon_;
  Espresso brand_;
  int temperature_;

public:
  BlackCoffee(Sweet sweet, bool cinnamon, Espresso brand, int temperature):
                        sweet_(sweet),
                        cinnamon_(cinnamon),
                        brand_(brand),
                        temperature_(temperature) {
  }
  Type get_type() override { return type; };
  void prepare() override {
    const std::vector<std::string> brand_string {"Brand A", "Brand B", "Brand C"};
    const std::vector<std::string> sweet_string {"Honey", "Sugar White", "Sugar Brown"};

    std::cout << "make coffee # black\n";
    std::cout << " - Add # " << brand_string.at(static_cast<int>(sweet_)) << '\n';
    std::cout << " - Add # cinnamon " << std::boolalpha << cinnamon_ << '\n';
    std::cout << " - Espresso # " << sweet_string.at(static_cast<int>(brand_)) << '\n';
    std::cout << " - Temperature # " << temperature_ << '\n';
  }
};

struct BlackCoffeeBuilder {
  Sweet sweet_;
  bool cinnamon_;
  Espresso brand_;
  int temperature_;

  BlackCoffeeBuilder(): sweet_(Sweet::SUGAR_BROWN),
                        cinnamon_(false),
                        brand_(Espresso::BRAND_A),
                        temperature_(195) {
  }
  void add_sweet(Sweet sweet) {
    sweet_ = sweet;
  }
  void select_cinnamon(bool cinnamon) {
    cinnamon_ = cinnamon;
  }
  void select_espresso(Espresso brand) {
    brand_ = brand;
  }
  void select_temperature(int temperature) {
    // 195°F and 205°F
    temperature_ = temperature;
  }

  std::unique_ptr<Coffee> make() {
    BlackCoffee *coffee  = new BlackCoffee(sweet_, cinnamon_, brand_, temperature_);
    return std::unique_ptr<Coffee>(coffee);
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # builder\n";

  {
    BlackCoffeeBuilder builder = BlackCoffeeBuilder {};
    auto coffee = builder.make();
    coffee->prepare();
  }

  {
    BlackCoffeeBuilder builder = BlackCoffeeBuilder {};
    builder.select_cinnamon(true);
    builder.select_temperature(201);
    auto coffee = builder.make();
    coffee->prepare();
  }

  return 0;
}
