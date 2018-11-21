//
// Design pattern # chain of responsiblity
// Lets you pass requests along a chain of handlers
//
// g++ -std=c++17 -Wall -Wextra -o chain_of_resp chain_of_resp.cc
//
#include <iostream>
#include <vector>

// widget -> window -> panel -> button
struct Widget {
  virtual void process(const std::string &msg) = 0;
};

struct Window: Widget {
  std::vector<Widget*> children;
  void add_child(Widget *wid) {
    children.push_back(wid);
  }
  void process(const std::string &msg) override {
    for (Widget *child: children) {
      child->process(msg);
    }
  }
  void send_event(const std::string &msg) {
    process(msg);
  }
};

struct Panel: Widget {
  std::vector<Widget*> children;
  void add_child(Widget *wid) {
    children.push_back(wid);
  }
  void process(const std::string &msg) override {
    for (Widget *child: children) {
      child->process(msg);
    }
  }
};

struct Button: Panel {
  void process(const std::string &msg) override {
    std::cout << "Button: Process event # " << msg << '\n';
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # chain of responsiblity\n";

  // widget -> window -> panel -> button
  Window window;
  Panel panel;
  Button button;

  panel.add_child(&button);
  window.add_child(&panel);
  window.send_event("Hello");

  return 0;
}
