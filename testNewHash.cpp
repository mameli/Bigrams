#include "threadsafe_unordered_map.hpp"
#include <string>
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>

threadsafe_unordered_map<std::string> map;

void set_threadFunction( int x) {
  map.insert("bla", x);
}

void print_threadFunction() {
  while (map.find("bla").x==0) {
    std::this_thread::yield();
  }
  std::cout << "threadFunction: " << map.find("bla").x << '\n';
}

int main(int argc, char const *argv[]) {

  map.insert("bla", 0);

  std::cout << map.count("bla") << '\n';

  std::thread first (print_threadFunction);
  std::thread second (set_threadFunction,10);

  first.join();
  second.join();

  return 0;
}
