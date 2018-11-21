//
// Program
//  Overflow validation.
//  Using GCC built-in function to validate whether result
//  of a given operation will overflow the available width
//  of that datatype or not.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o type_overflow type_overflow.cc
//
// Execution
//  ./type_overflow
//

#include <iostream>
#include <iomanip>
#include <limits>

// These builtin functions were added GCC version 5.
// #if GCC_VERSION >= 50100
// #define COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW 1
// #endif

//
// Entry function
//
int main() {
  std::cout << "--- data type overflow ---" << '\n';

  {
    std::cout   << "--------------------------------------------------------"
                << "---------------------------------------------"
                << '\n';
    std::cout   << std::setw(20) << std::left << "char"
                << std::setw(25) << std::right << "lowest()"
                << std::setw(25) << std::right << "min()"
                << std::setw(25) << std::right << "max()" << '\n';
    std::cout   << "--------------------------------------------------------"
                << "---------------------------------------------"
                << '\n';

    std::cout   << std::setw(20) << std::left << "char"
                << std::setw(25) << std::right << (int)std::numeric_limits<char>::lowest()
                << std::setw(25) << std::right << (int)std::numeric_limits<char>::min()
                << std::setw(25) << std::right << (int)std::numeric_limits<char>::max() << '\n';

    std::cout   << std::setw(20) << std::left << "unsigned char"
                << std::setw(25) << std::right << (int)std::numeric_limits<unsigned char>::lowest()
                << std::setw(25) << std::right << (int)std::numeric_limits<unsigned char>::min()
                << std::setw(25) << std::right << (int)std::numeric_limits<unsigned char>::max() << '\n';

    std::cout   << std::setw(20) << std::left << "signed char"
                << std::setw(25) << std::right << (int)std::numeric_limits<signed char>::lowest()
                << std::setw(25) << std::right << (int)std::numeric_limits<signed char>::min()
                << std::setw(25) << std::right << (int)std::numeric_limits<signed char>::max() << '\n';
    std::cout   << std::setw(20) << std::left << "char16_t"
                << std::setw(25) << std::right << (int)std::numeric_limits<char16_t>::lowest()
                << std::setw(25) << std::right << (int)std::numeric_limits<char16_t>::min()
                << std::setw(25) << std::right << (int)std::numeric_limits<char16_t>::max() << '\n';
    std::cout   << std::setw(20) << std::left << "char32_t"
                << std::setw(25) << std::right << (int)std::numeric_limits<char32_t>::lowest()
                << std::setw(25) << std::right << (int)std::numeric_limits<char32_t>::min()
                << std::setw(25) << std::right << (int)std::numeric_limits<char32_t>::max() << '\n';

    std::cout << std::setw(20) << std::left << "short"
                << std::setw(25) << std::right << std::numeric_limits<short>::lowest()
                << std::setw(25) << std::right << std::numeric_limits<short>::min()
                << std::setw(25) << std::right << std::numeric_limits<short>::max() << '\n';
    std::cout << std::setw(20) << std::left << "unsigned short"
                << std::setw(25) << std::right << std::numeric_limits<unsigned short>::lowest()
                << std::setw(25) << std::right << std::numeric_limits<unsigned short>::min()
                << std::setw(25) << std::right << std::numeric_limits<unsigned short>::max() << '\n';

    std::cout << std::setw(20) << std::left << "int"
                << std::setw(25) << std::right << std::numeric_limits<int>::lowest()
                << std::setw(25) << std::right << std::numeric_limits<int>::min()
                << std::setw(25) << std::right << std::numeric_limits<int>::max() << '\n';
    std::cout << std::setw(20) << std::left << "unsigned int"
                << std::setw(25) << std::right << std::numeric_limits<unsigned int>::lowest()
                << std::setw(25) << std::right << std::numeric_limits<unsigned int>::min()
                << std::setw(25) << std::right << std::numeric_limits<unsigned int>::max() << '\n';

    std::cout << std::setw(20) << std::left << "long"
                << std::setw(25) << std::right << std::numeric_limits<long>::lowest()
                << std::setw(25) << std::right << std::numeric_limits<long>::min()
                << std::setw(25) << std::right << std::numeric_limits<long>::max() << '\n';
    std::cout << std::setw(20) << std::left << "unsigned long"
                << std::setw(25) << std::right << std::numeric_limits<unsigned long>::lowest()
                << std::setw(25) << std::right << std::numeric_limits<unsigned long>::min()
                << std::setw(25) << std::right << std::numeric_limits<unsigned long>::max() << '\n';

    std::cout   << "--------------------------------------------------------"
                << "---------------------------------------------"
                << '\n';
  }

  {
    std::cout << "--- unsigned char ---" << '\n';
    // Range: 0 <> 255

    unsigned char a = 10;
    unsigned char b = 250;
    unsigned char c = 0;
    bool ret = __builtin_add_overflow(a, b, &c);
    std::cout << (int)a << " + " << (int)b << " = " << (int)c << '\n';
    std::cout << "  -- Overflow status: " << std::boolalpha << ret << '\n';
  }

  {
    std::cout << "--- unsigned char ---" << '\n';
    // Range: 0 <> 255

    unsigned char a = 10;
    unsigned char b = 230;
    unsigned char c = 0;
    bool ret = __builtin_add_overflow(a, b, &c);
    std::cout << (int)a << " + " << (int)b << " = " << (int)c << '\n';
    std::cout << "  -- Overflow status: " << std::boolalpha << ret << '\n';
  }

  {
    std::cout << "--- short ---" << '\n';
    // Range: -32768 <> 32767

    short a = 10;
    short b = 32760;
    short c = 0;
    bool ret = __builtin_add_overflow(a, b, &c);
    std::cout << a << " + " << b << " = " << c << '\n';
    std::cout << "  -- Overflow status: " << std::boolalpha << ret << '\n';
  }

  {
    std::cout << "--- short ---" << '\n';
    // Range: -32768 <> 32767

    short a = -10;
    short b = -32760;
    short c = 0;
    bool ret = __builtin_add_overflow(a, b, &c);
    std::cout << a << " + " << b << " = " << c << '\n';
    std::cout << "  -- Overflow status: " << std::boolalpha << ret << '\n';
  }

  {
    std::cout << "--- long ---" << '\n';
    // Range: -9223372036854775808 <> 9223372036854775807

    long a = 10;
    long b = 9223372036854775800;
    long c = 0;
    bool ret = __builtin_add_overflow(a, b, &c);
    std::cout << a << " + " << b << " = " << c << '\n';
    std::cout << "  -- Overflow status: " << std::boolalpha << ret << '\n';
  }

  {
    std::cout << "--- long ---" << '\n';
    // Range: -9223372036854775808 <> 9223372036854775807

    long a = 7;
    long b = 9223372036854775800;
    long c = 0;
    bool ret = __builtin_add_overflow(a, b, &c);
    std::cout << a << " + " << b << " = " << c << '\n';
    std::cout << "  -- Overflow status: " << std::boolalpha << ret << '\n';
  }

  return 0;
}
