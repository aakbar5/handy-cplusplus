//
// Program
//  This program simply creates unique pointer.
//
// Compile
//  g++ -std=c++17 -o 02-pointer 02-pointer.cc
//
// Execution
//  ./02-pointer
//

#include <iostream>
#include <memory>

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

  return 0;
}
