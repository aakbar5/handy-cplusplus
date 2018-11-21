//
// Program
//  Create a task using std::async and waits for its results.
//  std::async allows you to deal with task which are being started immediately in the
//  background whereas std::packaged_task allows you to deal with a task which is not being
//  started immediately.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 60-thread 60-thread.cc
//
// Execution
//  ./60-thread
//

#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

//
// Function to be called for async
//
static int async_callback(void) {
  auto id = std::this_thread::get_id();
  std::cout << "Thread id # " << id << " is having " << __func__ << " function" << '\n';

  std::cout << "Thread id # " << id << " is doing job" << '\n';
  std::this_thread::sleep_for(3s);

  std::cout << "Thread id # " << id << " is complete" << '\n';
  return 100;
}

//
// Entry function
//
int main() {
  std::cout << "--- std::async ---" << '\n';

  // The first parameter of std::async defines the launch policy. There are 3 options:
  // - std::launch::async: Runs passed function in a separate thread. Execution behaviour
  //                       is asynchronous.
  // - std::launch::deferred: Run passed function in the same thread context and its execution
  //                          will be deferred until caller forces for its execution by calling
  //                          .get function.
  std::future<int> fut_async = std::async(std::launch::async, async_callback);

  std::cout << "main is busy in doing other job..." << '\n';
  std::this_thread::sleep_for(2s);

  std::cout << "Get results from async..." << '\n';
  std::cout << "Result is " << fut_async.get() << '\n';

  return 0;
}
