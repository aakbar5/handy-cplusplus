//
// Program
//  std::erase/std::erase_if vs std::remove/std::remove_if
//  https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o erase_remove erase_remove.cc
//
// Execution
//  ./erase_remove
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <vector>

template <typename T>
void show(const std::vector<T>& container) {
  std::copy(std::begin(container), std::end(container),
    std::ostream_iterator<T>(std::cout, " "));
  std::cout << '\n';
}

void test_remove() {
  std::vector<int> input {1, 2, 3, 4, 5};

  std::cout << "vanilla container    (" << input.size() << "): ";
  show<int>(input);

  // Required elements are removed however container
  // size remains the same
  std::remove_if(std::begin(input), std::end(input),
    [](auto &num) {
        return ((num & 1) == 0);
    }
  );

  std::cout << "remove_if container  (" << input.size() << "): ";
  show<int>(input);
}

void test_erase() {
  std::vector<int> input {1, 2, 3, 4, 5};

  std::cout << "remove_if/erase container  (" << input.size() << "): ";
  show<int>(input);

  auto new_end = std::remove_if(std::begin(input), std::end(input), [](auto &num) {
    return ((num & 1) == 0);
  });

  //iterator erase( iterator first, iterator last );
  // Remove all b/w new and old end
  input.erase(new_end, std::end(input));

  std::cout << "remove_if/erase container  (" << input.size() << "): ";
  show<int>(input);
}

int main()
{
  std::cout << "Test # remove_if: " << '\n';
  test_remove();

  std::cout << "Test # remove_if + erase: " << '\n';
  test_erase();

  return 0;
}
