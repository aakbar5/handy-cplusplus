//
// Program
//  Determine the day of the week from a date
//  - This example is discussed in
//    Book # Modern C++ Programming Cookbook by Marius Bancila
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++20 -o 07-chrono 07-chrono.cc
//
// Execution
//  ./07-chrono
//

#include <iostream>
#include <chrono>

using namespace std::chrono;

// Compiler (C++20) is not having stream operator<<
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

inline static std::ostream &operator<<(std::ostream &os, const sys_days& sd) {
  auto ymd = year_month_day(sd);
  os << static_cast<unsigned>(ymd.day())
     << '/'
     << ymd.month()
     << '/'
     << static_cast<int>(ymd.year());
  return os;
}

inline static std::ostream &operator<<(std::ostream &os, const weekday& wd) {
  switch (wd.c_encoding())
  {
  case  0: os << "Sunday"; break;
  case  1: os << "Monday"; break;
  case  2: os << "Tuesday"; break;
  case  3: os << "Wednesday"; break;
  case  4: os << "Thursday"; break;
  case  5: os << "Friday"; break;
  case  6: os << "Saturday"; break;
  default: os << "<invalid day: " << wd.c_encoding() << ">";break;
  }
  return os;
}

inline static std::ostream &operator<<(std::ostream &os, const weekday_indexed& wi) {
  os << wi.weekday() << "(" << wi.index() << ")";
  return os;
}

static unsigned int week_day(const sys_days& date) {
  year_month_weekday ymw {date};
  return ymw.weekday_indexed().index();
}

//
// Entry function
//
int main() {
  std::cout << "--- Day of the week ---" << '\n';

  {
    year_month_weekday ymw {2018y/October/Friday[last]};
    std::cout << ymw << '\n'
              << "  - " << ymw.weekday_indexed() << '\n'
              << "  - " << ymw.weekday_indexed().weekday() << '\n'
              << "  - " << ymw.weekday_indexed().index() << '\n'
              << '\n';
  }

  {
    sys_days d1 {2018y/October/13};
    sys_days d2 {2018y/November/1};

    std::cout << d1 << " week day is " << week_day(d1) << '\n';
    std::cout << d2 << " week day is " << week_day(d2) << '\n';
  }

  return 0;
}
