//
// Program
//  Calculate elapsed time using a generic function.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 02-chrono 02-chrono.cc
//
// Execution
//  ./02-chrono
//

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

using namespace std::chrono_literals;

// Sample test function (input: no parameter)
void fun1(void) {
  std::this_thread::sleep_for(1s);
}

// Sample test function (input: input parameters)
void fun2(int x, int y) {
  int z = x + y;
  std::this_thread::sleep_for(2s);
  (void)z;
}

// Template based function to measure the time consumed
// by the user function
template <typename Units = std::chrono::nanoseconds>
struct Timer {
  template <typename F, typename... Args>
  static Units measure(F func, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    {
      std::invoke(func, std::forward<Args>(args)...);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<Units>(end - start);
  }
};

int main() {
  std::cout << "--- Calculate elapsed time ---" << '\n';

  {
    std::cout << "--- Measure time (simplified version) ---" << '\n';
    std::cout << "Sleep for a while..." << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    {
      std::this_thread::sleep_for(1s);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto sc = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << " Elapsed time (ns) # " << ns.count() << " nsec" << '\n';
    std::cout << " Elapsed time (us) # " << us.count() << " usec" << '\n';
    std::cout << " Elapsed time (ms) # " << ms.count() << " msec" << '\n';
    std::cout << " Elapsed time (sc) # " << sc.count() << " sec" << '\n';
  }

  {
    std::cout << "--- Measure time (generic version: user function takes no params) ---" << '\n';

    auto ns = Timer<std::chrono::nanoseconds>::measure(fun1);
    auto us = Timer<std::chrono::microseconds>::measure(fun1);
    auto ms = Timer<std::chrono::milliseconds>::measure(fun1);
    auto sc = Timer<std::chrono::seconds>::measure(fun1);
    auto def = Timer<>::measure(fun1);

    std::cout << " Elapsed time (default config) # " << def.count() << " nsec" << '\n';
    std::cout << " Elapsed time (ns)             # " << ns.count()  << " nsec" << '\n';
    std::cout << " Elapsed time (us)             # " << us.count()  << " usec" << '\n';
    std::cout << " Elapsed time (ms)             # " << ms.count()  << " msec" << '\n';
    std::cout << " Elapsed time (sc)             # " << sc.count()  << " sec"  << '\n';
  }

  {
    std::cout << "--- Measure time (generic version: user function takes params) ---" << '\n';

    auto ns = Timer<std::chrono::nanoseconds>::measure(fun2, 10, 10);
    auto us = Timer<std::chrono::microseconds>::measure(fun2, 10, 10);
    auto ms = Timer<std::chrono::milliseconds>::measure(fun2, 10, 10);
    auto sc = Timer<std::chrono::seconds>::measure(fun2, 10, 10);
    auto def = Timer<>::measure(fun2, 10, 10);

    std::cout << " Elapsed time (default config) # " << def.count() << " nsec" << '\n';
    std::cout << " Elapsed time (ns)             # " << ns.count()  << " nsec" << '\n';
    std::cout << " Elapsed time (us)             # " << us.count()  << " usec" << '\n';
    std::cout << " Elapsed time (ms)             # " << ms.count()  << " msec" << '\n';
    std::cout << " Elapsed time (sc)             # " << sc.count()  << " sec"  << '\n';

  }

  return 0;
}
