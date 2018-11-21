//
// Design pattern # observer
//
// g++ -std=c++17 -Wall -Wextra -o observer observer.cc
//
#include <iostream>
#include <vector>

struct Observer {
  virtual void on_notification(std::string message) = 0;
};

struct Seeker: Observer  {
  std::string name_;
  Seeker(std::string name): name_(name) {}
  void on_notification(std::string message) {
    std::cout << "Notification: " << name_ << " -> " << message << '\n';
  }
};

struct Event {
  std::vector<Seeker*> list;
  void add_observer(Seeker *seeker) {list.push_back(seeker);}
  void send_notification(std::string message) {
    for(auto entry: list)
    {
      entry->on_notification(message);
    }
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # observer\n";

  Seeker seekera("A");
  Seeker seekerb("B");

  Event event;
  event.add_observer(&seekera);
  event.add_observer(&seekerb);
  event.send_notification("Hello");

  return 0;
}
