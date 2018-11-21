//
// Design pattern # template method
//
// g++ -std=c++17 -Wall -Wextra -o template_method template_method.cc
//
#include <iostream>

struct Template {
  virtual void encode(std::string data) = 0;
};

struct Csv: Template {
  void encode(std::string data) {
    std::cout << "Encoding format is: CSV --> " << data << '\n';
  }
};

struct Excel: Template {
  void encode(std::string data) {
    std::cout << "Encoding format is: EXCEL --> " << data << '\n';
  }
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # template method\n";

  std::string data = "data data";

  Csv csv;
  csv.encode(data);

  return 0;
}
