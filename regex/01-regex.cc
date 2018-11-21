//
// Program
//  Regular Expression:
//      - Match an expression using simple regex.
//      - Match an expression using regex making groups of character sequence.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-regex 01-regex.cc
//
// Execution
//  ./01-regex
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
        { R"(sdummy<title>C++ Regex</title>)" },           // Not a match as required sequence is embedded in other sequence
        { R"(<title>C++ Regex</title>edummy)" },           // Same as above
        { R"(sdummy<title>C++ Regex</title>edummy)" },     // Same as above
    };

    std::cout << '\n'
              << "---- " << "Find start/end tag" <<  " ----"
              << '\n' << '\n';

    for (const auto& input: input_texts) {
      std::cout << "Sample Text: " << input << '\n';
      if (std::regex_match(input, re)) {
        std::cout << "    - Regex: start & end tags are found. " << '\n';
      }
      else {
        std::cout << "    - Regex: tags are not found. " << '\n';
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
      { R"(sdummy<title>C++ Regex</title>)" },           // Not a match as required sequence is embedded in other sequence
      { R"(<title>C++ Regex</title>edummy)" },           // Same as above
      { R"(sdummy<title>C++ Regex</title>edummy)" },     // Same as above
    };

    std::cout << '\n'
              << "---- " << "Find start/end tag (tag should be same)" <<  " ----"
              << '\n' << '\n';

    for (const auto& input: input_texts) {
      std::cout << "Sample Text: " << input << '\n';
      if (std::regex_match(input, re)) {
        std::cout << "    - Regex: start & end tags are found. " << '\n';
      }
      else {
        std::cout << "    - Regex: tags are not found. " << '\n';
      }
    }
  }

  return 0;
}
