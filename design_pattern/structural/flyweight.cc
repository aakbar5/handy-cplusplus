//
// Design pattern # fly weight
// Flyweight pattern is used to reduce the number of
// objects created.
//
// g++ -std=c++17 -Wall -Wextra -o flyweight flyweight.cc
//
#include <iostream>
#include <unordered_map>

struct Shape {
  virtual std::string name() = 0;
  virtual void draw() = 0;
};

struct Circle: Shape {
  std::string name() override { return "Shape -> Circle"; }
  void draw() override { std::cout << "Draw # " << name() << '\n'; }
};

struct Rectangle: Shape {
  std::string name() override { return "Shape -> Rectangle"; }
  void draw() override { std::cout << "Draw # " << name() << '\n'; }
};

struct Square: Shape {
  std::string name() override { return "Shape -> Square"; }
  void draw() override { std::cout << "Draw # " << name() << '\n'; }
};

struct Flyweight {
  enum class Type {
    Circle,
    Rectangle,
    Square
  };
  std::unordered_map<Flyweight::Type, Shape*> map;

  Shape* get(Flyweight::Type type) {
    Shape *sh = map[type];
    if (!sh) {
      if (type == Type::Circle)
        sh = new Circle();
      else if (type == Type::Rectangle)
        sh = new Rectangle();
      else if (type == Type::Square)
        sh = new Square();

      map[type] = sh;
    }

    return sh;
  }

  void show() {
    std::cout << "Available objects: \n";
    for(const std::pair<const Flyweight::Type, Shape *> n: map) {
      std::cout << "  " << n.second->name() << '\n';
    }
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # flyweight\n";

  Flyweight fw;

  Shape *s = fw.get(Flyweight::Type::Circle);
  s->draw();

  s = fw.get(Flyweight::Type::Square);
  s->draw();

  fw.show();

  s = fw.get(Flyweight::Type::Square);
  s->draw();

  return 0;
}
