//
// Design pattern # strategy
//  Lets you to select different behaviour at runtime.
//
// g++ -std=c++17 -Wall -Wextra -o strategy strategy.cc
//
#include <iostream>

struct SearchStrategy {
  virtual void search() = 0;
};

struct BinaryTree: SearchStrategy {
  void search() override {
    std::cout << "Search data using binary tree\n";
  }
};

struct Sequential: SearchStrategy {
  void search() override {
    std::cout << "Search data using sequential\n";
  }
};

struct Collection {
  SearchStrategy *strategy;

  void set_strategy(SearchStrategy *stategy) {
    this->strategy = stategy;
  }
  void search() {
    this->strategy->search();
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # strategy\n";
  Collection collection;

  collection.set_strategy(new Sequential());
  collection.search();

  collection.set_strategy(new BinaryTree());
  collection.search();

  return 0;
}
