//
// Program
//  C++17 Filesystem: Directory iterator.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 03-fs_test 03-fs_test.cc -lstdc++fs
//
// Execution
//  ./03-fs_test
//

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Iterate directory
void list_dir(fs::path dir_path, fs::directory_options opts, int level) {
  std::string prepend = std::string(level * 2, ' ');

  for(auto& p: fs::directory_iterator(dir_path, opts)) {
    auto path = p.path();
    if (fs::is_directory(path)) {
      std::cout << prepend << "+ " << path.filename().string() << '\n';
      list_dir(path, opts, ++level);
      level--;
    }
    else if (fs::is_regular_file(path)) {
      std::cout << prepend <<"- " << path.filename().string() << '\n';
    }
  }
}

//
// Entry function
//
int main() {
  fs::path tmp_path = fs::temp_directory_path();

  std::cout << "Hello world -- std::filesystem" << '\n';
  std::cout << " - Temporary directory:       " << tmp_path.string() << '\n';

  fs::directory_options opts = /* fs::directory_options::follow_directory_symlink | */
                                fs::directory_options::skip_permission_denied;

  // Iterate directory recursively
  list_dir(tmp_path, opts, 1);

  return 0;
}
