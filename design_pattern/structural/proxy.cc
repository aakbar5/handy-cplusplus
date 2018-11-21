//
// Design pattern # proxy
// Flyweight pattern is used to reduce the number of
// objects created.
//
// g++ -std=c++17 -Wall -Wextra -o proxy proxy.cc
//
#include <iostream>

struct Executer {
  virtual bool execute(const std::string &command) = 0;
};

struct User: Executer {
  bool execute(const std::string &command) override {
    std::cout << "Execute command # " << command << '\n';
    return true;
  }
};

// Proxy user
struct Root: Executer {
  std::string password;
  
  Root(const std::string &password) {
    this->password = password;
  }
  bool execute(const std::string &command) override {
    if (authenicate())
      std::cout << "Execute command # " << command << '\n';

    return false;
  }

  bool authenicate() {
    return this->password == "root";
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # proxy\n";

  bool ret;

  User user;
  ret = user.execute("show me the contents");
  if (!ret)
    std::cout << "Fail to execute command\n";

  Root root1("user");
  ret = root1.execute("move contents");
  if (!ret)
    std::cout << "Fail to execute command\n";

  Root root2("root");
  ret = root2.execute("move contents");
  if (!ret)
    std::cout << "Fail to execute command\n";

  return 0;
}
