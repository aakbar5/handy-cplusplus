//
// Program
//  Handy function to manipulate strings.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o string_utils string_utils.cc
//
// Execution
//  ./string_utils
//
#include <iostream>
#include <vector>
#include <algorithm>

bool starts_with(std::string_view input, std::string_view target) {
  return input.find(target) == 0;
}

bool ends_with(std::string_view input, std::string_view target) {
  auto pos = input.length() - target.length();
  return (input.find(target, pos) == pos);
}

void ltrim(std::string& input) {
  auto space_end = std::find_if(std::begin(input), std::end(input),
    [](const auto& ch) {
      return (!std::isspace(ch));
    }
  );
  input.erase(std::begin(input), space_end);
}

void rtrim(std::string& input) {
  auto rit = std::find_if(input.rbegin(), input.rend(),
      [](const auto& ch) {
        return !(std::isspace(ch));
      }
  );
  input.erase(rit.base(), input.end());
}

void trim(std::string& input) {
  ltrim(input);
  rtrim(input);
}

void tokenize(std::string_view input, const char target, std::vector<std::string>& token_list) {
  using size_type = std::string::size_type;

  size_type last_pos = 0;
  size_type pos = input.find(target, last_pos);
  while (pos != std::string::npos) {
    token_list.emplace_back(input.substr(last_pos, pos - last_pos));

    // Skip the character
    last_pos = pos + 1;
    pos = input.find(target, last_pos);
  }

  // Copy the left over part
  auto rem = input.length() - last_pos;
  if (rem > 0) {
    token_list.emplace_back(input.substr(last_pos));
  }
}

//
// Entry function
//
int main() {
  // Test starts_with
  {
    std::cout << "Test # starts_with" << '\n';
    std::cout << std::boolalpha << starts_with("testtesting", "te") << '\n';
    std::cout << std::boolalpha << starts_with("testtesting", "ta") << '\n';
    std::cout << std::boolalpha << starts_with("testtesting", "xy") << '\n';
  }

  {
    std::cout << "Test # ends_with" << '\n';
    std::cout << std::boolalpha << ends_with("test", "t") << '\n';
    std::cout << std::boolalpha << ends_with("test", "est") << '\n';
    std::cout << std::boolalpha << ends_with("test", "g") << '\n';
  }

  {
    std::cout << "Test # ltrim" << '\n';
    std::vector<std::string> strings {"  test", "test  ", " test  ", " test test "};
    for (auto str: strings) {
      std::cout << "[" << str << "]";
      ltrim(str);
      std::cout << "[" << str << "]" << '\n';
    }
  }

  {
    std::cout << "Test # rtrim" << '\n';
    std::vector<std::string> strings {"  test", "test  ", " test  ", " test test "};
    for (auto str: strings) {
      std::cout << "[" << str << "]";
      rtrim(str);
      std::cout << "[" << str << "]" << '\n';
    }
  }

  {
    std::cout << "Test # tokenize" << '\n';
    {
      std::vector<std::string> token_list;
      std::string input("first,second,third");
      tokenize(input, ',', token_list);

      std::cout << '\n' << "Show tokens of: " << input << '\n';
      for (const auto& tok: token_list)
        std::cout << "[" << tok << "]" << '\n';
    }

    {
      std::vector<std::string> token_list;
      std::string input("first,second,third,");
      tokenize(input, ',', token_list);

      std::cout << '\n' << "Show tokens of: " << input << '\n';
      for (const auto& tok: token_list)
        std::cout << "[" << tok << "]" << '\n';
    }

    {
      std::vector<std::string> token_list;
      std::string input("first,second,third,fourth,,              ,");
      tokenize(input, ',', token_list);

      std::cout << '\n' << "Show tokens of: " << input << '\n';
      for (const auto& tok: token_list)
        std::cout << "[" << tok << "]" << '\n';
    }
  }

  return 0;
}
