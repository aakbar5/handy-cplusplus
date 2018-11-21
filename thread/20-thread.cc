//
// Program
//  This program simply creates a mutex which is shared
//  among two threads.
//  This mutex guarantees that 2nd thread will not get hold off
//  the shared data until previous thread is not finished with its execution.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 20-thread 20-thread.cc
//
// Execution
//  ./20-thread
//

#include <iostream>
#include <thread>
#include <mutex>

//
// Data used by the example
//
struct Data {
  Data():value(0), mutex() {}
  std::uint32_t value;
  std::mutex mutex;
};

//
// Function to be called for thread
//
void thread_callback_1(Data &data) {
  data.mutex.lock();

  std::cout << __func__ << " is assigned to thread id # " << std::this_thread::get_id() << '\n';

  std::cout << "\tBefore: value = " << data.value << '\n';

  for (int i=1; i < 1000; ++i)
    ++data.value;

  std::cout << "\tAfter: value = " << data.value << '\n';

  data.mutex.unlock();
}

//
// Function to be called for thread
//
void thread_callback_2(Data &data) {
  data.mutex.lock(); // If mutex is already owned, it will suspend here
                      // You can you try_lock to see whether it is already locked or not

  std::cout << __func__ << " is assigned to thread id # " << std::this_thread::get_id() << '\n';

  std::cout << "\tBefore: value = " << data.value << '\n';

  for (int i=1; i < 1000; ++i)
    ++data.value;

  std::cout << "\tAfter: value = " << data.value << '\n';

  data.mutex.unlock();
}

//
// Entry function
//
int main() {
  std::cout << "--- Simple mutex ---" << '\n';

  Data data;

  std::cout << "Main -- Before: value = " << data.value << '\n';

  std::thread t1(thread_callback_1, std::ref(data));
  std::thread t2(thread_callback_2, std::ref(data));
  t1.join();
  t2.join();

  std::cout << "Main -- After: value = " << data.value << '\n';

  return 0;
}
