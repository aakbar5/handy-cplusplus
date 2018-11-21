//
// Program
//  Mutex management (std::scoped_lock).
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 25-thread 25-thread.cc
//
// Execution
//  ./25-thread
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

void move_balance(std::uint32_t amount, Account &from, Account &to) {
  std::scoped_lock lock(from._mutex, to._mutex);
  if (amount <= from._balance) {
    from._balance -= amount;
    to._balance += amount;
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- Scoped lock ---" << '\n';

  Account p1(10, 1000);
  Account p2(20, 2000);
  std::cout << p1.to_string() << '\n';
  std::cout << p2.to_string() << '\n';

  std::thread t1(move_balance, 100, std::ref(p1), std::ref(p2));
  std::thread t2(move_balance, 300, std::ref(p1), std::ref(p2));

  t1.join(); // Wait for the thread until it completes its execution
  t2.join(); // Wait for the thread until it completes its execution

  std::cout << p1.to_string() << '\n';
  std::cout << p2.to_string() << '\n';

  return 0;
}
