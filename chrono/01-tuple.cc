//
// Program
//  This program simply creates a thread and prints its ID.
//      - Create a thread
//      - Create a thread which accepts a parameter
//      - Create a thread whose callback is implemented by lambda
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-tuple 01-tuple.cc
//
// Execution
//  ./01-chrono
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
  std::cout << "std::tuple \n";

  // {
  //   object obj1;
  //   std::vector<object> vec(5); // 5 ctor will be called
  //   // vec.push_back(obj1);
  // }
  // // 5 dtor will be called as vec goes out of scope

  // {
  //   object obj1;
  //   std::vector<std::pair<int, object>> vec(2); // 5 ctor will be called
  //   vec[0] = {1, obj1}; // copy ctor, =move
  // }

  // {
  //   std::vector<std::pair<int, object>> vec; // 5 ctor will be called
  //   vec.emplace_back(1, object{}); // ctor, move ctro
  // }

    {
      {
        std::vector<std::pair<int, object>> vec;
        vec.emplace_back(1, object{});
        // vec.emplace_back(1, 2);
      }

      // {
      //   std::vector<std::pair<int, object>> vec;
      //   vec.emplace_back(std::piecewise_construct,
      //                    std::forward_as_tuple(3), std::forward_as_tuple());
      // }
    }

  // {
  //   struct Foo {
  //     Foo(int a, float b) {
  //       std::cout << "ctor (" << a << "," << b << ")\n";
  //     }
  //     Foo(std::tuple<int, float> t) {
  //       std::cout << "ctor tuple (" << std::get<0>(t)
  //                                   << "," << std::get<1>(t) << ")\n";
  //     }
  //   };

  //   Foo a = Foo(2, 3.5f);
  //   std::tuple <int, float> tuple (10, 10.5f);
  //   Foo b = Foo(tuple);
  //   Foo c = Foo(std::piecewise_construct, tuple);

  //   (void)a;
  //   (void)b;
  //   (void)c;
  // }

  return 0;
}
