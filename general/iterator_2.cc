//
// Program
//  A simple collection class with begin and end functions
//  to iterate the collection.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o iterator_2 iterator_2.cc
//
// Execution
//  ./iterator_2
//

#include <iostream>

#define ASSERT(expr)                                                        \
  if (!(expr)) {                                                            \
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

  T* begin() const {
    return &_data[0];
  }

  T* end() const {
    return &_data[_size];
  }

  void show() const {
    for (int i = 0; i < _size; ++i)
      std::cout << _data[i] << " ";
    std::cout << '\n';
  }
};

int main() {
  std::cout << "---- Iterator implementation - 2 -----" << '\n';

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
    Collection<int> list(3);
    list.insert(1);
    list.insert(2);
    list.insert(3);
    ASSERT(list.is_full() == true);

    std::cout << "Contents of collection: ";
    list.show();

    std::cout << "Contents of collection via begin/end: ";
    for (auto ptr = list.begin(); ptr != list.end(); ++ptr) {
        std::cout << *ptr << " ";
    }
    std::cout << '\n';
  }

  return 0;
}
