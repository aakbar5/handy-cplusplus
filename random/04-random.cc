//
// Program
//  Random numbers: Generate random numbers using std::discrete_distribution.
//  It produces random integers on the interval [0, n), where the probability of
//  each individual integer i is defined as w i/S, that is the weight of the ith
//  integer divided by the sum of all n weights.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 04-random 04-random.cc
//
// Execution
//  ./04-random
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
    std::cout << " " << std::setw(2) << item.first << " "
              << std::string(item.second/scale, '*')
              << " (" << item.second << " times)"
              << '\n';
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
    std::discrete_distribution<int> uid({50, 25, 25}); // 1 should be 50%
    for (int i = 0; i <= limit; ++i) {
      hist[uid(mt)] += 1;
    }

    show_histogram("discrete_distribution with mt19937", hist);
  }

  return 0;
}
