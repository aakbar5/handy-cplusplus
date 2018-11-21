//
// Program
//  This program simply creates a recursive mutex.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 21-thread 21-thread.cc
//
// Execution
//  ./21-thread
//

#include <iostream>
#include <thread>
#include <mutex>

using namespace std::chrono_literals;

//
// Function to be called to access shared resource
//
static void shared_resource(std::recursive_mutex& rmutex, std::thread::id thread_id, int repeat)
{
  try {
    for (int i = 0; i < repeat; ++i) {
      rmutex.lock();
      std::cout << "# " << i << ": shared_resource is used by thread # " << thread_id << '\n';
      rmutex.unlock();
    }
  } catch(const std::system_error& e) {
    std::cout << "Caught system_error" << '\n'
              << " - error code: " << e.code() << '\n'
              << " - message:    " << e.what() << '\n';
  }
}

//
// Function to be called for thread
//
static void thread_callback_1(std::recursive_mutex& rmutex) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  for (int i=1; i < 5; ++i) {
    shared_resource(rmutex, id, i);
    std::this_thread::sleep_for(2s);
  }
}

//
// Function to be called for thread
//
static void thread_callback_2(std::recursive_mutex& rmutex) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  for (int i=1; i < 6; ++i) {
    shared_resource(rmutex, id, i);
    std::this_thread::sleep_for(3s);
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- Recursive mutex ---" << '\n';

  std::recursive_mutex rmutex;

  std::thread t1(thread_callback_1, std::ref(rmutex));
  std::thread t2(thread_callback_2, std::ref(rmutex));
  t1.join();
  t2.join();

  return 0;
}
