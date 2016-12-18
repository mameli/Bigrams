#include <atomic>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <utility>
using namespace std;
struct Value
{
  std::atomic<int> x;
};

template<typename keyType>  class threadsafe_unordered_map {

private:
  std::unordered_map<keyType, Value > hashtable; // global
  std::mutex mtx;

public:
  Value& find(const keyType& key) {
    return hashtable[key];
  }

  void insert(const keyType& key , int val){
    std::lock_guard<std::mutex> guard{mtx};
    auto& ref = find(key);
    ref.x.store(val);
  }

  int count(const keyType& key){
    std::lock_guard<std::mutex> guard{mtx};
    return hashtable.count(key);
  }

  void add(const keyType& key, int x){
    std::lock_guard<std::mutex> guard{mtx};
    auto& ref = find(key);
    int oldVal = ref.x.load();
    int newVal = oldVal + x;
    ref.x.store(newVal);
  }

  void compare(std::unordered_map<keyType, int> mapComparing){
    std::lock_guard<std::mutex> guard{mtx};
    cout << "the hashMapLetters is:"<< std::endl;
    string temp = "";
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
      temp = it->first;
      if (mapComparing.find(temp)->second != it->second.x) {
        std::cout << "not equal" << '\n';
        return;
      }
    }
    std::cout << "good" << '\n';
  }
};
