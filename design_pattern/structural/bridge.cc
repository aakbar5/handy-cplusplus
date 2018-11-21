//
// Design pattern # bridge
// Implementation details of an object should have its own hierarchy
// so that both entities can be of independent of each other.
//
// g++ -std=c++17 -Wall -Wextra -o bridge bridge.cc
//
#include <iostream>

struct Color {
  virtual void draw() = 0;
};

struct Red: Color {
  void draw() override { std::cout << "Color: red" << std::endl; };
};

struct Green: Color {
  void draw() override { std::cout << "Color: green" << std::endl; };
};

struct Shape {
  virtual void draw(Color *color) = 0;
};

struct Triangle: Shape {
  void draw(Color *color) override {
    std::cout << "Shape: triangle" << std::endl;
    color->draw();
  }
};

struct Circle: Shape {
  void draw(Color *color) override {
    std::cout << "Shape: circle" << std::endl;
    color->draw();
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # bridge\n";

  Shape *shape = new Triangle();
  shape->draw(new Red());

  shape = new Circle();
  shape->draw(new Red());

  shape = new Circle();
  shape->draw(new Green());

  return 0;
}
