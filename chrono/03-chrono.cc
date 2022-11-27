//
// Program
//  Print date & time.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 03-chrono 03-chrono.cc
//
// Execution
//  ./03-chrono
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>

// std::put_time likes pointer to the calendar time structure as obtained from std::localtime or std::gmtime
std::string stringify_time_1(const std::chrono::system_clock::time_point& time_pt) {
  std::ostringstream time_str;

  // Convert time_point to ctime
  std::time_t now_tt = std::chrono::system_clock::to_time_t(time_pt);

  // Convertto std::tm
  struct std::tm *now_lt = std::localtime(&now_tt);

  // Send char* to string stream (NOTE: time format is in the format of std::ctime)
  time_str << std::put_time(now_lt, "%a %b %Od %OH:%OM:%OS %Y");

  return time_str.str();
}

// Use std::ctime to have textual representation of time
// - std::ctime makes use of the std::asctime to textual representation
//   and std:asctime function uses a statically allocated string so it is not
//   thread safe.
std::string stringify_time_2(const std::chrono::system_clock::time_point& time_pt) {
  std::ostringstream time_oss;

  // Convert time_point to ctime
  std::time_t now_tt = std::chrono::system_clock::to_time_t(time_pt);

  // Send char* to string stream
  time_oss << std::ctime(&now_tt);

  // Get time string
  auto str = time_oss.str();

  // Drop newline character
  return std::string(str, 0, str.size() - 1);
}

//
// Entry function
//
int main() {
  std::cout << "--- Date & time ---" << '\n';

  std::chrono::system_clock::time_point now_tp = std::chrono::system_clock::now();

  std::cout << "--- std::put_time ---" << '\n';
  std::cout << "Date & time (current):        " << stringify_time_1(now_tp) << '\n';
  std::cout << "Date & time (after 2 hours):  " << stringify_time_1(now_tp + std::chrono::hours(2)) << '\n';
  std::cout << "Date & time (Before 2 hours): " << stringify_time_1(now_tp - std::chrono::hours(2)) << '\n';

  std::cout << "--- std::ctime ---" << '\n';
  std::cout << "Date & time (current):        " << stringify_time_2(now_tp) << '\n';
  std::cout << "Date & time (after 2 hours):  " << stringify_time_2(now_tp + std::chrono::hours(2)) << '\n';
  std::cout << "Date & time (Before 2 hours): " << stringify_time_2(now_tp - std::chrono::hours(2)) << '\n';

  return 0;
}
