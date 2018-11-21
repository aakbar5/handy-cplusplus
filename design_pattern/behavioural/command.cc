//
// Design pattern # command
//  Lets you to encapsulate action into object.
//
// g++ -std=c++17 -Wall -Wextra -o command command.cc
//
#include <iostream>

struct Command {
  virtual void execute() = 0;
};

struct SaveCommand: Command {
  void execute() override {
    std::cout << "Execute save command ...\n";
  }
};

struct MenuItem {
  void execute(Command *cmd) {
    cmd->execute();
  }
};

struct Button {
  void execute(Command *cmd) {
    cmd->execute();
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # command\n";

  SaveCommand cmd_save;

  MenuItem menu_save;
  menu_save.execute(&cmd_save);

  Button btn_save;
  btn_save.execute(&cmd_save);

  return 0;
}
