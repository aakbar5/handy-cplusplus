//
// Program
//  Create multiple async and save respective future to a container.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 64-thread 64-thread.cc
//
// Execution
//  ./64-thread
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

//
// Function to be called for async
//
static void async_callback(int idx) {
  auto id = std::this_thread::get_id();
  std::cout << "Thread id # " << id << " is having seed # " << idx << '\n';

  std::cout << "Thread id # " << id << " is doing job" << '\n';
  std::this_thread::sleep_for(3s);

  std::cout << "Thread id # " << id << " is complete" << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- std::async with std::vector ---" << '\n';
  constexpr int count = 3;

  std::vector <std::future<void>> futures;
  for (int idx = 0; idx < count; ++idx) {
    // Use emplace_back as std::future is not copyable otherwise
    // use std::move to push to container
    futures.emplace_back(std::async(std::launch::async, async_callback, idx + 100));
  }

  std::cout << "main is busy in doing other job..." << '\n';
  std::this_thread::sleep_for(2s);

  std::cout << "main is waiting/extracting results from async..." << '\n';
  for (int idx = 0; idx < count; ++idx) {
    if (futures[idx].valid()) {
      futures[idx].wait();
    }
    else {
      std::cout << "async id # " << idx << " is invalid" << '\n';
    }
  }

  return 0;
}
