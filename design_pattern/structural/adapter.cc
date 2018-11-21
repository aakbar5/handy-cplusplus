//
// Design pattern # adapter
// Adapter pattern works as a bridge between two incompatible interfaces.
//  This type of design pattern comes under structural pattern as this pattern 
// combines the capability of two independent interfaces.
//
// g++ -std=c++17 -Wall -Wextra -o adapter adapter.cc
//
#include <iostream>

struct File {
  virtual std::string get_contents() = 0;
};

struct Object {
  void show(File *file) {
    std::cout << "Can only understand xml: " << '\n';
    std::cout << file->get_contents() << '\n';
  }
};

struct XmlFile: File {
  std::string get_contents() override {
    return "xml schema based contents";
  }
};

struct YamlFile {
  std::string reader() {
    return "yaml based contents";
  }
};

struct YamlFileAdapter: File {
  
  std::string get_contents() override {
    auto cont = file_.reader();
    return "Transformation: Yaml to xml contents";
  }

  YamlFile file_;
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # adapter\n";

  {
    Object obj {};
    XmlFile *xml = new XmlFile {};
    obj.show (xml);
  }

  {
    Object obj {};

    // Can't do this as my object does not understand
    // Yaml so have to go through adapter
    // YamlFile *yaml = new YamlFile {};
    // obj.show (yaml);

    YamlFileAdapter *yaml = new YamlFileAdapter {};
    obj.show (yaml);
  }
  return 0;
}
