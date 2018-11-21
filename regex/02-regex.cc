//
// Program
//  Regular Expression:
//      - Search an expression using simple regex.
//      - Search an expression using regex making groups of character sequence.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 02-regex 02-regex.cc
//
// Execution
//  ./02-regex
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
              << "---- " << "Find start/end tag" <<  " ----"
              << '\n' << '\n';

    std::smatch match;
    for (const auto& input: input_texts) {
      std::cout << '\n' << "Sample Text: " << input << '\n';
      if (std::regex_search(input, match, re)) {
        std::cout << "  " << "Prefix: " << match.prefix() << '\n';
        std::cout << "  " << "Suffix: " << match.suffix() << '\n';
        std::cout << "  " << "Matched: " << '\n';
        for (size_t i = 0; i < match.size(); ++i)
            std::cout << "  " << "  " << std::setw(2) << (i+1) << ": " << match[i] << '\n';
      }
      else {
        std::cout << "  " << "- Regex: tags are not found. " << '\n';
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
              << "---- " << "Find start/end tag (tag should be same)" <<  " ----"
              << '\n' << '\n';

    std::smatch match;
    for (const auto& input: input_texts) {
      std::cout << '\n' << "Sample Text: " << input << '\n';
      if (std::regex_search(input, match, re)) {
        std::cout << "  " << "Prefix: " << match.prefix() << '\n';
        std::cout << "  " << "Suffix: " << match.suffix() << '\n';
        std::cout << "  " << "Matched: " << '\n';
        for (size_t i = 0; i < match.size(); ++i)
          std::cout << "  " << "  " << std::setw(2) << (i+1) << ": " << match[i] << '\n';
      }
      else {
        std::cout << "  " << "- Regex: tags are not found. " << '\n';
      }
    }
  }

  return 0;
}
