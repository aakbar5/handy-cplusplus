//
// Program
//  Manipulate different clocks
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++20 -o 05-chrono 05-chrono.cc
//
// Execution
//  ./05-chrono
//

#include <iostream>
#include <chrono>
#include <iomanip>

// Util function which can handle different clocks
template<typename clock>
static void func(std::string msg) {
  auto now = clock::now();
  auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
  std::cout << msg << int_ms << std::endl;
}

//
// Entry function
//
int main() {
  // system wide real time wall clock
  // C-style time_t is available in it
  // Since C++20, Unix Time
  {
    // steady_clock can be also be used however std::localtime can transform steady_clock
    auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::cout << "system_clock: " << std::put_time(std::localtime(&time), "%F %T") << '\n';
  }

  // Increase with time
  // Can be mapped to system_clock or steady_clock so portablility can be problemetic
  {
    // const std::chrono::time_point<std::chrono::high_resolution_clock>
    auto now = std::chrono::high_resolution_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::cout << "high_resolution_clock: " << std::put_time(std::localtime(&time), "%F %T") << '\n';
  }

  // different clocks
  {
    func<std::chrono::system_clock>("system_clock: ");
    func<std::chrono::high_resolution_clock>("high_resolution_clock: ");
    // func<std::chrono::utc_clock>("utc_clock: ");
    // func<std::chrono::gps_clock>("gps_clock: ");
    // func<std::chrono::tai_clock>("tai_clock: ");
  }

  return 0;
}
