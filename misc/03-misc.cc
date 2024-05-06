//
// Program
//  Generate lookup table at compile time
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 03-misc 03-misc.cc
//
// Execution
//  ./03-misc
//

#include <array>
#include <iostream>
#include <string>

bool is_special_char_via_lookup(const char& ch)
{
  constexpr std::array<bool, 256> lookup = []() {
    std::array<bool, 256> result {};
    for (char ch: {'+', '-', '*', '/', '%'}) {
      result [ch] = true;
    }
    return result;
  }();

  return lookup[ch];
}

bool is_special_char_via_simple(const char& ch)
{
  // Switch statement can be used too here
  if (ch == '+' || ch == '-' ||
      ch == '*' || ch == '/' ||
      ch == '%') {
    return true;
  }

  return false;
}

//
// Entry function
//
int main() {
  std::cout << "--- Lookup table ---" << '\n';

  const std::string input { "Hello + world / Welcome" };

  std::cout << "Plain:        ";
  for (const auto &ch: input) {
    if (is_special_char_via_simple(ch)) {
      std::cout << ch << ' ';
    }
  }
  std::cout << '\n';

  std::cout << "Lookup Table: ";
  for (const auto &ch: input) {
    if (is_special_char_via_lookup(ch)) {
      std::cout << ch << ' ';
    }
  }
  std::cout << '\n';


  return 0;
}

// Output
// --- Lookup table ---
// Plain:        + /
// Lookup Table: + /
