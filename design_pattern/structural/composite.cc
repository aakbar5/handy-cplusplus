//
// Design pattern # composite
// Composite pattern allows you to deal individual objects.
//
// g++ -std=c++17 -Wall -Wextra -o composite composite.cc
//
#include <iostream>
#include <vector>
#include <tuple>

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

struct Picture {
  void add(Shape *shape, Color *color) {
   objects.push_back(std::make_tuple(shape, color));
  }
  void draw() {
   std::cout << "Draw picture" << '\n';
   for (const auto &obj: objects) {
    std::get<0>(obj)->draw(std::get<1>(obj));
   }
  }
  std::vector<std::tuple<Shape *, Color *>> objects;
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # composite\n";

  Picture pic;
  pic.add(new Triangle(), new Red());
  pic.add(new Triangle(), new Green());
  pic.add(new Circle(), new Green());
  pic.add(new Circle(), new Red());
  pic.draw();

  return 0;
}
