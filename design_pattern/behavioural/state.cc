//
// Design pattern # state
//  Lets an object alter its behavior when its
//  internal state changes.
//
// g++ -std=c++17 -Wall -Wextra -o state state.cc
//
#include <iostream>

struct State {
  virtual void write(std::string text) = 0;
};

struct UpperCase: State {
  void write(std::string text) override {
    for (auto ch: text) {
      std::cout << static_cast<char>(std::toupper(ch));
    }
    std::cout << '\n';
  }
};

struct LowerCase: State {
  void write(std::string text) override {
    for (auto ch: text) {
      std::cout << static_cast<char>(std::tolower(ch));
    }
    std::cout << '\n';
  }
};

struct TextEditor {
  State *state;
  TextEditor(State *state) {
    this->state = state;
  }

  void write(std::string text) {
    this->state->write(text);
  }

  void set_state(State *new_state) {
    this->state = new_state;
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # state\n";

  TextEditor *editor = new TextEditor(new LowerCase());
  editor->write("Sample Text to Write");

  editor->set_state(new UpperCase());
  editor->write("More text");

  return 0;
}
