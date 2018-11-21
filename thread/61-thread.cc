//
// Program
//  std::packaged_task takes a callable target allows to reterieve its result
//  via std::future.
//  std::async allows you to deal with task which are being started immediately in the
//  background whereas std::packaged_task allows you to deal with a task which is not being
//  started immediately.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 61-thread 61-thread.cc
//
// Execution
//  ./61-thread
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
  std::cout << "--- std::packaged_task ---" << '\n';

  std::packaged_task<int(void)> pack_tsk(async_callback);

  // Fetch future as package_task will be moved to its
  std::future<int> fut_async = pack_tsk.get_future();

  std::cout << "main is busy in doing other job..." << '\n';
  std::this_thread::sleep_for(2s);

  // pack_tsk is not copyable
  std::thread t(std::move(pack_tsk));
  t.join();

  std::cout << "main is busy in doing another job..." << '\n';
  std::this_thread::sleep_for(2s);

  std::cout << "Get results from async..." << '\n';
  std::cout << "Result is " << fut_async.get() << '\n';

  return 0;
}
