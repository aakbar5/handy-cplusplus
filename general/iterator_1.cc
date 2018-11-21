//
// Program
//  A simple collection class to be used as a base for iterator implementation.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o iterator_1 iterator_1.cc
//
// Execution
//  ./iterator_1
//

#include <iostream>

#define ASSERT(expr)                                                                \
  if (!(expr)) {                                                              \
    std::cerr << "Assert error!" << #expr << __FILE__ << __LINE__;          \
    std::abort();                                                           \
  }

template <typename T>
class Collection {
private:
  int _capacity;
  int _size;
  T *_data;

public:
  explicit Collection(int capacity):
          _capacity(capacity), _size(0),
          _data(new T[_capacity]{}) {}

  Collection(const Collection&) = delete;
  Collection& operator= (const Collection &) = delete;

  ~Collection() {
      delete []_data;
  }

  bool is_empty() const { return (_size == 0); }
  bool is_full() const { return (_size >= _capacity); }
  int size() const { return _size; }
  int capacity() const { return _capacity; }

  void insert(const T& elem) {
    if (is_full())
      throw std::runtime_error("collection is already full");

    _data[_size++] = elem;
  }

  T remove() {
    if (is_empty())
      throw std::runtime_error("collection is empty");

    return _data[--_size];
  }

  void show() const {
    for (int i = 0; i < _size; ++i)
        std::cout << _data[i] << " ";
    std::cout << '\n';
  }
};

int main() {
  std::cout << "---- Iterator implementation - 1 -----" << '\n';

  {
    Collection<int> list(3);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    ASSERT(list.is_full() == true);

    std::cout << "Contents of collection: ";
    list.show();

    std::cout << "Remove contents: ";
    std::cout << list.remove() << " ";
    std::cout << list.remove() << " ";
    std::cout << list.remove() << '\n';
    ASSERT(list.is_empty() == true);
  }

  {
    Collection<int> list(1);
    ASSERT(list.is_full() == false);

    std::cout << "Contents of collection: ";
    list.show();
  }

  return 0;
}
