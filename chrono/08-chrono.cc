//
// Program
//  Show calendar of a month
//  - This example is discussed in
//    Book # Modern C++ Programming Cookbook by Marius Bancila
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++20 -o 08-chrono 08-chrono.cc
//
// Execution
//  ./08-chrono
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

// Compiler (C++20) is not having stream operator<<
inline static std::ostream &operator<<(std::ostream &os, const year& y) {
  return os << static_cast<int>(y);
}

inline static std::ostream &operator<<(std::ostream &os, const month& m) {
    switch (static_cast<unsigned>(m))
    {
    case  1: os << "January"; break;
    case  2: os << "February"; break;
    case  3: os << "March"; break;
    case  4: os << "April"; break;
    case  5: os << "May"; break;
    case  6: os << "June"; break;
    case  7: os << "July"; break;
    case  8: os << "August"; break;
    case  9: os << "September"; break;
    case 10: os << "October"; break;
    case 11: os << "November"; break;
    case 12: os << "December"; break;
    default: os << "<invalid month: " << static_cast<unsigned>(m) << ">";break;
    }
    return os;
}

static void show_calendar(int y, int m) {

  // Start of the month
  auto start = year_month_day{year(y)/month(m)/1};

  // End of the month
  auto end = year_month_day{year(y)/month(m)/last};

  // Calculate missing day offset
  auto offset_days = (weekday(start) - Sunday).count();
  auto offset_str = std::string(offset_days * 4, ' ');

  // Show banner
  std::cout << start.year() << "/" << start.month() << std::endl;
  std::vector<std::string> days {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
  for (const auto &d: days) {
      std::cout << std::setw(4) << std::left << d << std::flush;
  }
  std::cout << '\n';
  std::cout << offset_str << std::flush;

  // Show dates
  for (unsigned i = 1; i <= static_cast<unsigned>(end.day()); ++i) {
    if (offset_days % 7 == 0)
        std::cout << '\n';

    std::cout << std::setw(3) << std::right << i << ' ' << std::flush;
    ++offset_days;
  }

  std::cout << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- Calendar of a month ---" << '\n';
  show_calendar(2017, 12);
  return 0;
}
