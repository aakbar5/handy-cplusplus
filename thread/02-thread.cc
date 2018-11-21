//
// Program
//  This program simply creates a thread and calls different
//  management functions.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 02-thread 02-thread.cc
//
// Execution
//  ./02-thread
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <ctime>

using namespace std::chrono;

//
// Function to be called for thread
//
static void thread_func(void) {
  std::cout << __func__ << " is used by thread Id: " << std::this_thread::get_id() << '\n';

  // ---------------------------------------
  std::cout << '\n' << "--- sleep_for ---" << '\n';
  {
    auto time_cur = system_clock::to_time_t(system_clock::now());
    auto time_str = std::put_time(std::localtime(&time_cur), "%H:%M:%S");

    std::cout << "Going to sleep for 2s at " << time_str << '\n';
    std::this_thread::sleep_for(2s);

    time_cur = system_clock::to_time_t(system_clock::now());
    time_str = std::put_time(std::localtime(&time_cur), "%H:%M:%S");
    std::cout << "Back to live at " << time_str << '\n';
  }

  // ---------------------------------------
  std::cout << '\n' << "--- sleep_until ---" << '\n';
  {
    auto time_cur = system_clock::to_time_t(system_clock::now());
    auto time_str = std::put_time(std::localtime(&time_cur), "%H:%M:%S");

    std::cout << "Going to sleep until for 3s at " << time_str << '\n';
    std::this_thread::sleep_until(system_clock::now() + 3s);

    time_cur = system_clock::to_time_t(system_clock::now());
    time_str = std::put_time(std::localtime(&time_cur), "%H:%M:%S");
    std::cout << "Back to live at " << time_str << '\n';
  }

  // ---------------------------------------
  std::cout << '\n' << "--- yeild ---" << '\n';
  {
    auto time_cur = system_clock::to_time_t(system_clock::now());
    auto time_str = std::put_time(std::localtime(&time_cur), "%H:%M:%S");

    std::cout << "Going to yield at " << time_str << '\n';
    std::this_thread::yield();

    time_cur = system_clock::to_time_t(system_clock::now());
    time_str = std::put_time(std::localtime(&time_cur), "%H:%M:%S");
    std::cout << "Back to live at " << time_str << '\n';
  }
}

//
// Entry function
//
int main() {
  // Create & start thread
  std::cout << "--- Thread: with managing functions ---" << '\n';
  {
    std::thread t(thread_func);
    t.join(); // Wait for the thread until it completes its execution
  }

  // No thread is running at this moment
  std::cout << "Good bye!" << '\n';

  return 0;
}
