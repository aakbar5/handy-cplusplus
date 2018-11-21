//
// Program
//  Two threads (Producer & Consumer) communicate with each via
//  std::promise and std::future.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 62-thread 62-thread.cc
//
// Execution
//  ./62-thread
//

#include <iostream>
#include <thread>
#include <future>

using namespace std::chrono_literals;

//
// Function to be called for thread
//
void consumer_func(std::future<int> &future) {
  std::cout << "Consumer: is up..." << '\n';

  // Wait for value to set on promise
  std::cout << "Consumer: is waiting for promise..." << '\n';
  future.wait();

  std::cout << "Consumer: Got value # " << future.get() << '\n';
}

//
// Function to be called for thread
//
void producer_func(std::promise<int> &promise) {
  std::cout << "Producer: is up..." << '\n';

  std::cout << "Producer: is doing work..." << '\n';
  std::this_thread::sleep_for(5s);

  std::cout << "Producer: set value..." << '\n';
  promise.set_value(500);
}

//
// Entry function
//
int main() {
  std::cout << "--- std::future/std::promise ---" << '\n';

  std::promise<int> pro;
  std::future<int> fut(pro.get_future());

  std::thread t1(consumer_func, std::ref(fut));
  std::thread t2(producer_func, std::ref(pro));
  t1.join();
  t2.join();

  return 0;
}
