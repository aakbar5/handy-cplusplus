//
// Program
//  C++17 Filesystem: Shows current and temporary directories and evaluates disk sizes.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 01-fs_test 01-fs_test.cc -lstdc++fs
//
// Execution
//  ./01-fs_test
//

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

constexpr uintmax_t bytes_kilo = 1LL << 10;
constexpr uintmax_t bytes_mega = 1LL << 20;
constexpr uintmax_t bytes_giga = 1LL << 30;
constexpr uintmax_t bytes_tera = 1LL << 40;

// Convert bytes into std::string using storage units
std::string bytestostring(uintmax_t bytes) {
  long double bytes_f = bytes * 1.0f;

  if (bytes > bytes_tera) {
    return std::to_string( bytes_f / bytes_tera) + std::string(" TB");
  }
  else if (bytes > bytes_giga) {
    return std::to_string(bytes_f / bytes_giga) + std::string(" GB");
  }
  else if (bytes > bytes_mega) {
    return std::to_string(bytes_f / bytes_mega) + std::string(" MB");
  }
  else if (bytes > bytes_kilo) {
    return std::to_string(bytes_f / bytes_kilo) + std::string(" KB");
  }

  return std::to_string(bytes_f) + std::string(" Bytes");
}

//
// Entry function
//
int main() {
  fs::path curr_path = fs::current_path();
  fs::path tmp_path = fs::temp_directory_path();

  std::cout << "Hello world -- std::filesystem" << '\n';
  std::cout << " - Current working directory: " << curr_path.string() << '\n';
  std::cout << " - Temporary directory:       " << tmp_path.string() << '\n';

  fs::space_info info = fs::space(curr_path);
  std::cout << '\n';
  std::cout << " - Directory info:     " << curr_path.string() << '\n';
  std::cout << "   - Total size:       " << bytestostring(info.capacity) << '\n';
  std::cout << "   - Free space size:  " << bytestostring(info.free) << '\n';
  std::cout << "   - Available size:   " << bytestostring(info.available) << '\n';

  return 0;
}
