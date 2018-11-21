//
// Program
//  Random numbers: Generate random numbers using different
//  distribution (int + real).
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-random 01-random.cc
//
// Execution
//  ./01-random
//

#include <iostream>
#include <random>
#include <algorithm>

//
// Show numbers onto console
//
void show_numbers(const std::vector<int> &numbers) {
  for (int i = 0; i < 10; ++i) {
    std::cout << numbers[i] << " ";
  }
  std::cout << '\n';
}

//
// Entry function
//
int main() {
  {
    std::cout << "--- uniform_int_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::uniform_int_distribution<int> uid(10, 20);
    for (int i = 0; i < 10; ++i) {
      std::cout << uid(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- uniform_int_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::uniform_int_distribution<char> uid('a', 'z');
    for (int i = 0; i < 10; ++i) {
      std::cout << uid(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- std::shuffle @ uniform_int_distribution ---" << '\n';

    std::vector<int> numbers {};
    std::default_random_engine dre {};
    std::uniform_int_distribution<int> uid(10, 20);

    // Generate numbers
    for (int i = 0; i < 10; ++i) {
      numbers.push_back(uid(dre));
    }

    show_numbers(numbers);

    // Shuffle the above generate numbers
    std::shuffle(std::begin(numbers), std::end(numbers), dre);
    show_numbers(numbers);

    // Shuffle the above generate numbers
    std::shuffle(std::begin(numbers), std::end(numbers), dre);
    show_numbers(numbers);

    // Shuffle the above generate numbers
    std::shuffle(std::begin(numbers), std::end(numbers), dre);
    show_numbers(numbers);
  }

  {
    std::cout << "--- uniform_real_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::uniform_real_distribution<double> urd(10.0, 20.0);
    for (int i = 0; i < 10; ++i) {
      std::cout << urd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- discrete_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::discrete_distribution<int> dd(10, 20);
    for (int i = 0; i < 10; ++i) {
      std::cout << dd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- gamma_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::gamma_distribution<double> gd(10.0, 20.0);
    for (int i = 0; i < 10; ++i) {
      std::cout << gd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- binomial_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::binomial_distribution<int> bd(10, 20);
    for (int i = 0; i < 10; ++i) {
      std::cout << bd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- geometric_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::geometric_distribution<int> gd(0.3);
    for (int i = 0; i < 10; ++i) {
      std::cout << gd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- negative_binomial_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::negative_binomial_distribution<int> nbd(10, 20);
    for (int i = 0; i < 10; ++i) {
      std::cout << nbd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- poisson_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::poisson_distribution<int> pd(2.0);
    for (int i = 0; i < 10; ++i) {
      std::cout << pd(dre) << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "--- exponential_distribution ---" << '\n';
    std::default_random_engine dre {};
    std::exponential_distribution<double> pd(2.0);
    for (int i = 0; i < 10; ++i) {
      std::cout << pd(dre) << " ";
    }
    std::cout << '\n';
  }

  return 0;
}
