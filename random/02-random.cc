//
// Program
//  Random numbers: Generate random numbers for uniform integer
//  distribution by using different random engines.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 02-random 02-random.cc
//
// Execution
//  ./02-random
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
    std::default_random_engine dre {};
    std::uniform_int_distribution<int> uid(1, 5);
    for (int i = 0; i < limit; ++i) {
      hist[uid(dre)] += 1;
    }

    show_histogram("uniform_int_distribution with random_engine", hist);
  }

  {
    std::map<int, int> hist{};
    std::random_device rd {};
    std::uniform_int_distribution<int> uid(1, 5);
    for (int i = 0; i < limit; ++i) {
      hist[uid(rd)] += 1;
    }

    show_histogram("uniform_int_distribution with random_device", hist);
  }

  {
    std::map<int, int> hist{};
    std::knuth_b kb {};
    std::uniform_int_distribution<int> uid(1, 5);
    for (int i = 0; i < limit; ++i) {
      hist[uid(kb)] += 1;
    }

    show_histogram("uniform_int_distribution with knuth_b", hist);
  }

  return 0;
}
