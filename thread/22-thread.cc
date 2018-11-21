//
// Program
//  Mutex management (std::lock_guard) same as 20-thread however it
//  uses std::lock_guard which allows to lock mutex only for the scoped.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 22-thread 22-thread.cc
//
// Execution
//  ./22-thread
//

#include <iostream>
#include <thread>
#include <mutex>

//
// Global data shared b/w threads
//
static unsigned int g_data = 0;
static std::mutex g_mutex; // Mutex is created

//
// Function to be called for thread
//
void thread_callback_1(void) {
  std::lock_guard<std::mutex> lock(g_mutex);
  // g_mutex.lock();

  std::cout << __func__ << '\n'
            << "\tThread Id: " << std::this_thread::get_id() << '\n';

  std::cout << "\tBefore: global_data = " << g_data << '\n';

  for (int i=1; i < 1000; ++i)
    ++g_data;

  std::cout << "\tAfter: global_data = " << g_data << '\n';

  // g_mutex.unlock();
  // No need to unlock std::lock_guard will take care of it
}

//
// Function to be called for thread
//
void thread_callback_2(void) {
  std::lock_guard<std::mutex> lock(g_mutex);
  // g_mutex.lock(); // If mutex is already owned, it will suspend here
                      // You can you try_lock to see whether it is already locked or not

  std::cout << __func__ << '\n'
            << "\tThread Id: " << std::this_thread::get_id() << '\n';

  std::cout << "\tBefore: global_data = " << g_data << '\n';

  for (int i=1; i < 1000; ++i)
    ++g_data;

  std::cout << "\tAfter: global_data = " << g_data << '\n';

  // g_mutex.unlock();
  // No need to unlock std::lock_guard will take care of it
}

//
// Entry function
//
int main() {
  std::cout << "--- Lock guard ---" << '\n';
  std::cout << "Main -- Before: global_data = " << g_data << '\n';

  std::thread t1(thread_callback_1);
  std::thread t2(thread_callback_2);

  t1.join();
  t2.join();

  std::cout << "Main -- After: global_data = " << g_data << '\n';

  return 0;
}
