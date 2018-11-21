//
// Program
//  std::shared_future allows multiple threads to await
//  upon std::future.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 63-thread 63-thread.cc
//
// Execution
//  ./63-thread
//

#include <iostream>
#include <thread>
#include <future>

using namespace std::chrono_literals;

//
// Function to be called for thread
//
void consumer_func(std::shared_future<int> &sfuture) {
  auto id = std::this_thread::get_id();

  std::cout << "Consumer: " << id << " is up..." << '\n';

  // Wait for value to set on promise
  std::cout << "Consumer: " << id << " is waiting for promise..." << '\n';
  sfuture.wait();

  std::cout << "Consumer: " << id << " Got value # " << sfuture.get() << '\n';
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
  std::shared_future<int> sfut(pro.get_future());

  std::thread t1(consumer_func, std::ref(sfut));
  std::thread t2(consumer_func, std::ref(sfut));
  std::thread t3(consumer_func, std::ref(sfut));
  std::thread t4(consumer_func, std::ref(sfut));

  std::thread t5(producer_func, std::ref(pro));
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join(); // producer

  return 0;
}
