//
// Program
//  This program simply creates a thread and prints its ID.
//      - Create a thread
//      - Create a thread which accepts a parameter
//      - Create a thread whose callback is implemented by lambda
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 01-thread 01-thread.cc
//
// Execution
//  ./01-thread
//

#include <iostream>
#include <thread>
#include <system_error>

//
// Function to be called for thread
//
static void thread_callback_plain(void) {
  std::cout << __func__ << '\n'
            << "\tThread Id: " << std::this_thread::get_id() << '\n';
}

//
// Function to be called for thread
//
static void thread_callback_param(int param1) {
  std::cout << __func__ << '\n'
            << "\tThread Id: " << std::this_thread::get_id() << '\n'
            << "\tparam # 1: " << param1 << '\n';
}

//
// Entry function
//
int main() {
  // Create & start thread
  std::cout << "--- Thread: create simple thread ---" << '\n';
  {
    std::thread t(thread_callback_plain);
    t.join(); // Wait for the thread until it completes its execution
  }

  // Create & start thread and pass a parameter
  std::cout << "--- Thread: create simple thread and passed parameter by value ---" << '\n';
  {
    std::thread t(thread_callback_param, 100);
    t.join(); // Wait for the thread until it completes its execution
  }

  // Create & start thread where thread execution is implemented in lambda
  std::cout << "--- Thread: create a thread whose execution function is in lambda ---" << '\n';
  {
    std::thread t1([] {
      std::cout << __func__ << '\n'
          << "\tThread Id: " << std::this_thread::get_id() << '\n';
    });
    t1.join(); // Wait for the thread until it completes its execution
  }

  // Create & start thread where thread execution is implemented in function objects
  std::cout << "--- Thread: create a thread whose execution function is function object ---" << '\n';
  {
    struct thread_impl {
      void operator ()() {
        std::cout << __func__ << '\n'
            << "\tThread Id: " << std::this_thread::get_id() << '\n';
      }
    };

    std::thread t1((thread_impl()));
    t1.join(); // Wait for the thread until it completes its execution
  }

  // Create a thread without any callback
  std::cout << "--- Thread: create a thread without any callback (Expected: exception) ---" << '\n';
  {
    try {
      std::thread t2; // No callback is registered so invalid thread
      t2.join(); // Attempt to join will generate exception

    } catch(const std::system_error& err) {
      std::cout << "Error is caught=" << err.what() << "(" << err.code() << ")" << '\n';
    }
  }

  // No thread is running at this moment
  return 0;
}
