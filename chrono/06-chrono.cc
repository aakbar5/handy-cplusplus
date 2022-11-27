//
// Program
//  Number of days between two dates
//  - This example is discussed in
//    Book # Modern C++ Programming Cookbook by Marius Bancila
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++20 -o 05-chrono 05-chrono.cc
//
// Execution
//  ./05-chrono
//

#include <iostream>
#include <chrono>
#include <cassert>

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

// Number of days b/w two dates
static int get_days(const sys_days& d1, const sys_days& d2) {
  return (d1 - d2).count();
}

//
// Entry function
//
int main() {
  std::cout << "--- Number of days between two dates ---" << '\n';

  {
    sys_days d1{2018y/October/13};
    sys_days d2{2018y/October/10};

    std::cout << "D1: " << d1 << '\n';
    std::cout << "D2: " << d2 << '\n';
    std::cout << "Days: " << get_days(d1, d2) << '\n';
    std::cout << "Days: " << get_days(2018y/October/13, 10d/October/2018) << '\n';
  }

  {
    assert(3   == get_days(2018y/October/13, 2018y/October/10));
    assert(112 == get_days(2019y/December/15, 2019y/August/25));
    assert(1   == get_days(2019y/December/15, 2019y/December/14));
    assert(2922 == get_days(2027y/December/15, 2019y/December/15));
  }

  return 0;
}
