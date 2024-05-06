//
// Program
//  Map a value of one range to another range.
//  https://stackoverflow.com/a/5732390 is having a good
//  explanation. Formula to be used:
//    double slope = 1.0 * (output_end - output_start) / (input_end - input_start)
//    output = output_start + slope * (input - input_start)
//
// Compile
//  g++ -Wall -Wextra -std=c++17 -o 02-misc 02-misc.cc
//
// Execution
//  ./02-misc
//

#include <iostream>

template<typename T>
struct Range {
  T start;
  T end;
};

struct Ranges {
  Range<int> input;
  Range<float> output;
};

double getSlope(const Ranges& ranges) {
  return 1.0f *
    (ranges.output.end - ranges.output.start) /
    (ranges.input.end - ranges.input.start);
}

double map(const Ranges& ranges, int input) {
  return (ranges.output.start + getSlope(ranges) *
    (input - ranges.input.start));
}

//
// Entry function
//
int main() {
  std::cout << "--- Map values b/w two ranges ---" << '\n';

  std::cout << "--- Map -128 <> 127 to 0.0f <> 1.0f ---\n";
  {
    const Ranges s8 = {
      .input = { .start = -128, .end = 127 },
      .output = { .start = 0.0f, .end = 1.0f },
    };

    for (int idx = -128; idx <= 127; ++idx) {
      printf("%4d, %lf\n", idx, map(s8, idx));
    }
  }

  std::cout << "--- Map 0 <> 255 to 0.0f <> 1.0f ---\n";
  {
    const Ranges u8 = {
      .input = { .start = 0, .end = 255 },
      .output = { .start = 0.0f, .end = 1.0f },
    };

    for (int idx = 0; idx <= 255; ++idx) {
      printf("%4d, %lf\n", idx, map(u8, idx));
    }
  }

  return 0;
}

// Output
// --- Map values b/w two ranges ---
// --- Map -128 <> 127 to 0.0f <> 1.0f ---
// -128, 0.000000
// -127, 0.003922
// -126, 0.007843
// ...
// ...
//    0, 0.501961
// ...
// ...
//  125, 0.992157
//  126, 0.996078
//  127, 1.000000
// --- Map 0 <> 255 to 0.0f <> 1.0f ---
//    0, 0.000000
//    1, 0.003922
//    2, 0.007843
// ...
// ...
//  130, 0.509804
// ...
// ...
//  253, 0.992157
//  254, 0.996078
//  255, 1.000000
