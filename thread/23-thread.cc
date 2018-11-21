//
// Program
//  This program utilizes std::shared_mutex where multiple
//  threads are using reader lock whereas one thread is using
//  writer lock.
//
//  The output of the program:
// 		thread_reader_func is assigned to thread id # 140587796313856
// 		thread_writer_func is assigned to thread id # 140587779528448
// 		thread_reader_func is assigned to thread id # 140587787921152
// 		Thread id # 140587779528448 wl   => write-lock
// 		Thread id # 140587779528448 wr   => write-release
// 		Thread id # 140587796313856 rl   => Read-lock
// 		Thread id # 140587787921152 rl   => Read-lock
// 		Thread id # 140587796313856 rr   => Read-release
// 		Thread id # 140587787921152 rr   => Read-release
// 		Thread id # 140587779528448 wl   => write-lock
// 		Thread id # 140587779528448 wr   => write-release
// 		Thread id # 140587796313856 rl   => Read-lock
// 		Thread id # 140587787921152 rl   => Read-lock
// 		Thread id # 140587796313856 rr   => Read-release
// 		Thread id # 140587796313856 rl   => Read-lock
// 		Thread id # 140587787921152 rr   => Read-release
// 		Thread id # 140587787921152 rl   => Read-lock
// 		Thread id # 140587787921152 rr   => Read-release
// 		Thread id # 140587796313856 rr   => Read-release
// 		Thread id # 140587779528448 wl   => write-lock
// 		Thread id # 140587779528448 wr 	 => write-release
// 		Thread id # 140587787921152 rl   => Read-lock
// 		Thread id # 140587796313856 rl   => write-lock
// 		Thread id # 140587796313856 rr   => Read-release
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 23-thread 23-thread.cc
//
// Execution
//  ./23-thread
//

#include <iostream>
#include <thread>
#include <shared_mutex>

using namespace std::chrono_literals;

//
// Function to be called for thread
//
static void thread_reader_func(std::shared_mutex& smutex) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  std::this_thread::sleep_for(3s);

  while (true) {
    smutex.lock_shared();
    std::cout << "Thread id # " << id << " rl" << '\n';

    std::this_thread::sleep_for(4s);

    smutex.unlock();
    std::cout << "Thread id # " << id << " rr" << '\n';
  }
}

//
// Function to be called for thread
//
static void thread_writer_func(std::shared_mutex& smutex) {
  auto id = std::this_thread::get_id();
  std::cout << __func__ << " is assigned to thread id # " << id << '\n';

  std::this_thread::sleep_for(1s);

  while (true) {
    smutex.lock();
    std::cout << "Thread id # " << id << " wl" << '\n';

    std::this_thread::sleep_for(2s);

    smutex.unlock();
    std::cout << "Thread id # " << id << " wr" << '\n';
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- Shared mutex ---" << '\n';

  std::shared_mutex smutex;

  std::thread t1(thread_reader_func, std::ref(smutex));
  std::thread t2(thread_reader_func, std::ref(smutex));
  std::thread t3(thread_writer_func, std::ref(smutex));

  t1.join();
  t2.join();
  t3.join();

  return 0;
}
