//
// Program
//  Mutex management (std::unique_lock). Two threads try to modify the
//  object. After getting hold of mutex before doing actual modification
//  thread will sleep for a while forcing other thread to wait until it
//  becomes free.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 26-thread 26-thread.cc
//
// Execution
//  ./26-thread
//

#include <iostream>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

//
// Global data shared b/w threads
//
struct Account {
  Account(std::uint32_t id, std::uint32_t balance): _id(id), _balance(balance) {}
  std::string to_string() {
    return std::string("Account # ") + std::to_string(_id) + std::string (" is having balance ") + std::to_string(_balance);
  }

  std::uint32_t _id;
  std::uint32_t _balance;
  std::mutex _mutex;
};

void add_balance(std::uint32_t amount, Account &to) {
  // Create a lock without locking mutex
  std::unique_lock<std::mutex> lock(to._mutex, std::defer_lock);
  volatile bool done = false;

  while (done == false) {
    if (lock.try_lock()) {
      std::cout << std::this_thread::get_id() << " ()" << '\n';

      std::this_thread::sleep_for(2s);
      to._balance += amount;
      done = true;
    }
    else {
      std::cout << std::this_thread::get_id() << " ++" << '\n';
    }
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- Unique lock ---" << '\n';

  Account p1(10, 500);
  std::cout << p1.to_string() << '\n';

  std::thread t1(add_balance, 100, std::ref(p1));
  std::thread t2(add_balance, 300, std::ref(p1));

  t1.join(); // Wait for the thread until it completes its execution
  t2.join(); // Wait for the thread until it completes its execution

  std::cout << p1.to_string() << '\n';

  return 0;
}
