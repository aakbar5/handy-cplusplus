//
// Program
//  Regular Expression: Replace an expression
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 04-regex 04-regex.cc
//
// Execution
//  ./04-regex
//

#include <iostream>
#include <iomanip>
#include <regex>
#include <vector>

//
// Entry function
//
int main() {
  {
    // Find start and end tags:
    // - <START_TAG> text </ END_TAG>
    // - start and end tags can be anywhere in the long sentence
    // - start end end tags must have same text
    std::regex re(R"(<(.*)>.*<\/(\1)>)");

    std::vector<std::string> input_texts = {
      { R"(<start>C++ Regex</start>)" },
      { R"(<start>C++ Regex</end>)" },
      { R"(<title>C++ Regex</title>)" },
      { R"(<title>C++ Regex  title>)" },
      { R"(<title C++ Regex</title>)" },
      { R"(sdummy<title>C++ Regex</title>)" },
      { R"(<title>C++ Regex</title>edummy)" },
      { R"(sdummy<title>C++ Regex</title>edummy)" },
    };

    std::cout << '\n'
              << "---- " << "Find start/end tag" <<  " ----"
              << '\n' << '\n';

    // Ref: https://www.boost.org/doc/libs/1_46_1/libs/regex/doc/html/boost_regex/format.html explains mapping fmt
    std::string new_s;
    for (const auto& input: input_texts) {
      std::cout << '\n' << "- " << input << '\n';
      new_s = std::regex_replace(input, re, "[$&]"); // $& wrapped matched char sequence in [ ]
      std::cout << "> " << new_s << '\n';

      new_s = std::regex_replace(input, re, "[$']"); // $' wrapped char sequence after our matched string in [ ]
      std::cout << "> " << new_s << '\n';

      new_s = std::regex_replace(input, re, "[$`]"); // $' wrapped char sequence before our matched string in [ ]
      std::cout << "> " << new_s << '\n';
    }
  }

  return 0;
}
