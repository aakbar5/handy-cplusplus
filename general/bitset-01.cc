//
// Program
//  std::bitset usage.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o bitset-01 bitset-01.cc
//
// Execution
//  ./bitset-01
//

#include <iostream>
#include <bitset>
#include <cassert>

//
// Entry function
//
int main() {
  std::cout << "--- std::bitset ---" << '\n';

  std::bitset<4> b4;
  assert(b4 == 0b0000);

  std::bitset<4> b4i {};
  assert(b4i == 0b0000);

  std::bitset<4> bh{0xF};
  assert(bh == 0b1111);

  std::bitset<4> bs{"1111"};
  assert(bs == 0b1111);

  std::bitset<4> bb{0b110};
  assert(bb == 0b0110);

  std::bitset<4> bn{4};
  assert(bn == 0b0100);

  bn.set(0);
  assert(bn == 0b0101);

  bn.reset(0);
  assert(bn == 0b0100);

  bn.reset();
  assert(bn == 0b0000);

  bn.flip(0);
  assert(bn == 0b0001);

  bn.flip();
  assert(bn == 0b1110);

  bn.set(0, true);
  assert(bn == 0b1111);

  bn.set(1, false);
  assert(bn == 0b1101);

  bn <<= 2;
  assert(bn == 0b0100);

  bn >>= 2;
  assert(bn == 0b0001);

  bn = 0b0000;
  assert(bn.all() == false); // has all 1?
  assert(bn.any() == false); // has any 1?
  assert(bn.none() == true); // has all zero?

  bn = 0b1111;
  assert(bn.all() == true); // has all 1?
  assert(bn.any() == true); // has any 1?
  assert(bn.none() == false); // has all zero?

  bn = 0b0101;
  assert(bn.all() == false); // has all 1?
  assert(bn.any() == true); // has any 1?
  assert(bn.none() == false); // has all zero?

  bn = 0x4;
  assert(bn.size() == 4);
  assert(bn.count() == 1);

  assert(bn.to_string() == "0100");
  assert(bn.to_ulong() == 4UL);
  assert(bn.to_ullong() == 4ULL);

  return 0;
}
