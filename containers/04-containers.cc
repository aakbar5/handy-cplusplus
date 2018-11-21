//
// Program
//  Containers: std::map usage
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 04-containers 04-containers.cc
//
// Execution
//  ./04-containers
//

#include <iostream>
#include <map>

// Print map
template <typename UserMap>
static void print_map(const UserMap& m) {
  for (const auto& item: m) {
    std::cout << item.first << " : " << item.second << '\n';
  }
}

//
// Entry function
//
int main() {
  std::cout << "--- std::map ---" << '\n';

  // Simple std::map declaration
  {
    std::map<int, std::string> m;

    m.insert({1, "entry1"});
    m.insert({2, "entry2"});
    m.insert(std::make_pair(3, "entry3"));

    std::cout << "Size: " << m.size() << '\n'; // 3 items are there
    std::cout << "Is empty: " << std::boolalpha << m.empty() << '\n'; // Not empty
    std::cout << "Max size: " << m.max_size() << '\n';
    std::cout << "Key # 3 is having count: " << m.count(3) << '\n'; // 1 entry of a specific key

    std::cout << "Show items of the map" << '\n';
    print_map(m);

    // It will fail as this key already exists
    auto ret = m.insert(std::make_pair(3, "entry3_2"));
    if (ret.second == false)
        std::cout << "Fail to insert new value with old key" << '\n';
    else
        std::cout << "New value with old key is inserted" << '\n';

    m[3] = "entry3_2"; // Old value will be replaced
    print_map(m);

    m[4] = "entry4"; // new key will be created
    print_map(m);
  }

  // search & delete operations
  {
    std::map<int, std::string> m;

    m.insert(std::make_pair(1, "entry1"));
    m.insert(std::make_pair(2, "entry2"));
    m.insert(std::make_pair(3, "entry3"));
    m.insert(std::make_pair(4, "entry4"));
    m.insert(std::make_pair(5, "entry5"));
    m.insert(std::make_pair(6, "entry6"));
    m.insert(std::make_pair(7, "entry7"));
    m.insert(std::make_pair(8, "entry8"));
    m.insert(std::make_pair(9, "entry9"));

    std::cout << "Size: " << m.size() << '\n';

    // search map with a key (key exists)
    std::cout << "Search by key" << '\n';
    {
      int key_to_find = 5;
      auto it = m.find(key_to_find);
      if (it != m.end()) {
        std::cout << "  Found:: " << "key # " << key_to_find << " : " << it->second << '\n';
      }
      else {
        std::cout << "  Not found:: " << "key # " << key_to_find << '\n';
      }
    }

    // search map with a key (key does not exists)
    std::cout << "Search by key" << '\n';
    {
      int key_to_find = 15;
      auto it = m.find(key_to_find);
      if (it != m.end()) {
        std::cout << "  Found:: " << "key # " << key_to_find << " : " << it->second << '\n';
      }
      else {
        std::cout << "  Not found:: " << "key # " << key_to_find << '\n';
      }
    }

    // search map with a value
    std::cout << "Search by value" << '\n';
    {
      std::string value_to_find = "entry8";

      bool is_found = false;
      auto m_item = m.begin();
      auto m_end = m.end();

      while (m_item != m_end) {
        if (m_item->second == value_to_find) {
          is_found = true;
          break;
        }

        ++m_item;
      }

      if (is_found) {
        std::cout << "  Found:: " << m_item->first << " : " << m_item->second << '\n';
      }
      else {
        std::cout << "  Not Found:: " << '\n';
      }
    }

    // Delete an entry with a key
    std::cout << "Delete by key" << '\n';
    std::cout << "Map before deletion (Count: " << m.size() << ")" << '\n';
    print_map(m);
    {
      int key_to_find = 1;
      auto it = m.find(key_to_find);
      if (it != m.end()) {
        m.erase(it);
      }
    }
    std::cout << "Map after deletion (Count: " << m.size() << ")" << '\n';
    print_map(m);
  }

  // Map with custom Compare
  {
    std::cout << "std::map with default comparator ---" << '\n';
    {
      std::map<std::string, std::string> m;
      m.insert(std::make_pair("zz", "entry1"));
      m.insert(std::make_pair("tt", "entry2"));
      m.insert(std::make_pair("cc", "entry3"));
      m.insert(std::make_pair("dd", "entry4"));
      m.insert(std::make_pair("ee", "entry5"));
      m.insert(std::make_pair("aa", "entry6"));
      for (auto item: m) {
        std::cout << item.first << " : " << item.second << '\n';
      }
    }

    std::cout << "std::map with custom comparator ---" << '\n';
    {
      struct comparator {
        bool operator()(const std::string &left, const std::string &right) const {
          return left > right;
        }
      };

      std::map<std::string, std::string, comparator> m;
      m.insert(std::make_pair("zz", "entry1"));
      m.insert(std::make_pair("tt", "entry2"));
      m.insert(std::make_pair("cc", "entry3"));
      m.insert(std::make_pair("dd", "entry4"));
      m.insert(std::make_pair("ee", "entry5"));
      m.insert(std::make_pair("aa", "entry6"));
      for (auto item: m) {
        std::cout << item.first << " : " << item.second << '\n';
      }
    }
  }

  return 0;
}
