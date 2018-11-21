//
// Design pattern # mediator
//  Lets you to break the dependancy b/w different objects
//  so objects interact with mediator for communication instead
//  of direclty dealing with each other object they need to
/// interact.
//
// g++ -std=c++17 -Wall -Wextra -o mediator mediator.cc
//
#include <iostream>
#include <unordered_map>

struct UserI {
  virtual std::string get_id(void) = 0;
  virtual void send(std::string msg) = 0;
  virtual void receive(std::string msg) = 0;
};

struct Mediator {
  std::unordered_map<std::string, UserI*> users;

  void list() {
    for (const auto& n: users) {
      std::cout << ((UserI*)n.second)->get_id() << '\n';
    }
  }
  void add(UserI *user) {
    users[user->get_id()] = user;
  }
  void send(const std::string &id, const std::string &msg) {
    for (const auto& n: users) {
      UserI *ptr = n.second;
      if (ptr->get_id() != id)
        ptr->receive(msg);
    }
  }
};

struct User: UserI {
  std::string id;
  Mediator *mediator;

  User(Mediator *mediator, std::string id) {
    this->mediator = mediator;
    this->id = id;
  }
  std::string get_id(void) override {
    return this->id;
  }
  void send(std::string msg) override {
    mediator->send(get_id(), msg);
  }
  void receive(std::string msg) override {
    std::cout << get_id() << " has received # " << msg << '\n';
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # mediator\n";

  Mediator mediator;

  User u1(&mediator, "u1");
  User u2(&mediator, "u2");

  mediator.add(&u1);
  mediator.add(&u2);

  u1.send("hello world from u1");
  u2.send("hello world from u2");

  return 0;
}
