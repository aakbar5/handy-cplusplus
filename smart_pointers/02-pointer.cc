//
// Program
//  Usage of unique pointer in different use-cases..
//    - Simple unique_pointer
//    - Empty unique_pointer via std::make_unique
//    - Empty unique_pointer
//    - std::move with unique_ptr
//    - Raw pointer access
//    - unique_ptr with array
//    - Custom deletor
//    - unique_ptr in map
//    - unique_ptr in class data member
//
// Compile
//  g++ -std=c++17 -o 02-pointer 02-pointer.cc
//
// Execution
//  ./02-pointer
//

#include <iostream>
#include <memory>
#include <map>

struct Test {
  std::string msg{"Test string"};

  Test() {
    std::cout << __func__  << "(default)" << '\n';
  }

  explicit Test(const std::string &m): msg(m) {
    std::cout << __func__ << "(param)" << '\n';
  }

  void show() {
    std::cout << "Message # " << this->msg << '\n';
  }

  std::string get() {
    return this->msg;
  }

  ~Test() {
    std::cout << __func__ << '\n';
  }
};

//
// Entry function
//
int main() {
  std::cout << "--- std::unique_ptr ---" << '\n';

  // Handling Test object via plain pointer
  std::cout << "--- plain pointer ---" << '\n';
  {
    Test *ptr = new Test();
    ptr->show();
    delete ptr;    // dtor should be called
  }

  // Handling of Test object via unique pointer
  std::cout << "--- simple unique_pointer ---" << '\n';
  {
    std::unique_ptr<Test> ptr(new Test());
    ptr->show();
    ptr.reset();        // dtor should be called
  }

  std::cout << "--- empty unique_pointer via std::make_unique ---" << '\n';
  {
    std::unique_ptr<Test> ptr = std::make_unique<Test>();
    ptr->show();
    // dtor should be called here
  }

  // An empty pointer
  std::cout << "--- empty unique_pointer ---" << '\n';
  {
    std::unique_ptr<Test> ptr; // no ctor should be called here as
                                // ptr is not initialized
    if (ptr.get())
      std::cout << "It is not empty" << '\n';
    else
      std::cout << "It is empty" << '\n';

    ptr.reset();        // no dtor should be called here
  }

  std::cout << "--- std::move with unique_ptr ---" << '\n';
  {
    std::unique_ptr<Test> ptr1(new Test());

    // std::unique_ptr<Test> ptr2 = new Test();     //ERROR
    // std:unique_ptr does not allow initialization
    // via assignment so should be initialized by value

    // std::unique_ptr<Test> ptr2(ptr1);            // ERROR -- can't copy it
    std::unique_ptr<Test> ptr2(std::move(ptr1));    // OKAY - it is moved

    // dtor should be called here
  }

  // Accessing raw pointer
  std::cout << "--- raw pointer access ---" << '\n';
  {
    std::unique_ptr<Test> ptr = std::make_unique<Test>();
    ptr->show();

    Test *ptr_raw = ptr.get();      // Access raw pointer
    ptr_raw->show();                // Call func using raw pointer

    // dtor should be called here
  }

  // Handling array of objects
  std::cout << "--- unique_ptr with array ---" << '\n';
  {
    const int size = 3;

    {
      std::unique_ptr<Test[]> ptr(new Test[size]);
      for (int i = 0; i < size; ++i) {
        ptr[i].show();
      }

      // dtor should be called here for
      // multiple times due to array count
    }

    // NOTE:
    // In book # Effective Modern C++ by Scott Meyers, he has said that:
    // |
    // | The existence of std::unique_ptr for arrays should be of only intellectual interest
    // | to you, because std::array, std::vector, and std::string are virtually always
    // | better data structure choices than raw arrays. About the only situation I can conceive
    // | of when a std::unique_ptr<T[]> would make sense would be when you’re using a
    // | C-like API that returns a raw pointer to a heap array that you assume ownership of.
    // |
    // Moreover in case of having array, you can't easily call parameterized ctor of
    // the class.

    {
      std::unique_ptr<Test[]> ptr(new Test[size]{Test("Obj1"),Test("Obj2"),Test("Obj3")});
      for (int i = 0; i < size; ++i) {
        ptr[i].show();
      }

      // dtor should be called here for
      // multiple times due to array count
    }
  }

  std::cout << "--- custom deletor ---" << '\n';
  {
    auto TestDeletor = [](Test *p) {
      std::cout << "custom delete func is called" << '\n';
      delete p;
    };
    std::unique_ptr<Test, decltype(TestDeletor)> ptr(new Test(), TestDeletor);
    ptr->show();

    // dtor should be called
  }

  std::cout << "--- unique_ptr in map ---" << '\n';
  {
    std::map<std::string, std::unique_ptr<Test>> map;

    // unique ptr using make_unique
    map["test1"] = std::make_unique<Test>("test1");

    // Entry into map using insert
    map.insert(std::make_pair("test2", std::make_unique<Test>("test2")));

    // Entry of an old ptr
    auto ptr = std::make_unique<Test>("test3");
    map["test3"] = std::move(ptr);

    for (const auto& m: map) {
      std::cout << m.second->get() << '\n';
    }
  }

  std::cout << "--- unique_ptr in class ---" << '\n';
  {
    struct Object {
      std::unique_ptr<Test> ptr;
      Object(): ptr(std::make_unique<Test>()) { std::cout << "Object()\n"; }
      void call() { ptr->show(); }
      ~Object() { std::cout << "~Object()\n"; }
    };

    Object obj {};
    obj.call();
  }

  return 0;
}

// Output
// --- std::unique_ptr ---
// --- plain pointer ---
// Test(default)
// Message # Test string
// ~Test
// --- simple unique_pointer ---
// Test(default)
// Message # Test string
// ~Test
// --- empty unique_pointer via std::make_unique ---
// Test(default)
// Message # Test string
// ~Test
// --- empty unique_pointer ---
// It is empty
// --- std::move with unique_ptr ---
// Test(default)
// ~Test
// --- raw pointer access ---
// Test(default)
// Message # Test string
// Message # Test string
// ~Test
// --- unique_ptr with array ---
// Test(default)
// Test(default)
// Test(default)
// Message # Test string
// Message # Test string
// Message # Test string
// ~Test
// ~Test
// ~Test
// Test(param)
// Test(param)
// Test(param)
// Message # Obj1
// Message # Obj2
// Message # Obj3
// ~Test
// ~Test
// ~Test
// --- custom deletor ---
// Test(default)
// Message # Test string
// custom delete func is called
// ~Test
// --- unique_ptr in map ---
// Test(param)
// Test(param)
// Test(param)
// test1
// test2
// test3
// ~Test
// ~Test
// ~Test
// --- unique_ptr in class ---
// Test(default)
// Object()
// Message # Test string
// ~Object()
// ~Test
