//
// Program
//  This program simply creates a thread and prints its ID.
//      - Create a thread
//      - Create a thread which accepts a parameter
//      - Create a thread whose callback is implemented by lambda
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-chrono 01-chrono.cc
//
// Execution
//  ./01-chrono
//

#include <iostream>
#include <chrono>
#include <iomanip>

template<typename clock>
void fun(std::string msg) {
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
    // const std::chrono::time_point<std::chrono::system_clock>
    auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::cout << "system_clock: " << std::put_time(std::localtime(&time), "%F %T") << '\n';
  }

  // Increase with time
  // Can be mapped to system_clock of steady_clock so portablility can be problemetic
  {
    // const std::chrono::time_point<std::chrono::high_resolution_clock>
    auto now = std::chrono::high_resolution_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::cout << "high_resolution_clock: " << std::put_time(std::localtime(&time), "%F %T") << '\n';
  }

  // Increase with time
  // Good for interval measurements
  {
    //  std::chrono::steady_clock::time_point
    // std::chrono::time_point<std::chrono::steady_clock>
    // auto now = std::chrono::steady_clock::now();
    // return system_clock::to_time_t(system_clock::now() + (t - steady_clock::now()));
    // const std::time_t time = std::chrono::system_clock::to_time_t(now);
    // std::cout << "steady_clock: " << std::put_time(std::localtime(&time), "%F %T") << '\n';
  }

  // utc_clock
  {
    fun<std::chrono::system_clock>("system_clock: ");
    fun<std::chrono::high_resolution_clock>("high_resolution_clock: ");
    // fun<std::chrono::utc_clock>("utc_clock: ");
    // fun<std::chrono::gps_clock>("gps_clock: ");
    // fun<std::chrono::tai_clock>("tai_clock: ");
  }

  return 0;
}
