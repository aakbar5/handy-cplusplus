//
// Program
//  String tokenization
//
//  Following articles are quite interested to read:
//    - https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
//    - https://www.cppstories.com/2018/07/string-view-perf-followup/
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 04-misc 04-misc.cc
//
// Execution
//  ./04-misc
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Raw implementation using find & substring
template <typename InserterIter>
void split_1(const std::string& input, const std::string& delim, InserterIter iter)
{
  const size_t dlen = delim.length();
  const size_t ilen = input.length();

  size_t spos = 0;
  size_t fpos = input.find_first_of(delim, spos);
  while (fpos != input.npos)
  {
    std::string token = input.substr(spos, fpos - spos);
    if (token.length()) {
      *iter++ = token;
    }

    spos = fpos + dlen;
    fpos = input.find_first_of(delim, spos);
  }

  // To handle usecase; (1) input string is not having any delimnator
  // (2) token beyond the last deliminator
  std::string token = input.substr(spos, ilen);
  if (token.length()) {
    *iter++ = token;
  }
}

// Optimized version of the above
template <typename InserterIter>
void split_2(const std::string& input, const std::string& delim, InserterIter iter)
{
  const size_t dlen = delim.length();
  const size_t ilen = input.length();

  size_t spos = 0;
  while (spos < ilen)
  {
    size_t fpos = input.find_first_of(delim, spos);
    if (spos != fpos) {
      *iter++ = input.substr(spos, fpos - spos);
    }

    if (fpos == input.npos) {
      break;
    }

    spos = fpos + dlen;
  }
}

// Use strtok
template <typename InserterIter>
void split_3(const std::string& input, const std::string& delim, InserterIter iter)
{
  char *token = std::strtok((char *)input.c_str(), (char *)delim.c_str());
  while (token)
  {
    *iter++ = token;
    token = std::strtok(nullptr, (char *)delim.c_str());
  }
}

// Use std::getline
// Limit: delim must be single char
template <typename InserterIter>
void split_4(const std::string& input, const char delim, InserterIter iter)
{
  std::string token = {};
  std::istringstream sstream(input);
  while (std::getline(sstream, token, delim))
  {
    *iter++ = token;
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- String tokenization ---" << '\n';

  struct Test {
    std::string input;
    size_t tokenCount;
  };

  static std::vector<Test> TestCases {
    {"", 0},
    {"  ", 1},
    {"                      ", 1},
    {"Hello", 1},
    {"Hello,world", 2},
    {"This,is,a,test", 4},
    {"This,is,a,long,test", 5},
    {" This,is,a,long,test", 5},
    {" This,is,a,long,test  ", 5},
    {"    This,   is,   a,  long, test  ", 5},
    {" T,H,I,S  ", 4},
    {"Hello,,,", 1},
  };

  for (const auto& test: TestCases) {

    {
      std::vector<std::string> tokens;
      split_1(test.input, ",", std::back_inserter(tokens));
      assert(tokens.size() == test.tokenCount);
    }

    {
      std::vector<std::string> tokens;
      split_2(test.input, ",", std::back_inserter(tokens));
      assert(tokens.size() == test.tokenCount);
    }

    {
      std::vector<std::string> tokens;
      split_3(test.input, ",", std::back_inserter(tokens));
      assert(tokens.size() == test.tokenCount);
    }

    {
      std::vector<std::string> tokens;
      split_4(test.input, ',', std::back_inserter(tokens));
      assert(tokens.size() == test.tokenCount);
    }
  }

  return 0;
}
