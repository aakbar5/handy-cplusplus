//
// Program
//  This program creates thread(s) and manipulate their CPU affinity.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 03-thread 03-thread.cc
//
// Execution
//  ./03-thread
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <vector>
#include <sched.h>

using namespace std::chrono;

//
// Handy function to get CPU id where a specific
// process id is running.
//
int get_cpu_id(pthread_t p_id, unsigned int cpu_count) {
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);

  // Get cpu affinity
  // sched_getaffinity can also be used
  int ret = pthread_getaffinity_np(p_id, sizeof(cpu_set_t), &cpu_set);
  if (ret != 0) {
    std::cout << "Error: pthread_getaffinity_np error code # " << errno << '\n';
    return -1;
  }

  // Find out which cpu id is set
  for (auto c = 0U; c < cpu_count; ++c) {
    if (CPU_ISSET(c, &cpu_set)) {
      return c;
    }
  }

  return -1;
}

//
// Handy function to set CPU id for a specific process.
//
void set_cpu_id(pthread_t p_id, unsigned int cpu_id) {
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  CPU_SET(cpu_id, &cpu_set);

  // Set CPU affinity
  // sched_setaffinity can also be used
  int ret = pthread_setaffinity_np(p_id, sizeof(cpu_set_t), &cpu_set);
  if (ret != 0) {
    std::cout << "Error: pthread_setaffinity_np error code # " << errno << '\n';
  }
}

//
// Entry function
//
int main() {
  // Create & start thread
  std::cout << "--- Thread and manipulate affinity ---" << '\n';

  unsigned int cpus = std::thread::hardware_concurrency();
  std::cout << "Number of CPUs: " << cpus << '\n';
  std::vector<std::thread> threads(cpus);

  std::mutex mutex {};
  for (auto idx = 0U; idx < cpus; ++idx) {
    threads[idx] = std::thread([idx, &mutex, &cpus] {

      // This mutex makes sure that we are not being suspended in the mid
      // of the work
      std::scoped_lock lock(mutex);

      // Set CPU, without this call
      // underlying os can use any CPU
      auto p_id = pthread_self();
      set_cpu_id(p_id, idx + 1);

      std::cout << "Thread # " << std::setw(2) << idx << ": \n"
                << " - Thread Id (cxx):    " << std::this_thread::get_id() << "\t"
                << " - Thread Id (native): " << p_id << '\n'
                << " - CPU Id: " << get_cpu_id(p_id, cpus) << '\n';

      // Let's do some work
      std::this_thread::sleep_for(2s);
    });
  }

  for (auto& t: threads) {
    t.join();
  }

  // No thread is running at this moment
  std::cout << "Good bye!" << '\n';

  return 0;
}
