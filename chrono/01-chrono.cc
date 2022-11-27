//
// Program
//  Calculate elapsed time.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-chrono 01-chrono.cc
//
// Execution
//  ./01-chrono
//

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

//
// Entry function
//
int main() {
  std::cout << "--- Calculate elapsed time ---" << '\n';

  std::cout << "Sleep for a while..." << '\n';
  auto start = std::chrono::high_resolution_clock::now();
  {
    std::this_thread::sleep_for(5s);
  }
  auto end = std::chrono::high_resolution_clock::now();

  /* Method # 1 use duration_cast to calcaulate elapsed time */
  {
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto sc = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << " Elapsed time (duration_cast - ns) # " << ns.count() << " nsec" << '\n';
    std::cout << " Elapsed time (duration_cast - us) # " << us.count() << " usec" << '\n';
    std::cout << " Elapsed time (duration_cast - ms) # " << ms.count() << " msec" << '\n';
    std::cout << " Elapsed time (duration_cast - sc) # " << sc.count() << " sec" << '\n';
  }

  /* Method # 2 use duration and ratio to calculate elapsed time */
  {
    std::chrono::duration<double, std::nano> ns = end - start;
    std::chrono::duration<double, std::micro> us = end - start;
    std::chrono::duration<double, std::milli> ms = end - start;
    std::chrono::duration<double, std::deci> sc = end - start;

    std::cout << " Elapsed time (duration - ns)      # " << std::setprecision(5) << ns.count() << " nsec" << '\n';
    std::cout << " Elapsed time (duration - us)      # " << std::setprecision(5) << us.count() << " usec" << '\n';
    std::cout << " Elapsed time (duration - ms)      # " << std::setprecision(5) << ms.count() << " msec" << '\n';
    std::cout << " Elapsed time (duration - sc)      # " << std::setprecision(5) << sc.count() << " sec" << '\n';
  }

  return 0;
}
