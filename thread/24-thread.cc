//
// Program
//  This program utilizes std::shared_lock. Same as std::shared_mutex usage
//  however makes use of std::shared_lock for lock management instead of
//  directly calling std::shared_mutex interface.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 24-thread 24-thread.cc
//
// Execution
//  ./24-thread
//

#include <iostream>
#include <thread>
#include <shared_mutex>

using namespace std::chrono_literals;

//
// Function to be called for thread
//
static void thread_reader_func(std::shared_mutex& smutex) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  std::this_thread::sleep_for(3s);

  while (true) {
    {
      std::shared_lock<std::shared_mutex> lock(smutex);
      std::cout << "Thread id # " << id << " rl" << '\n';

      std::this_thread::sleep_for(4s);
    }

    std::cout << "Thread id # " << id << " rr" << '\n';
  }
}

//
// Function to be called for thread
//
static void thread_writer_func(std::shared_mutex& smutex) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  std::this_thread::sleep_for(1s);

  while (true) {
    {
      std::shared_lock<std::shared_mutex> lock(smutex);
      std::cout << "Thread id # " << id << " wl" << '\n';

      std::this_thread::sleep_for(2s);
    }

    std::cout << "Thread id # " << id << " wr" << '\n';
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- Shared lock ---" << '\n';

  std::shared_mutex smutex;

  std::thread t1(thread_reader_func, std::ref(smutex));
  std::thread t2(thread_reader_func, std::ref(smutex));
  std::thread t3(thread_writer_func, std::ref(smutex));

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
