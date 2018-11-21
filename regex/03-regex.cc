//
// Program
//  Regular Expression:
//      - Search an expression via iterator using simple regex.
//      - Search an expression via iterator using regex making groups of character sequence.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 03-regex 03-regex.cc
//
// Execution
//  ./03-regex
//

#include <iostream>
#include <regex>
#include <vector>

//
// Entry function
//
int main() {
  {
    // Our regex expression is looking for a sequence having
    // - <START_TAG>text</END_TAG>
    // - START_TAG and END_TAG can have any text
    std::regex re(R"(<.*>.*<\/.*>)");

    std::vector<std::string> input_texts = {
      { R"(<start>C++ Regex</start>)" },                 // Match is there
      { R"(<start>C++ Regex</end>)" },                   // Match is there
      { R"(<title>C++ Regex</title>)" },                 // Match is there
      { R"(<title>C++ Regex  title>)" },                 // Not a match; End tag is missing
      { R"(<title C++ Regex</title>)" },                 // Not a match; Start tag is missing
      { R"(sdummy<title>C++ Regex</title>)" },           // Match is there
      { R"(<title>C++ Regex</title>edummy)" },           // Match is there
      { R"(sdummy<title>C++ Regex</title>edummy)" },     // Match is there
    };

    std::cout << '\n'
              << "---- " << "Find start/end tag (iterator)" <<  " ----"
              << '\n' << '\n';

    for (const auto& input: input_texts) {
      std::cout << '\n' << "Sample Text: " << input << '\n';

      auto start = std::sregex_iterator(std::begin(input), std::end(input), re);
      auto end = std::sregex_iterator();

      std::cout << "  " << "Found: " << std::distance(start, end) << '\n';
      for (size_t idx = 1; start != end; ++start, ++idx) {
        std::cout << "  " << "#" << idx << ": '" << start->str() << "'\n";
      }
    }
  }

  {
    // Find start and end tags:
    // - <START_TAG> text </ END_TAG>
    // - start and end tags can be anywhere in the long sentence
    // - start end end tags must have same text
    std::regex re(R"(<(.*)>.*<\/(\1)>)");

    std::vector<std::string> input_texts = {
      { R"(<start>C++ Regex</start>)" },                 // Match is there
      { R"(<start>C++ Regex</end>)" },                   // Not a match as start/end tags are different
      { R"(<title>C++ Regex</title>)" },                 // Match is there
      { R"(<title>C++ Regex  title>)" },                 // Not a match; End tag is missing
      { R"(<title C++ Regex</title>)" },                 // Not a match; Start tag is missing
      { R"(sdummy<title>C++ Regex</title>)" },           // Match is there
      { R"(<title>C++ Regex</title>edummy)" },           // Match is there
      { R"(sdummy<title>C++ Regex</title>edummy)" },     // Match is there
    };

    std::cout << '\n'
              << "---- " << "Find start/end tag (iterator)" <<  " ----"
              << '\n' << '\n';

    for (const auto& input: input_texts) {
      std::cout << '\n' << "Sample Text: " << input << '\n';
      {
        std::cout << '\n' << "  " << "--- # 0 ---" << '\n';
        auto start = std::sregex_token_iterator(std::begin(input), std::end(input), re, 0);
        auto end = std::sregex_token_iterator();

        std::cout << "  " << "Found: " << std::distance(start, end) << '\n';
        for (size_t idx = 1; start != end; ++start, ++idx) {
          std::cout << "  " << "#" << idx << ": '" << start->str() << "'\n";
        }
      }
      {
        std::cout << '\n' << "  " << "--- # -1 ---" << '\n';
        auto start = std::sregex_token_iterator(std::begin(input), std::end(input), re, -1);
        auto end = std::sregex_token_iterator();

        std::cout << "  " << "Found: " << std::distance(start, end) << '\n';
        for (size_t idx = 1; start != end; ++start, ++idx) {
          std::cout << "  " << "#" << idx << ": '" << start->str() << "'\n";
        }
      }
      {
        std::cout << '\n' << "  " << "--- # {0, -1} ---" << '\n';
        auto start = std::sregex_token_iterator(std::begin(input), std::end(input), re, {0, -1});
        auto end = std::sregex_token_iterator();

        std::cout << "  " << "Found: " << std::distance(start, end) << '\n';
        for (size_t idx = 1; start != end; ++start, ++idx) {
          std::cout << "  " << "#" << idx << ": '" << start->str() << "'\n";
        }
      }
      {
        std::cout << '\n' << "  " << "--- # {0, 1} ---" << '\n';
        auto start = std::sregex_token_iterator(std::begin(input), std::end(input), re, {0, 1});
        auto end = std::sregex_token_iterator();

        std::cout << "  " << "Found: " << std::distance(start, end) << '\n';
        for (size_t idx = 1; start != end; ++start, ++idx) {
          std::cout << "  " << "#" << idx << ": '" << start->str() << "'\n";
        }
      }
    }
  }

  return 0;
}
