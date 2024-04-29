//
// Program
//  std::unordered_map with custom hash
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 08-containers 08-containers.cc
//
// Execution
//  ./08-containers
//

#include <iostream>
#include <unordered_set>
#include <cassert>

//
// Entry function
//
int main() {

  std::cout << "unordered_set<std::string> ---" << '\n';
  {
    std::unordered_set<std::string> m;

    m.insert("entry1");
    m.insert("entry2");

    std::cout << "Show items of the std::unordered_set " << m.size() << '\n';
    for (const auto& item: m) {
      std::cout << item << '\n';
    }
  }

  std::cout << "unordered_set<struct> ---" << '\n';
  {
    enum class Color: uint8_t {
      RED,
      GREEN,
      BLUE,
    };

    auto to_string = [](Color p) {
           if (static_cast<uint8_t>(p) == static_cast<uint8_t>(Color::RED))     return "Red";
      else if (static_cast<uint8_t>(p) == static_cast<uint8_t>(Color::GREEN))   return "Green";
      else if (static_cast<uint8_t>(p) == static_cast<uint8_t>(Color::BLUE))    return "Blue";
      return "Unknown";
    };

    struct Pixel {
      uint32_t idx;
      Color col;

      Pixel(uint32_t i, Color c) {
        idx = i;
        col = c;
      }

      bool operator==(const Pixel& pix) const {
        return ((pix.idx == idx) && (pix.col == col));
      }
    };

    struct KeyHash {
      std::size_t operator()(const Pixel& pix) const {
        return (size_t)pix.idx ^ static_cast<uint8_t>(pix.col);
      };
    };

    std::unordered_set<Pixel, KeyHash> m {
      {1, Color::RED},
      {2, Color::GREEN},
      {3, Color::BLUE},
      {3, Color::RED},
    };

    assert(m.size() == 4);
    m.insert({3, Color::RED});
    assert(m.size() == 4);

    std::cout << "Show items of the std::unordered_set " << m.size() << '\n';
    for (const auto& item: m) {
      std::cout << "{" << item.idx << "," << to_string(item.col) << "}\n";
    }
  }

  return 0;
}

// Output
// unordered_set<std::string> ---
// Show items of the std::unordered_set 2
// entry2
// entry1
// unordered_set<struct> ---
// Show items of the std::unordered_set 4
// {3,Red}
// {2,Green}
// {3,Blue}
// {1,Red}
