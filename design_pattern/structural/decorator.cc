//
// Design pattern # decorator
// Decorator allows you to attach new behaviour.
//
// g++ -std=c++17 -Wall -Wextra -o decorator decorator.cc
//
#include <iostream>

struct Notifier {
  virtual void send() = 0;
};

struct EmailNotifier: Notifier {
  void send() override {
    std::cout << "Notifier -> email" << '\n';
  }
};

// Decorator
struct DecoratorNotifier: Notifier {
  Notifier *notifier_;
  DecoratorNotifier(Notifier *notifier):  notifier_(notifier) {}
  void send() override {
    notifier_->send();
    std::cout << "Notifier -> Sms" << '\n';
  }
};

struct Work {
  void do_job() {
    std::cout << "Work --> job" << '\n';
  }
  void send_notification(Notifier* notifier) {
    notifier->send();
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # decorator\n";

  Notifier *notifier = new DecoratorNotifier(new EmailNotifier());

  Work work;
  work.do_job();
  work.send_notification(notifier);

  return 0;
}
