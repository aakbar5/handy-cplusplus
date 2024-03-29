//
// Program
//  std::tuple usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o tuple-01 tuple-01.cc
//
// Execution
//  ./tuple-01
//

#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

struct object {
  object() {
    std::cout << "ctor" << '\n';
  }
  object(int) {
    std::cout << "ctor -- int" << '\n';
  }
  object(const object&) {
    std::cout << "copy ctor" << '\n';
  }
  object(object &&) noexcept  {
    std::cout << "move ctor" << '\n';
  }
  object& operator=(const object&) {
    std::cout << "=copy\n";
    return *this;
  }
  object& operator=(object&&)
  {
    std::cout << "=move\n";
    return *this;
  }
  ~object() {
    std::cout << "dtor" << '\n';
  }
};

//
// Entry function
//
int main() {
  std::cout << "---- std::tuple -----" << '\n';

  std::cout << "--- vector of objects (simple)\n";
  {
    object obj;
    std::vector<object> vec(2); // ctor of object will be called 2 times here
    vec.push_back(obj);
  }
  // 2 dtor will be called as vec goes out of scope

  std::cout << "--- vector of objects (object in pair)\n";
  {
    object obj;
    std::vector<std::pair<int, object>> vec(2); // ctor of object will be called 2 times
    vec[0] = {1, obj}; // copy ctor, =move
  }
  // 2 dtor will be called as vec goes out of scope

  std::cout << "--- vector of objects (object in pair -- emplace)\n";
  {
    std::vector<std::pair<int, object>> vec;
    vec.emplace_back(1, object{}); // ctor, move ctro
  }

  std::cout << "--- std::piecewise_construct\n";
  {
    {
      std::vector<std::pair<int, object>> vec;
      vec.emplace_back(1, object{}); // ctor, move ctor
      // vec.emplace_back(1, 2);
    }
    // dtor, dtor

    {
      std::vector<std::pair<int, object>> vec;
      vec.emplace_back(std::piecewise_construct,
                       std::forward_as_tuple(3),
                       std::forward_as_tuple()); // ctor
    }
    // dtor
  }

  std::cout << "--- struct with tuple in ctor\n";
  {
    struct Foo {
      Foo(int a, float b) {
        std::cout << "ctor (" << a << "," << b << ")\n";
      }
      Foo(std::tuple<int, float> t) {
        std::cout << "ctor tuple (" << std::get<0>(t)
                                    << "," << std::get<1>(t) << ")\n";
      }
      void show() {

      }
    };

    Foo a {2, 3.5f};
    a.show();

    std::tuple <int, float> tuple (10, 10.5f);
    Foo b (tuple);
    b.show();
  }

  std::cout << "--- std::apply to calculate sum of tuple elements\n";
  {
    std::tuple <int, float> t1 (10, 10.5f);
    auto add1 = [](int a, float b) {
      return a+b;
    };
    std::cout << "std::apply (2 params): " << std::apply(add1, t1) << '\n';

    std::tuple <int, int, float> t2 (10, 2, 10.5f);
    auto add2 = [](int a, int b, float c) {
      return a+b+c;
    };
    std::cout << "std::apply (3 params): " << std::apply(add2, t2) << '\n';
  }

  std::cout << "--- Iterate tuple elements\n";
  {
    std::tuple <int, float> t1 (10, 10.5f);
    auto size = std::tuple_size<decltype(t1)>::value;
    std::cout << "Size: " << size << std::endl;

    using telement = std::tuple_element<0, decltype(t1)>::type;
    telement a = 100.0f; // It won't be float as first element is of type int
    std::cout << "value: " << a << '\n';
  }

  return 0;
}
