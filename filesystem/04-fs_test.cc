//
// Program
//  C++17 Filesystem: Directory watcher.
//  - It looks for file added/removed in sub folder as well.
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -pthread -o 04-fs_test 04-fs_test.cc -lstdc++fs
//
// Execution
//  ./04-fs_test
//

#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <functional>

namespace fs = std::filesystem;

// File statuses
enum class File_Status: int {
  Is_Updated = 1 << 1,        // File has been modified
  Is_Removed = 1 << 2,        // File has been removed
  Is_Added = 1 << 3,          // File has been added
};

//
// This function monitors a given folder. It accepts following parameter
//  delay_in_seconds: Specify the time interval to used to watch a folder
//  folder_to_watch: Path of the folder
//  callback: Function to be called carrying std::unordered_map<File path, File status>.
//
void start_folder_watcher_thread(int delay_in_seconds,
                                 std::string folder_to_watch,
                                 std::function<void(std::unordered_map<std::string, File_Status>)> callback)
{
  fs::directory_options opts = /* fs::directory_options::follow_directory_symlink | */
                                fs::directory_options::skip_permission_denied;

  fs::path watch_path = fs::path(folder_to_watch);
  if (!fs::exists(watch_path)) {
    std::cout << "Error: " << folder_to_watch << " does not exists" << '\n';
    return;
  }

  if (!fs::is_directory(watch_path)) {
    std::cout << "Error: " << folder_to_watch << " is not a folder" << '\n';
    return;
  }

  std::unordered_map<std::string, fs::file_time_type> map_startup;
  for (auto& p: fs::recursive_directory_iterator(watch_path, opts)) {
    if (fs::is_regular_file(p.path())) {
      map_startup[p.path().string()] = fs::last_write_time(p.path());
    }
  }

  std::cout << "Initial files: " << '\n';
  for (const auto& p: map_startup) {
    auto ts_in_time = std::chrono::system_clock::to_time_t(p.second);
    auto ts_in_text = std::asctime(std::localtime(&ts_in_time));

    std::cout << " > " << p.first << " " << ts_in_text << '\n';
  }

  while (1) {
    std::vector<std::string> list_scan;
    std::unordered_map<std::string, File_Status> map_update;

    std::cout << " ---- Rescan folder --- " << '\n';

      // Get new files list
    for (auto& p: fs::recursive_directory_iterator(watch_path, opts)) {
      if (fs::is_regular_file(p)) {
        list_scan.push_back(p.path().string());
      }
    }

    // Let's see what we have lost
    {
      for (auto it = std::begin(map_startup); it != std::end(map_startup); ) {
        std::string path_s = (*it).first;

        auto it_find = std::find(std::begin(list_scan), std::end(list_scan), path_s);
        if (it_find != std::end(list_scan)) {
          // An old item is found

          // Let's verify its timestamp
          auto time = fs::last_write_time(path_s);
          if (time != (*it).second) {
            // Update our and user maps
            map_update[path_s] = File_Status::Is_Updated;
            map_startup[path_s] = time;
          }

          // Also remove this element of the list_scan too.
          // It will save us for encountering this element again
          // while we are looking for newly created files.
          list_scan.erase(it_find);

          // Move to next item
          ++it;
        }
        else {
          // An old item is not found

          // Update our and user maps
          map_update[path_s] = File_Status::Is_Removed;
          it = map_startup.erase(it);
        }
      }
    }

    // Let's see what we have found
    {
      for (auto it = std::begin(list_scan); it != std::end(list_scan); ++it) {
        std::string path_s = *it;

        // Just for debugging: Let's cross check
        auto search = map_startup.find(path_s);
        if (search != map_startup.end()) {
          // Logically it should be captured in the above block
          std::cout << "*** We should not see this message. ****" << path_s << '\n';
        }
        else {
          // New element is found

          // Update our and user maps
          map_update[path_s] = File_Status::Is_Added;
          map_startup[path_s] = fs::last_write_time(path_s);
        }
      }
    }

    // Send back info to the user
    if (callback && map_update.size() > 0)
      callback(map_update);

    // Reset our internal state
    map_update.clear();
    list_scan.clear();

    // Sleep
    std::this_thread::sleep_for(std::chrono::seconds(delay_in_seconds));
  }
}

//
// Entry function
//
int main() {
  std::cout << "Hello world -- std::filesystem" << '\n';

  std::thread t(start_folder_watcher_thread,
    2,
    "/tmp",
    [](std::unordered_map<std::string, File_Status> files) {
      for (auto& p: files) {
        std::string prepend("?");

        if (p.second == File_Status::Is_Updated)
          prepend = std::string("#");
        else if (p.second == File_Status::Is_Removed)
          prepend = std::string("-");
        else if (p.second == File_Status::Is_Added)
          prepend = std::string("+");

        std::cout << prepend << " " << p.first << '\n';
      }
    }
  );
  t.join(); // Wait for the thread until it completes its execution

  return 0;
}
