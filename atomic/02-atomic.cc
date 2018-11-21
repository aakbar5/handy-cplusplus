//
// Program
//  std::atomic_flag is special version of std::atomic<bool> which is
//  guarented to be lock free. It does not support load or store operations.
//  APIs.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 02-atomic 02-atomic.cc
//
// Execution
//  ./02-atomic
//

#include <iostream>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;

//
// Data used by the example
//
class SpinLock {
  public:
  SpinLock(): is_ready(ATOMIC_FLAG_INIT) {}
  void lock() { while (is_ready.test_and_set(std::memory_order_acquire) ) {} }
  void release() { is_ready.clear(std::memory_order_release); }
  private:
  std::atomic_flag is_ready;
};

struct Data {
  Data():value(0), lock() {}
  std::uint32_t value;
  SpinLock lock;
};

//
// Function to be called for thread
//
void thread_producer(Data &data) {
  std::cout << "producer # " << std::this_thread::get_id() << " is up" << '\n';

  // lock the before entering into critical section
  data.lock.lock();

  std::cout << "producer # " << std::this_thread::get_id() << " is doing work..." << '\n';
  std::cout << "producer # " << std::this_thread::get_id() << " initial value is " << data.value << '\n';

  for (int i=1; i < 1000; ++i) {
    ++data.value;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  std::cout << "producer # " << std::this_thread::get_id() << " after value is " << data.value << '\n';

  // release the lock
  data.lock.release();

  std::this_thread::sleep_for(2s);
  std::cout << "producer # " << std::this_thread::get_id() << " is done" << '\n';
}

//
// Entry function
//
int main() {
  std::cout << "--- std::atomic_flag / Spinlock ---" << '\n';

  Data data;
  std::cout << "main vanilla value is " << data.value << '\n';

  std::thread t2(thread_producer, std::ref(data));
  std::thread t1(thread_producer, std::ref(data));
  t1.join();
  t2.join();

  std::cout << "main modified value is " << data.value << '\n';

  return 0;
}
