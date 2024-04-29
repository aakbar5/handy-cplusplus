//
// Program
//  Remove an element from the container.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 12-containers 12-containers.cc
//
// Execution
//  ./12-containers
//
#include <iostream>
#include <vector>
#include <chrono>

struct Info {
  int id;
  int score;
  std::string name;
};

int get_sum(std::vector<Info>& vec)
{
  int total = 0;

  const int size = vec.size();
  for (int i = 0; i < size; ++i) {
    if (vec[i].id != -1) {
      total += vec[i].score;
    }
  }
  return total;
}

void popuplate(int count, std::vector<Info>& vec)
{
  for (int idx = 0; idx < count; ++idx) {
    vec.emplace_back(Info{idx, idx * 10, "name" + std::to_string(idx)});
  }
}

void removeElementByPopBack(int index, std::vector<Info>& vec)
{
  const int size = vec.size() - 1;
  if (index != size) {
    vec[index] = vec.back();
  }
  vec.pop_back();
}

void removeElementByIterator(int index, std::vector<Info>& vec)
{
  auto iter = vec.begin() + index;
  vec.erase(iter);
}

//
// Entry function
//
int main() {

  constexpr int count = 100'000;

  // Remove element by marking index -1
  // Effectively element is there but we will ignore it as id is not valid
  {
    std::vector<Info> vec {};
    popuplate(count, vec);

    vec[500].id = -1;
    vec[505].id = -1;
    vec[507].id = -1;

    int sum = 0;
    auto start = std::chrono::high_resolution_clock::now();
    {
      sum = get_sum(vec);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Mark id to -1:        " << vec.size() << " in " << us.count() << " usec" << '\n';

    (void)sum;
  }

  // Remove element from the vector by swapping it to the last element
  {
    int sum = 0;
    std::vector<Info> vec {};
    popuplate(count, vec);

    removeElementByPopBack(500, vec);
    removeElementByPopBack(505, vec);
    removeElementByPopBack(507, vec);

    auto start = std::chrono::high_resolution_clock::now();
    {
      sum = get_sum(vec);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Swap last element:    " << vec.size() << " in " << us.count() << " usec" << '\n';

    (void)sum;
  }

  // Remove element from the vector by using iterator from the index
  {
    int sum = 0;
    std::vector<Info> vec {};
    popuplate(count, vec);

    removeElementByIterator(500, vec);
    removeElementByIterator(505, vec);
    removeElementByIterator(507, vec);

    auto start = std::chrono::high_resolution_clock::now();
    {
      sum = get_sum(vec);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Using erase by index: " << vec.size()
              << " in " << us.count() << " usec" << '\n';

    (void)sum;
  }

  return 0;
}
