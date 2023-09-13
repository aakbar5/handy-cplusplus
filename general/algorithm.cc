//
// Program
//  <algorithm> usage.
//    - std::transform
//    - std::count
//    - std::count_if
//    - std::generate
//    - std::for_each
//    - std::for_each_n
//    - std::fill_n
//    - std::copy
//    - std::copy_if
//    - std::copy_n
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o algorithm algorithm.cc
//
// Execution
//  ./algorithm
//

#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>

// Util function to print vector
static std::ostream& operator<< (std::ostream& out, const std::vector<int> vec) {

  out << "(size: " << vec.size() << ") ";
  for (const auto &num: vec) {
    out << num << " ";
  }
  return out;
}

//
// Entry function
//
int main() {

  {
    // The transform performs operation onto the input container
    // and stores results to the 2nd container

    // Make vector of values having odd numbers
    std::cout << "--- std::transform (extract odd) ---" << '\n';
    {
      std::vector<int> input {1, 2, 3, 4, 5, 6};
      std::vector<int> odd {};

      auto fun = [](int num) {
        return (num & 0x1) ? num : 0;
      };
      std::transform(std::begin(input), std::end(input),
                     std::back_inserter(odd), fun);

      assert(odd.size() == 6); // Note size is 6 not 3
      std::cout << "Input:  " << input << '\n';
      std::cout << "Odds:   " << odd << '\n';
    }

    // Extract values from the map
    std::cout << "--- std::transform (extract values from map) ---" << '\n';
    {
      std::map<std::string, int> input {
        {"Test1", 100}, {"Test2", 200},
        {"Test3", 300}, {"Test4", 400},
      };
      std::vector<int> values {};

      auto fun = [](const auto &pair) {
        return (pair.second);
      };
      std::transform(std::begin(input), std::end(input),
                     std::back_inserter(values), fun);

      assert(values.size() == 4);
      std::cout << "Transform (Keys): " << values << '\n';
    }

    // Add each element of the input vectors
    std::cout << "--- std::transform (+ two vectors) ---" << '\n';
    {
      std::vector<int> input1 {1, 3, 5, 7};
      std::vector<int> input2 {2, 4, 6, 8};
      std::vector<int> total {};

      auto fun = [](int num1, int num2) {
        return (num1 + num2);
      };
      std::transform(std::begin(input1), std::end(input1),
                     std::begin(input2),
                     std::back_inserter(total), fun);

      // assert(total.size() == 4);
      std::cout << "Input1: " << input1 << '\n';
      std::cout << "Input2: " << input2 << '\n';
      std::cout << "Sum:    " << total << '\n';
    }

    // Change case of the input string
    std::cout << "--- std::transform (Change case) ---" << '\n';
    {
      std::string input {"HELLO world"};
      std::string output {};

      auto fun = [](char ch) {
        if (ch >= 'A' && ch <= 'Z')
          return ::tolower(ch);
        else
          return ::toupper(ch);
      };
      std::transform(std::begin(input), std::end(input),
                     std::back_inserter(output), fun);

      std::cout << "Input:  " << input << '\n';
      std::cout << "Output: " << output << '\n';
    }

    // Change case of the input string (inplace)
    std::cout << "--- std::transform (Change case inplace) ---" << '\n';
    {
      std::string input {"HELLO world"};
      std::cout << "Input:  " << input << '\n';

      auto fun = [](unsigned char ch) {
        if (ch >= 'A' && ch <= 'Z')
          return ::tolower(ch);
        else
          return ::toupper(ch);
      };
      std::transform(std::begin(input), std::end(input),
                     std::begin(input), fun);
      std::cout << "Output: " << input << '\n';
    }
  }

  {
    std::cout << "--- std::count ---" << '\n';
    {
      std::vector<int> vec {1, 2, 1, 4, 3, 6};

      auto ret = std::count(vec.begin(), vec.end(), 1);
      assert(ret == 2);
      std::cout << vec << " is having 2 " << ret << " times" << '\n';

      ret = std::count(vec.begin(), vec.end(), 3);
      assert(ret == 1);
      std::cout << vec << " is having 3 " << ret << " times" << '\n';

      ret = std::count(vec.begin(), vec.end(), 10);
      assert(ret == 0);
      std::cout << vec << " is having 10 " << ret << " times" << '\n';

      ret = std::count_if(vec.begin(), vec.end(), [](int num){ return (num & 0x1);});
      assert(ret == 3);
      std::cout << vec << " is having " << ret << " odd numbers" << '\n';
    }
  }

  {
    std::cout << "--- std::generate ---" << '\n';
    {
      std::vector<int> vec (5);
      std::cout << vec << '\n';

      int val = 1;
      auto fun = [&val]() {
        return val++;
      };

      // Assigns each element of the container a value
      // received from the generator
      std::generate(vec.begin(), vec.end(), fun);
      std::cout << "Generate: " << vec << '\n';
    }
  }

  {
    std::cout << "--- std::for_each ---" << '\n';
    {
      std::vector<std::string> vec {"1", "2", "3", "4"};
      std::string combine {};
      std::for_each(vec.begin(), vec.end(),
        [&combine] (const std::string &str) {
          if (combine.size())
              combine += "|";
          combine += str;
      });
      std::cout << "Concatenate: " << combine << '\n';
    }

    std::cout << "--- std::for_each_n ---" << '\n';
    {
      std::vector<int> vec {1, 2, 3, 4, 5, 6};
      auto fun = [](int num) {
        if (num & 0x1)
          std::cout << num << " is odd\n";
        else
          std::cout << num << " is even\n";
      };
      std::for_each_n(vec.begin(), 6, fun);
    }
  }

  std::cout << "--- std::fill_n ---" << '\n';
  {
    // Usage of std::fill_n function
    {
      std::vector<int> vec {};
      std::cout << "Before: " << vec << '\n';

      // seg fault as you are trying fill vec which is of size zero
      // std::fill_n(vec.begin(), 10, 0);

      vec.resize(10);
      std::fill_n(vec.begin(), 10, -1);
      std::cout << "After: " << vec << '\n';
    }
    {
      std::vector<int> vec {};
      std::cout << "Before: " << vec << '\n';

      // back_inserter allows inserts element at the end of the
      // given container
      // As we are using back_inserter so don't need to resize it
      std::fill_n(std::back_inserter(vec), 10, -1);
      std::cout << "After: " << vec << '\n';
    }
  }

  std::cout << "--- std::copy ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    std::vector<int> output {};

    std::copy(input.begin(), input.end(),
      std::back_inserter(output)
    );

    // Both input/output containers should be same
    std::cout << "Input:  " << input << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(input.size() == output.size());
  }

  std::cout << "--- std::copy_if ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    std::vector<int> output {};

    auto isItOdd = [](int num) {
        return ((num & 0x1) == 0x1);
    };
    std::copy_if(input.begin(), input.end(),
      std::back_inserter(output),
      isItOdd
    );

    // Output should only have odd numbers
    std::cout << "Input:  " << input << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(1 == output.size());
  }

  std::cout << "--- std::copy_n ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    std::vector<int> output {};

    std::copy_n(input.begin(), input.size(),
      std::back_inserter(output)
    );

    // Both input/output containers should be same
    std::cout << "Input:  " << input << std::endl;
    std::cout << "Output: " << output << std::endl;
    assert(input.size() == output.size());
  }

  return 0;
}
