//
// Program
//  Using std::shared_ptr with atomic
//  As per https://en.cppreference.com/w/cpp/memory/shared_ptr/atomic2
//  If multiple threads of execution access the same std::shared_ptr
//  object without synchronization and any of those accesses uses a
//  non-const member function of shared_ptr then a data race will occur
//  unless all such access is performed through an instance of
//  std::atomic<std::shared_ptr>>.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 05-atomic 05-atomic.cc
//
// Execution
//  ./05-atomic
//

#include <iostream>
#include <sstream>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>

using namespace std::chrono_literals;

struct Test {
  std::string msg{"Test: Default string"};

  Test() {
    std::cout << "Test: Func # " << __func__ << "(default)" << '\n';
  }

  explicit Test(const std::string& m): msg(m) {
    std::cout << "Test: Func # " << __func__ << "(param)" << '\n';
  }

  void show() {
    std::cout << "Test: Message is " << this->msg << '\n';
  }

  ~Test() {
    std::cout << "Test: Func # " << __func__ << '\n';
  }
};

//
// Function to be called for thread
//
static void thread_callback(std::shared_ptr<Test> ptr) {
  std::stringstream s_id;
  s_id << std::this_thread::get_id();

  ptr->show();

  std::cout << __func__ << '\n'
            << "\tThread Id: " << s_id.str() << '\n'
            << "\tUse count: " << ptr.use_count() << '\n';

  // We are changing object so without any protection it will have
  // data race. One can use mutex to avoid it.
  // ptr = std::make_shared<Test>("By thread # " + s_id.str());

  // Howver using atomic Ops are lightweight solution to avoid data race
  auto new_ptr = std::make_shared<Test>("By thread # " + s_id.str());
  std::atomic_store(&ptr, new_ptr);

  std::cout << __func__ << '\n'
            << "\tThread Id: " << s_id.str() << '\n'
            << "\tUse count: " << ptr.use_count() << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- std::atomic & std::shared_ptr ---" << '\n';

  std::shared_ptr<Test> ptr = std::make_shared<Test>();
  ptr->show();
  std::cout << "Use count: " << ptr.use_count() << '\n';

  constexpr int count = 2;
  std::vector<std::thread> threads(count);

  for (auto i = 0; i < count; ++i) {
    threads[i] = std::thread(thread_callback, ptr);
  }

  for (auto &t: threads) {
    t.join();
  }

  std::cout << "Use count: " << ptr.use_count() << '\n';

  std::cout << "Good bye!" << '\n';

  return 0;
}
