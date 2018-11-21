//
// Program
//  C++17 Filesystem: Evaluate a path.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 02-fs_test 02-fs_test.cc -lstdc++fs
//
// Execution
//  ./02-fs_test
//

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

//
// Entry function
//
int main() {
  fs::path file_path = fs::path(__FILE__);
  std::uintmax_t file_size = fs::file_size(file_path);

  std::cout << "Hello world -- std::filesystem" << '\n';
  std::cout << "Absolute path:        " << fs::absolute(file_path).string() << '\n';
  std::cout << "Relative path:        " << fs::relative(file_path).string() << '\n';
  std::cout << "Root name:            " << file_path.root_name().string() << '\n';
  std::cout << "Root directory:       " << file_path.root_directory().string() << '\n';
  std::cout << "Root path:            " << file_path.root_path().string() << '\n';
  std::cout << "Relative path:        " << file_path.relative_path().string() << '\n';
  std::cout << "Parent path:          " << file_path.parent_path().string() << '\n';
  std::cout << "File name with ext:   " << file_path.filename().string() << '\n';
  std::cout << "File name without ext:" << file_path.stem().string() << '\n';
  std::cout << "File extension:       " << file_path.extension().string() << '\n';
  std::cout << "Is exists:            " << std::boolalpha << fs::exists(file_path) << '\n';
  std::cout << "Is dir file:          " << std::boolalpha << fs::is_directory(file_path) << '\n';
  std::cout << "Is regular file:      " << std::boolalpha << fs::is_regular_file(file_path) << '\n';
  std::cout << "Is block file:        " << std::boolalpha << fs::is_block_file(file_path) << '\n';
  std::cout << "Is char file:         " << std::boolalpha << fs::is_character_file(file_path) << '\n';
  std::cout << "Is empty:             " << std::boolalpha << fs::is_empty(file_path) << '\n';
  std::cout << "Is FIFO:              " << std::boolalpha << fs::is_fifo(file_path) << '\n';
  std::cout << "Is other:             " << std::boolalpha << fs::is_other(file_path) << '\n';
  std::cout << "Is socket:            " << std::boolalpha << fs::is_socket(file_path) << '\n';
  std::cout << "Is symlink:           " << std::boolalpha << fs::is_symlink(file_path) << '\n';
  std::cout << "File size:            " << file_size << " bytes" << '\n';

  fs::perms prms = fs::status(file_path).permissions();
  std::cout << "File permission:      "
            << ((prms & fs::perms::owner_read)    != fs::perms::none ? "r" : "-")
            << ((prms & fs::perms::owner_write)   != fs::perms::none ? "w" : "-")
            << ((prms & fs::perms::owner_exec)    != fs::perms::none ? "x" : "-")
            << ((prms & fs::perms::group_read)    != fs::perms::none ? "r" : "-")
            << ((prms & fs::perms::group_write)   != fs::perms::none ? "w" : "-")
            << ((prms & fs::perms::group_exec)    != fs::perms::none ? "x" : "-")
            << ((prms & fs::perms::others_read)   != fs::perms::none ? "r" : "-")
            << ((prms & fs::perms::others_write)  != fs::perms::none ? "w" : "-")
            << ((prms & fs::perms::others_exec)   != fs::perms::none ? "x" : "-")
            << '\n';

  fs::file_time_type time = fs::last_write_time(file_path);
  auto t1 = std::chrono::system_clock::to_time_t(time);
  auto t2 = std::asctime(std::localtime(&t1));
  std::cout << "File time stamp:      " << t2 << '\n';

  return 0;
}
