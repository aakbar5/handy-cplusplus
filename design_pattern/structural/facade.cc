//
// Design pattern # facade
// Facade provides a simplified interface of a complex system.
//
// g++ -std=c++17 -Wall -Wextra -o facade facade.cc
//
#include <iostream>
#include <vector>

struct Pixel {
  int8_t red;
  int8_t green;
  int8_t blue;
};

struct RawImageData {
  int32_t width;
  int32_t height;
  std::vector<Pixel> rgb;
};

struct Facade {
  bool endswith(const std::string& file, const std::string &ext) {
    auto pos = file.find(ext);
    return pos != std::string::npos;
  }
  bool decode(const char *file) {
    if (endswith(file, ".png")) {
      std::cout << "png library is loaded" << '\n';
      std::cout << "png is decoded" << '\n';
    }
    else if (endswith(file, ".jpg")) {
      std::cout << "jpg library is loaded" << '\n';
      std::cout << "jpg is decoded" << '\n';
    }
    else if (endswith(file, ".bmp")) {
      std::cout << "bmp decoder is loaded" << '\n';
      std::cout << "png is decoded" << '\n';
    }
    else if (endswith(file, ".ppm")) {
      std::cout << "ppm decoder is loaded" << '\n';
      std::cout << "ppm is decoded" << '\n';
    }
    else {
      return false;
    }

    data.height = 100;
    data.width = 100;
    std::cout << "RGB data is ready" << '\n';
    return true;
  }

  bool save(const std::string& file) {
    std::cout << "RGB data is saved # " << file << '\n';
  }

  RawImageData data;
};

//
// Entry function
//
int main() {
  std::cout << "Design pattern # Facade\n";

  Facade facade;
  bool ret = facade.decode ("test.jpg");
  if (ret)
    facade.save("raw_rgb.data");

  return 0;
}
