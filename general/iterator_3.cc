//
// Program
//  A simple collection class with read iterator.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o iterator_3 iterator_3.cc
//
// Execution
//  ./iterator_3
//

#include <iostream>
#include <vector>

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

  void show() const {
    for (int i = 0; i < _size; ++i)
      std::cout << _data[i] << " ";
    std::cout << '\n';
  }

  class iterator {
  public:
    explicit iterator(T *ptr): _current(ptr) {}

    iterator& operator++() {
      ++_current;
      return *this;
    }

    T& operator*() {
      return *_current;
    }

    bool operator< (const iterator& rhs) { return  (_current < rhs._current); }
    bool operator> (const iterator& rhs) { return  (rhs._current < _current); }
    bool operator<=(const iterator& rhs) { return !(_current > rhs._current); }
    bool operator>=(const iterator& rhs) { return !(_current < rhs._current); }
    bool operator==(const iterator& rhs) { return  (_current == rhs._current); }
    bool operator!=(const iterator& rhs) { return !(_current == rhs._current); }

  private:
    T* _current;
  };

  iterator begin() const { return iterator(&_data[0]); }
  iterator end() const { return iterator(&_data[_size - 1]); }
};

int main() {
  std::cout << "---- Iterator implementation - 3 -----" << '\n';

  {
    std::cout << "*** std::vector ***" << '\n';

    std::vector<int> vec{10, 20, 30};
    std::cout << "std::begin " << *std::begin(vec) << '\n';
    std::cout << "std::end   " << *std::end(vec) << '\n';

    std::cout << "--- range loop ---" << '\n';
    for (auto &it: vec) {
      std::cout << it << " ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "*** custom collection ***" << '\n';

    Collection<int> list(3);
    list.insert(10);
    list.insert(20);
    list.insert(30);
    ASSERT(list.is_full() == true);

    std::cout << "--- simple show ---" << '\n';
    list.show();

    auto vi = std::begin(list);
    std::cout << "std::begin: " << *vi << '\n';

    auto ve = std::end(list);
    std::cout << "std::end: " << *ve << '\n';

    std::cout << "--- for loop # range loop ---" << '\n';
    for (auto &it: list) {
      std::cout << it << " ";
    }
    std::cout << '\n';

    std::cout << "--- for loop # begin/end @ != ---" << '\n';
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
      std::cout << *iter << " ";
    }
    std::cout << '\n';
    std::cout << "--- for loop # begin/end @ <= ---" << '\n';
    for (auto iter = list.begin(); iter <= list.end(); ++iter) {
      std::cout << *iter << " ";
    }
    std::cout << '\n';
  }

  return 0;
}
