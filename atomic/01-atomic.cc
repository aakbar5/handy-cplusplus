//
// Program
//  In this program, producer and consumer communicates with other
//  via atomic_bool variable to inform that data is ready. One can
//  use mutex instead of atomic bool. However mutex operation are
//  relative expensive as compared to atomic.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 01-atomic 01-atomic.cc
//
// Execution
//  ./01-atomic
//

#include <iostream>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;

//
// Data used by the example
//
struct Data {
    Data():value(0), is_ready(false) {}
    std::uint32_t value;
    std::atomic<bool> is_ready;
};

//
// Function to be called for thread
//
void thread_consumer(Data &data) {
  std::cout << "consumer is up" << '\n';
  std::cout << "consumer is waiting for flag..." << '\n';

  // Wait until flag is not set by the producer
  // TODO: C++20 got wait function which will be handy here

  while (!data.is_ready.load()) {
    std::this_thread::sleep_for(10ms);
  }

  std::cout << "consumer data ready flag is set" << '\n';
  std::cout << "consumer initial value is " << data.value << '\n';
}

//
// Function to be called for thread
//
void thread_producer(Data &data) {
  std::cout << "producer is up" << '\n';

  std::cout << "producer is doing work..." << '\n';
  std::cout << "producer initial value is " << data.value << '\n';

  for (int i=1; i < 1000; ++i) {
    ++data.value;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  std::cout << "producer after value is " << data.value << '\n';

  // Inform consumer that data is ready
  std::cout << "producer data is ready for others" << '\n';
  data.is_ready.store(true);

  std::this_thread::sleep_for(2s);
  std::cout << "producer is done" << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- std::atomic<bool> ---" << '\n';

  Data data;
  std::thread t1(thread_consumer, std::ref(data));
  std::thread t2(thread_producer, std::ref(data));
  t1.join();
  t2.join();

  return 0;
}
