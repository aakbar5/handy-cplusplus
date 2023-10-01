//
// Program
//  <algorithm> @ copy usage.
//    - std::copy (vector <> vector)
//    - std::copy_if (vector <> vector)
//    - std::copy_n (vector <> vector)
//    - std::copy_n (vector <> vector)
//    - std::copy_n (vector <> array)
//    - std::copy_n (vector <> array using raw pointer)
//    - std::copy/copy_n (vector <> array of structure)
//    - std::copy_backward (vector <> array of structure)
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o algorithm_copy algorithm_copy.cc
//
// Execution
//  ./algorithm_copy
//

#include <iostream>
#include <algorithm>
#include <cassert>

constexpr int SIZE = 6;

struct pack {
  int ival;
  float fval;
};

// Util function to print vector
static std::ostream& operator<< (std::ostream& out, const std::vector<int>& vec) {

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

  std::cout << "--- std::copy (vector <> vector) ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    std::vector<int> output {};

    assert(3 == input.size());
    assert(0 == output.size());

    std::copy(input.begin(), input.end(),
      std::back_inserter(output)
    );

    // Both input/output containers should be same
    std::cout << "Input:  " << input << '\n';
    std::cout << "Output: " << output << '\n';

    assert(input.size() == output.size());
  }

  std::cout << "--- std::copy_if (vector <> vector) ---" << '\n';
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
    std::cout << "Input:  " << input << '\n';
    std::cout << "Output: " << output << '\n';
    assert(1 == output.size());
  }

  std::cout << "--- std::copy_n (vector <> vector) ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    std::vector<int> output {};

    assert(3 == input.size());
    assert(0 == output.size());

    std::copy_n(input.begin(), input.size(),
      std::back_inserter(output)
    );

    // Both input/output containers should be same
    std::cout << "Input:  " << input << '\n';
    std::cout << "Output: " << output << '\n';

    assert(input.size() == output.size());
  }

  std::cout << "--- std::copy_n (vector <> vector) ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    std::vector<int> output {};
    output.resize(input.size());

    assert(input.size() == output.size());

    std::copy_n(input.begin(), input.size(), output.begin());

    // Both input/output containers should be same
    std::cout << "Input:  " << input << '\n';
    std::cout << "Output: " << output << '\n';

    assert(input.size() == output.size());
  }

  std::cout << "--- std::copy_n (vector <> array) ---" << '\n';
  {
    std::vector<int> input { 2, 3, 4 };
    int output[4];

    std::copy_n(input.begin(), std::size(output), std::begin(output));

    // Both input/output containers should be same
    std::cout << "Input:  " << input << '\n';
    std::cout << "Output: " << output << '\n';
  }

  std::cout << "--- std::copy_n (vector <> array using raw pointer)" << '\n';
  {
    constexpr int size = 4;

    std::vector<int> input { 2, 3, 4 };
    int output[size] = {0};

    {
      // NOTE: A risky approach as vector can move its data location (ie on resize)
      //       In that case you may end up with danging pointer
      int *ptr = input.data();
      for (int i = 0; i < size; ++i) {
        output[i] = ptr[i];
      }
    }

    std::cout << "Input:  " << input << '\n';
    std::cout << "Output: " << output << '\n';
  }

  std::cout << "--- std::copy/copy_n (vector <> array of structure)" << '\n';
  {
    std::vector<pack> pack_vec(SIZE);
    for (int i = 0; i < SIZE; ++i) {
      pack_vec[i].ival = i + 0;
      pack_vec[i].fval = i + 0.1f;
    }

    std::cout << " [Input]\n";
    for (int i = 0; i < SIZE; ++i) {
      std::cout << '(' << pack_vec[i].ival << "," <<  pack_vec[i].fval << ')' << ' ';
    }
    std::cout << '\n';

    pack pack_arr[SIZE] = {0, 0.0f};
    for (int i = 0; i < SIZE; ++i) {
      std::cout << '(' << pack_arr[i].ival << "," <<  pack_arr[i].fval << ')' << ' ';
    }
    std::cout << '\n';

    {
      // std::copy(std::begin(pack_vec), std::end(pack_vec), pack_arr);
      std::copy_n(std::begin(pack_vec), SIZE, pack_arr);
    }

    std::cout << " [Output]\n";
    for (int i = 0; i < SIZE; ++i) {
      std::cout << '(' << pack_arr[i].ival << "," <<  pack_arr[i].fval << ')' << ' ';
    }
    std::cout << '\n';
  }

  std::cout << "--- std::copy_backward (vector <> array of structure)" << '\n';
  {
    std::vector<pack> pack_vec(SIZE);
    for (int i = 0; i < SIZE; ++i) {
      pack_vec[i].ival = i + 0;
      pack_vec[i].fval = i + 0.1f;
    }

    std::cout << " [Input]\n";
    for (int i = 0; i < SIZE; ++i) {
      std::cout << '(' << pack_vec[i].ival << "," <<  pack_vec[i].fval << ')' << ' ';
    }
    std::cout << '\n';

    pack pack_arr[SIZE] = {0, 0.0f};
    for (int i = 0; i < SIZE; ++i) {
      std::cout << '(' << pack_arr[i].ival << "," <<  pack_arr[i].fval << ')' << ' ';
    }
    std::cout << '\n';

    {
      std::copy_backward(pack_vec.begin(), pack_vec.end(), &pack_arr[SIZE]);
    }

    std::cout << " [Output]\n";
    for (int i = 0; i < SIZE; ++i) {
      std::cout << '(' << pack_arr[i].ival << "," <<  pack_arr[i].fval << ')' << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
