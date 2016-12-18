#include "threadsafe_unordered_map.hpp"
#include <string>
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>

threadsafe_unordered_map<std::string> map;

void set_foo( int x) {
  map.insert("bla", x);
}

void print_foo() {
  while (map.find("bla").x==0) {
    std::this_thread::yield();
  }
  std::cout << "foo: " << map.find("bla").x << '\n';
}

int main(int argc, char const *argv[]) {

  map.insert("bla", 0);

  std::cout << map.count("bla") << '\n';

  std::thread first (print_foo);
  std::thread second (set_foo,10);

  first.join();
  second.join();

  return 0;
}
