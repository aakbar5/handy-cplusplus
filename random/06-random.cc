//
// Program
//  Random numbers: Generate random numbers b/w different ranges as
//  per their defined weights linearly.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 06-random 06-random.cc
//
// Execution
//  ./06-random
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
    // -  1.0 <>  5.0 -> increase value linearly
    // -  5.0 <> 10.0 -> remains constant
    // - 10.0 <> 15.0 -> decrease value linearly
    std::vector<double> input {1.0, 5.0, 10.0, 15.0};
    std::vector<double> weight{0.0, 0.5,  0.5,  0.0};
    std::piecewise_linear_distribution<double> pcd(std::begin(input),
                                                   std::end(input),
                                                   std::begin(weight));

    for (int i = 0; i <= limit; ++i) {
      hist[pcd(mt)] += 1;
    }

    show_histogram("piecewise_linear_distribution with mt19937", hist);
  }

  return 0;
}
