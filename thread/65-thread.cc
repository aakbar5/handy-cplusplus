//
// Program
//  Create multiple async and save their future to a container. Use these
//  futures to extract results from async.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 65-thread 65-thread.cc
//
// Execution
//  ./65-thread
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

//
// Entry function
//
int main() {
  std::cout << "--- std::async with std::vector ---" << '\n';
  constexpr int count = 3;

  // Function to be called for async
  auto func = [](int idx) {
    auto id = std::this_thread::get_id();
    std::cout << "Thread id # " << id << " is having seed # " << idx << '\n';

    std::cout << "Thread id # " << id << " is doing job" << '\n';
    std::this_thread::sleep_for(3s);

    std::cout << "Thread id # " << id << " is complete" << '\n';
    return idx - 100;
  };

  std::vector <std::future<int>> futures;
  for (int idx = 0; idx < count; ++idx) {
    // Use emplace_back as std::future is not copyable otherwise
    // use std::move to push to container
    futures.emplace_back(std::async(std::launch::async, func, idx + 100));
  }

  std::cout << "main is busy in doing other job..." << '\n';
  std::this_thread::sleep_for(2s);

  std::cout << "main is waiting/extracting results from async..." << '\n';
  for (int idx = 0; idx < count; ++idx) {
    if (futures[idx].valid()) {
      futures[idx].wait();
      std::cout << "async id # " << idx << " has sent result # " << futures[idx].get() << ":" << futures[idx].valid() << '\n';
    }
    else {
      std::cout << "async id # " << idx << " has nothing to share" << '\n';
    }
  }

  return 0;
}
