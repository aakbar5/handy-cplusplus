//
// Program
//  Creates two threads which waits on a condition
//  variable sent by another function.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 30-thread 30-thread.cc
//
// Execution
//  ./30-thread
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std::chrono_literals;

//
// Data used by the example
//
struct Data {
  Data():mutex(), cond() {}
  std::mutex mutex;
  std::condition_variable cond;
};

//
// Function to be called for thread
//
static void thread_callback_1(Data& data) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  std::cout << "Thread id # " << id << " is locking mutex to wait on condition" << '\n';
  std::unique_lock<std::mutex> lock(data.mutex);
  data.cond.wait(lock);

  std::cout << "Thread id # " << id << " is having condition signal..." << '\n';

  for (int i=1; i < 5; ++i) {
    std::this_thread::sleep_for(1s);
  }

  std::cout << "Thread id # " << id << " is complete" << '\n';
}

//
// Function to be called for thread
//
static void thread_callback_2(Data& data) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  std::cout << "Thread id # " << id << " is locking mutex to wait on condition" << '\n';
  std::unique_lock<std::mutex> lock(data.mutex);
  data.cond.wait(lock);

  std::cout << "Thread id # " << id << " is having condition signal..." << '\n';

  for (int i=1; i < 5; ++i) {
    std::this_thread::sleep_for(1s);
  }

  std::cout << "Thread id # " << id << " is complete" << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- Condition variable ---" << '\n';

  Data data;

  std::thread t1(thread_callback_1, std::ref(data));
  std::thread t2(thread_callback_2, std::ref(data));

  std::cout << "main is sleeping for 4s..." << '\n';
  std::this_thread::sleep_for(4s);

  std::cout << "Sending notification to threads..." << '\n';
  data.cond.notify_all(); // send notification to all threads waiting on cv

  std::cout << "Waiting for threads..." << '\n';
  t1.join();
  t2.join();

  return 0;
}
