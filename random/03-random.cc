//
// Program
//  Random numbers: Generate random numbers for uniform integer
//  distribution using Mersenne twister.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 03-random 03-random.cc
//
// Execution
//  ./03-random
//

#include <iostream>
#include <random>
#include <algorithm>
#include <map>
#include <iomanip>

constexpr int scale =   1000;
constexpr int limit = 100000;

//
// Show historgram
//
static void show_histogram(const std::string& title, const std::map<int, int> &hist) {
  std::cout << "--- " << title << " ---" << '\n';
  for (auto item: hist) {
    std::cout << " " << std::setw(2) << item.first << " " << std::string(item.second/scale, '*') << '\n';
  }
}

//
// Entry function
//
int main() {
  {
    std::map<int, int> hist{};
    std::random_device rd {};
    std::mt19937 mt(rd()); // Get seed from random_device
    std::uniform_int_distribution<int> uid(1, 5);
    for (int i = 0; i <= limit; ++i) {
      hist[uid(mt)] += 1;
    }

    show_histogram("uniform_int_distribution with mt19937", hist);
  }

  {
    std::map<int, int> hist{};
    std::random_device rd {};
    std::mt19937_64 mt64(rd()); // Get seed from random_device
    std::uniform_int_distribution<int> uid(1, 5);
    for (int i = 0; i < limit; ++i) {
      hist[uid(mt64)] += 1;
    }

    show_histogram("uniform_int_distribution with mt19937_64", hist);
  }

  return 0;
}
