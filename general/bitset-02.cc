//
// Program
//  std::bitset + bit algo usage.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++20 -o bitset-02 bitset-02.cc
//
// Execution
//  ./bitset-02
//

#include <iostream>
#include <bitset>
#include <bit>
#include <cassert>

//
// Entry function
//
int main() {
  std::cout << "---  std::bitset + bit algo usage ---" << '\n';

  for (const uint8_t var: {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}) {
    std::cout << std::bitset<8>(var)
              << " (" << static_cast<int>(var) << ") "
              << " has_single_bit: "
              << std::boolalpha
              << std::has_single_bit(var)
              << '\n';
  }
  std::cout << '\n';

  for (const uint8_t var: {0U, 0b11111111U, 0b11110000U, 0b00011110U, 0b00110000U, 0b00010100U}) {
    std::cout << std::bitset<8>(var) << " countl_zero: " << std::countl_zero(var) << '\n';
    std::cout << std::bitset<8>(var) << " countl_one:  " << std::countl_one(var) << '\n';
    std::cout << std::bitset<8>(var) << " countr_zero: " << std::countr_zero(var) << '\n';
    std::cout << std::bitset<8>(var) << " countr_one:  " << std::countr_one(var) << '\n';
    std::cout << std::bitset<8>(var) << " popcount:    " << std::popcount(var) << '\n';
    std::cout << std::bitset<8>(var) << " rotl:        " << std::bitset<8>(std::rotl(var, 2)) << '\n';
    std::cout << std::bitset<8>(var) << " rotr:        " << std::bitset<8>(std::rotr(var, 2)) << '\n';
    std::cout << '\n';
  }

  for (const uint32_t var: {0, 2, 5, 7, 8, 13, 15, 16, 31, 63, 127, 128}) {
    std::cout << var << " bit_ceil: " << std::bit_ceil(var) << '\n';
  }
  std::cout << '\n';

  return 0;
}
