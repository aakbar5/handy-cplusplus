//
// Program
//  Two threads tries to update shared atomic value.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 03-atomic 03-atomic.cc
//
// Execution
//  ./03-atomic
//

#include <iostream>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;

//
// Data used by the example
//
struct Data {
  Data():value(0) {}
  std::uint64_t getValue() { return value.load(); }
  std::uint64_t setValue(const std::uint64_t &newValue) {
    std::uint64_t oldValue = value.load();

    // NOTE:
    // compare_exchange_strong can also be used however as per
    // https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange.
    // When a compare-and-exchange is in a loop, the weak version will
    // yield better performance on some platforms.
    while (value.compare_exchange_weak(oldValue, newValue))
    {}

    return oldValue;
  }
  std::atomic_uint64_t value;
};

//
// Function to be called for thread
//
void thread_producer(Data &data) {
  std::cout << "producer # " << std::this_thread::get_id() << " is up" << '\n';

  std::cout << "producer # " << std::this_thread::get_id() << " is doing work..." << '\n';
  std::cout << "producer # " << std::this_thread::get_id() << " initial value is " << data.value << '\n';

  // Get value
  std::uint64_t value = data.getValue();

  // Modify value
  for (int i=1; i < 1000; ++i) {
    ++value;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  // Update value
  data.setValue(value);

  std::cout << "producer # " << std::this_thread::get_id() << " after value is " << data.value << '\n';

  std::this_thread::sleep_for(2s);
  std::cout << "producer # " << std::this_thread::get_id() << " is done" << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- std::atomic_uint64_t with exchange ---" << '\n';

  Data data;
  std::cout << "main vanilla value is " << data.value << '\n';

  std::thread t2(thread_producer, std::ref(data));
  std::thread t1(thread_producer, std::ref(data));
  t1.join();
  t2.join();

  std::cout << "main modified value is " << data.value << '\n';

  return 0;
}
