//
// Program
//  A class with simulates the functionality timer. On expiration
//  of time, timer can execute a callback function too.
//  Timer can configured in different ways:
//  - It can be asked to run for specific number of times.
//  - or it can be asked to run for infinite number of times.
//      - Use stop function to stop this timer.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 04-chrono 04-chrono.cc
//
// Execution
//  ./04-chrono
//

#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>

class Timer {
private:
  intmax_t time_out_ms_;
  intmax_t shot_count_;
  std::function<void(void)> callback_;
  std::atomic<bool> is_running_;
  std::thread thread_;

  void thread_callback() {
    intmax_t times = 0;

    while (is_running_ == true && (shot_count_ == 0 || times < shot_count_)) {
      if (callback_ != nullptr) {
        callback_();
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(time_out_ms_));
      ++times;
    }

    is_running_ = false;
  }

public:
  Timer() = delete;
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer &&) = delete;

  explicit Timer(intmax_t time_out_ms, intmax_t shot_count=1,
                 std::function<void(void)> callback=nullptr):
    time_out_ms_(time_out_ms),
    shot_count_(shot_count),
    callback_(callback),
    is_running_(false),
    thread_({}) {
  }

  void start() {
    is_running_ = true;
    thread_ = std::thread(&Timer::thread_callback, this);
  }

  // It is blocking call, as it wait
  // until underlying thread is not finished
  void stop() {
    try {
      // Ask thread to stop execution
      is_running_ = false;

      // Do busy wait until thread is not being marked as dead
      if (thread_.joinable()) {
        thread_.join();
      }
    }
    catch(...) {}
  }

  bool is_active() const {
    return this->is_running_.load();
  }

  intmax_t get_time_out(void) const {
    return this->time_out_ms_;
  }

  intmax_t get_shot_count(void) const {
    return this->shot_count_;
  }

  ~Timer() {
    stop();
  }
};

// Timer callback
static uint64_t timer_callback_counter = 0;
void callback() {
  std::cout << "Timer callback is called: " << ++timer_callback_counter << '\n';
}

//
// Entry function
//
int main() {
  {
    std::thread t([] {
      // Reset callback counter
      timer_callback_counter = 0;

      // Create timer for 5sec for 150
      Timer myTimer(5, 25, callback);

      std::cout << "Start timer..." << '\n';
      myTimer.start();

      while (myTimer.is_active())
      {
      }

      std::cout << "Timer is stopped" << '\n';
      myTimer.stop();
    });
    t.join();
  }

  {
    std::thread t([] {
      // Reset callback counter
      timer_callback_counter = 0;

      // Keep timer running
      Timer myTimer(6, 0, callback);

      std::cout << "Start timer..." << '\n';
      myTimer.start();

      while (myTimer.is_active())
      {
        // After a while ask thread to shutdown itself
        if (timer_callback_counter >= 500) {
          std::cout << "Timer is stopped" << '\n';
          myTimer.stop();
        }
      }
    });
    t.join();
  }

  return 0;
}
