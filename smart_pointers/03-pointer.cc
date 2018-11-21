//
// Program
//  This program simply creates shared pointer.
//
// Compile
//  g++ -std=c++17 -o 03-pointer 03-pointer.cc
//
// Execution
//  ./03-pointer
//

#include <iostream>
#include <memory>

struct Test {
  std::string msg{"Test string"};

  Test() {
    std::cout << __func__  << "(default)" << '\n';
  }

  explicit Test(const std::string& m): msg(m) {
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
  std::cout << "--- std::shared_ptr ---" << '\n';

  // Handling Test object via plain pointer
  std::cout << "--- plain pointer ---" << '\n';
  {
    Test *ptr = new Test();
    ptr->show();
    delete ptr;    // dtor should be called
  }

  // Handling of Test object via shared pointer
  std::cout << "--- simple shared_pointer ---" << '\n';
  {
    std::shared_ptr<Test> ptr(new Test());
    ptr->show();
    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    // dtor should be called
  }

  std::cout << "--- simple shared_pointer via std::make_shared ---" << '\n';
  {
    std::shared_ptr<Test> ptr = std::make_shared<Test>();
    ptr->show();
    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    // dtor should be called
  }

  std::cout << "--- 2x shared_pointer via std::make_shared ---" << '\n';
  {
    std::shared_ptr<Test> ptr = std::make_shared<Test>();
    ptr->show();
    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    std::shared_ptr<Test> ptr_2 = ptr;
    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 2
    ptr_2.reset();
    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    // dtor should be called
  }

  // An empty pointer
  std::cout << "--- empty shared_pointer ---" << '\n';
  {
    std::shared_ptr<Test> ptr; // no ctor should be called here as
                                // ptr is not initialized

    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 0

    if (ptr == nullptr)
      std::cout << "pointer is nullptr" << '\n';

    if (!ptr)
      std::cout << "pointer is nullptr" << '\n';

    ptr.reset();        // no dtor should be called here
  }

  // Accessing raw pointer
  std::cout << "--- raw pointer access ---" << '\n';
  {
    std::shared_ptr<Test> ptr = std::make_shared<Test>();
    ptr->show();

    {
      std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

      Test *ptr_raw = ptr.get();      // Access raw pointer
      ptr_raw->show();                // Call func using raw pointer

      std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1
    }

    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    // dtor should be called here
  }

  std::cout << "--- custom deletor ---" << '\n';
  {
    auto TestDeletor = [](Test *p) {
      std::cout << "custom delete func is called" << '\n';
      delete p;
    };
    std::shared_ptr<Test> ptr(new Test(), TestDeletor);
    ptr->show();

    // dtor should be called
  }

  std::cout << "--- custom deletor ---" << '\n';
  {
    auto TestDeletor = [](Test *p) {
      std::cout << "custom delete func is called" << '\n';
      delete []p;
    };
    std::shared_ptr<Test[]> ptr(new Test[5], TestDeletor);

    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    ptr[0].show();
    ptr[1].show();
    ptr[2].show();
    ptr[3].show();

    std::cout << "Use count: " << ptr.use_count() << '\n'; // Use count should be 1

    // dtor should be called
  }

  std::cout << "--- shared_ptr for simple integer pointer ---" << '\n';
  {
    std::shared_ptr<unsigned int> ptr = std::make_shared<unsigned int>(100);
    std::cout << "Value of ptr is " << *ptr << '\n';

    *ptr = 102;
    std::cout << "Value of ptr is " << *ptr << '\n';

    *(ptr.get()) = 104;
    std::cout << "Value of ptr is " << *ptr << '\n';
  }

  std::cout << "--- pointer comparison ---" << '\n';
  {
    std::shared_ptr<unsigned int> ptr_uni = std::make_shared<unsigned int>(100);
    std::shared_ptr<unsigned int> ptr_dup_1 = std::make_shared<unsigned int>(100);
    std::shared_ptr<unsigned int> ptr_dup_2(ptr_dup_1);
    std::shared_ptr<unsigned int> ptr_empty(nullptr);

    // Return address of the resource managed by shared_pointer
    std::cout << "ptr_uni @ address:      " << ptr_uni << '\n';            // ptr_uni @ address: 0xxxxxxx7702c0
    std::cout << "ptr_uni @ address:      " << ptr_uni.get() << '\n';      // ptr_uni @ address: 0xxxxxxx7702c0

    std::cout << "ptr_dup_1 @ address:    " << ptr_dup_1 << '\n';          // ptr_dup_1 @ address: 0xxxxxxx7703d0
    std::cout << "ptr_dup_1 @ address:    " << ptr_dup_1.get() << '\n';    // ptr_dup_1 @ address: 0xxxxxxx7703d0

    std::cout << "ptr_uni == ptr_dup_1:   " << std::boolalpha << (ptr_uni == ptr_dup_1) << '\n';   // False
    std::cout << "ptr_uni < ptr_dup_1:    " << std::boolalpha << (ptr_uni < ptr_dup_1) << '\n';    // True -- Check addresses
    std::cout << "ptr_dup_1 == ptr_dup_2: " << std::boolalpha << (ptr_dup_1 == ptr_dup_2) << '\n'; // True

    if (ptr_uni)
      std::cout << "ptr_uni is valid" << '\n';       // ptr_uni is valid

    if (!ptr_empty)
      std::cout << "ptr_empty is empty" << '\n';     // ptr_empty is empty

    if (ptr_empty == nullptr)
      std::cout << "ptr_empty is empty" << '\n';     // ptr_empty is empty
  }

  return 0;
}
