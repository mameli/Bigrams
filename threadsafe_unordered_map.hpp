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
  void rehash(int val){
    hashtable.rehash(val);
  }

  Value& find(const keyType& key) {
    return hashtable[key];
  }

  void insert(const keyType& key , int val){
    // std::lock_guard<std::mutex> guard{mtx};
    auto& ref = hashtable[key];
    ref.x.store(val);
  }

  int count(const keyType& key){
    std::lock_guard<std::mutex> guard{mtx};
    return hashtable.count(key);
  }

  void add(const keyType& key, int x){
    std::lock_guard<std::mutex> guard{mtx};
    auto& ref = hashtable[key];
    ref.x.store(ref.x.load()+x);
  }

  void compare(std::unordered_map<keyType, int> mapComparing){
    std::lock_guard<std::mutex> guard{mtx};

    // cout << "the hashMap compared contains:"<< std::endl;
    string stars = "";
    // for ( auto it = mapComparing.begin(); it != mapComparing.end(); ++it ){
    //   stars = "";
    //   for (int i = 0; i < it->second; i++) {
    //     stars += "*";
    //   }
    //   cout << " " << it->first << ":" << it->second<< endl;
    // }
    //
    cout << "the hashMap thread safe contains:"<< std::endl;
    stars = "";
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
      stars = "";
      for (int i = 0; i < it->second.x; i++) {
        stars += "*";
      }
      cout << " " << it->first << ":" << it->second.x<< endl;
    }

    cout << "the hashMapLetters is:"<< std::endl;
    string temp = "";
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
      temp = it->first;
      //std::cout << "Comparing Seq \n key : " <<temp<< "\n value: " << mapComparing.find(temp)->second << "\n with atomic: "<< it->second.x<< '\n';
      if (mapComparing.find(temp)->second != it->second.x) {
        std::cout << "not equal" << '\n';
      }
    }
    std::cout << "equal" << '\n';
  }
};
