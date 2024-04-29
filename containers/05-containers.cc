//
// Program
//  Containers: std::multimap & std::multiset usage
//  - Simple multimap
//  - multimap: Use lower_bound and upper_bound
//  - multimap: Erase entries using lower_bound, upper_bound
//  - multiset: std::multiset with c-structure
//
// Compile
//  g++ -Wall -Wextra -pedantic -std=c++17 -o 05-containers 05-containers.cc
//
// Execution
//  ./05-containers
//

#include <iostream>
#include <map>
#include <set>

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
  std::cout << "--- std::multimap ---" << '\n';

  // Simple std::multimap declaration
  {
    std::multimap<int, std::string> m;

    m.insert({1, "entry1"});
    m.insert({2, "entry2"});
    m.insert(std::make_pair(3, "entry3"));

    std::cout << "Size: " << m.size() << '\n'; // 3 items are there
    std::cout << "Is empty: " << std::boolalpha << m.empty() << '\n'; // Not empty
    std::cout << "Max size: " << m.max_size() << '\n';
    std::cout << "Key # 3 is having count: " << m.count(3) << '\n'; // 1 entry of a specific key

    std::cout << "Show items of the map" << '\n';
    print_map(m);

    m.insert(std::make_pair(3, "entry3_2"));
    std::cout << "Key # 3 is having count: " << m.count(3) << '\n'; // 1 entry of a specific key
    print_map(m);
  }

  // Lower bound
  std::cout << "Lower bound ---" << '\n';
  {
    std::multimap<int, std::string> m;

    m.insert(std::make_pair(1, "entry1"));
    m.insert(std::make_pair(2, "entry2"));
    m.insert(std::make_pair(3, "entry3"));
    m.insert(std::make_pair(4, "entry4"));
    m.insert(std::make_pair(5, "entry5"));
    // m.insert(std::make_pair(6, "entry6"));
    m.insert(std::make_pair(7, "entry7"));
    m.insert(std::make_pair(8, "entry8"));
    m.insert(std::make_pair(9, "entry9"));

    std::cout << "Size: " << m.size() << '\n';

    auto lstart = m.begin();

    // Found the node which is not less than key
    // If key is in the map our _bound will return that
    // iterator otherwise it will point to the possible
    // location
    auto lend = m.lower_bound(6);
    if (lstart != lend) {
      int idx = 0;
      while (lstart != lend) {
        std::cout << idx << " : " << lstart->first << ", " << lstart->second << '\n';
        ++idx;
        ++lstart;
      }
    }
  }

  // Upper bound
  std::cout << "Upper bound ---" << '\n';
  {
    std::multimap<int, std::string> m;

    m.insert(std::make_pair(1, "entry1"));
    m.insert(std::make_pair(2, "entry2"));
    m.insert(std::make_pair(3, "entry3"));
    m.insert(std::make_pair(4, "entry4"));
    m.insert(std::make_pair(5, "entry5"));
    // m.insert(std::make_pair(6, "entry6"));
    m.insert(std::make_pair(7, "entry7"));
    m.insert(std::make_pair(8, "entry8"));
    m.insert(std::make_pair(9, "entry9"));

    std::cout << "Size: " << m.size() << '\n';

    // Found the node which is greater than key
    // If key is in the map our _bound will return that
    // iterator otherwise it will point to the possible
    // location
    auto lstart = m.upper_bound(6);
    auto lend = m.end();
    if (lstart != lend) {
      int idx = 0;
      while (lstart != lend) {
        std::cout << idx << " : " << lstart->first << ", " << lstart->second << '\n';
        ++idx;
        ++lstart;
      }
    }
  }

  // Erase range
  std::cout << "Erase ---" << '\n';
  {
    std::multimap<int, std::string> m;

    m.insert(std::make_pair(1, "entry1"));
    m.insert(std::make_pair(2, "entry2"));
    m.insert(std::make_pair(3, "entry3"));
    m.insert(std::make_pair(4, "entry4"));
    m.insert(std::make_pair(5, "entry5"));
    // m.insert(std::make_pair(6, "entry6"));
    m.insert(std::make_pair(7, "entry7"));
    m.insert(std::make_pair(8, "entry8"));
    m.insert(std::make_pair(9, "entry9"));

    std::cout << "Size before delete: " << m.size() << '\n';
    print_map(m);

    auto lstart = m.upper_bound(6);
    auto lend = m.upper_bound(8);
    m.erase(lstart, lend);

    std::cout << "Size after delete: " << m.size() << '\n';
    print_map(m);
  }

  // Structure
  std::cout << "std::set with structure ---" << '\n';
  {
    struct Object {
      int id;
      std::string name;
      bool operator< (const Object& second) const {
        return (id < second.id);
      }
    };

    std::multiset<Object> set;
    set.insert({1, "test1"});
    set.insert({2, "test2"});
    set.insert({3, "test3"});

    for (const auto& obj: set) {
      std::cout << "{" << obj.id << ", " << obj.name << "}\n";
    }
  }

  return 0;
}

// Output
// --- std::multimap ---
// Size: 3
// Is empty: false
// Max size: 128102389400760775
// Key # 3 is having count: 1
// Show items of the map
// 1 : entry1
// 2 : entry2
// 3 : entry3
// Key # 3 is having count: 2
// 1 : entry1
// 2 : entry2
// 3 : entry3
// 3 : entry3_2
// Lower bound ---
// Size: 8
// 0 : 1, entry1
// 1 : 2, entry2
// 2 : 3, entry3
// 3 : 4, entry4
// 4 : 5, entry5
// Upper bound ---
// Size: 8
// 0 : 7, entry7
// 1 : 8, entry8
// 2 : 9, entry9
// Erase ---
// Size before delete: 8
// 1 : entry1
// 2 : entry2
// 3 : entry3
// 4 : entry4
// 5 : entry5
// 7 : entry7
// 8 : entry8
// 9 : entry9
// Size after delete: 6
// 1 : entry1
// 2 : entry2
// 3 : entry3
// 4 : entry4
// 5 : entry5
// 9 : entry9
// std::set with structure ---
// {1, test1}
// {2, test2}
// {3, test3}
