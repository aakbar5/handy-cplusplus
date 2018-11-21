//
// Program
//  Random numbers: Generate random numbers b/w different ranges as
//  per their defined weights.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 05-random 05-random.cc
//
// Execution
//  ./05-random
//

#include <iostream>
#include <random>
#include <algorithm>
#include <map>
#include <iomanip>

constexpr int scale =   1000;
constexpr int limit = 100000;

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

    //
    // As per weight, we are looking following distribution of our rand numbers:
    // -  1.0 <>  5.0 -> 10000
    // -  5.0 <> 10.0 -> 40000
    // - 10.0 <> 15.0 -> 50000
    std::vector<double> input {1.0, 5.0, 10.0, 15.0};
    std::vector<double> weight{   0.1, 0.4,  0.5  };
    std::piecewise_constant_distribution<double> pcd(std::begin(input),
                                                      std::end(input),
                                                      std::begin(weight));

    for (int i = 0; i <= limit; ++i) {
      hist[pcd(mt)] += 1;
    }

    show_histogram("piecewise_constant_distribution with mt19937", hist);
  }

  return 0;
}
