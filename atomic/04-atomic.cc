//
// Program
//  Two threads tries to update shared POD.
//
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 04-atomic 04-atomic.cc
//
// Execution
//  ./04-atomic
//

#include <iostream>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;

//
// Data used by the example
//
struct Data {
  Data(std::uint64_t val = 0): value(val) {}
  std::uint64_t value;
};

//
// Function to be called for thread
//
void thread_producer(std::atomic<Data> &atomicData) {
  std::cout << "producer # " << std::this_thread::get_id() << " is up" << '\n';
  std::cout << "producer # " << std::this_thread::get_id() << " is doing work..." << '\n';

  static uint64_t increment = 2;

  // Prepare new value
  Data newValue {increment ++};

  // Modify value
  for (int i=1; i < 1000; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  // Get old value
  Data oldValue = atomicData.load();

  // Update value
  while (atomicData.compare_exchange_weak(oldValue, newValue))
  {}

  std::cout << "producer # " << std::this_thread::get_id() << " after value is " << atomicData.load().value << '\n';
  std::this_thread::sleep_for(2s);
  std::cout << "producer # " << std::this_thread::get_id() << " is done" << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- std::atomic with POD ---" << '\n';

  std::atomic<Data> atomicData(10);

  std::cout << "is POD: " << std::boolalpha << std::is_pod<Data>::value << '\n';
  std::cout << "Start value: " << atomicData.load().value << '\n';

  std::thread t1(thread_producer, std::ref(atomicData));
  std::thread t2(thread_producer, std::ref(atomicData));

  t1.join();
  t2.join();

  std::cout << "Last value: " << atomicData.load().value << '\n';

  return 0;
}
