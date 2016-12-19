#include <atomic>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <utility>
using namespace std;

template<typename keyType>  class threadsafe_unordered_map {

private:
  std::unordered_map<keyType, atomic<uint> > hashtable; // global
  std::mutex mtx;

public:
  void rehash(int val){
    hashtable.rehash(val);
  }
  int find(const keyType& key) {
    return hashtable[key];
  }

  void insert(const keyType& key){
    mtx.lock();
    hashtable[key]++;
    mtx.unlock();
  }

  int count(const keyType& key){
    return hashtable.count(key);
  }

  void add(const keyType& key){
      hashtable.at(key)++;
  }

  void compare(std::unordered_map<keyType, int> mapComparing){
    std::lock_guard<std::mutex> guard{mtx};

    cout << "the hashMap compared contains:"<< std::endl;
    string stars = "";
    for ( auto it = mapComparing.begin(); it != mapComparing.end(); ++it ){
      stars = "";
      for (int i = 0; i < it->second; i++) {
        stars += "*";
      }
      cout << " " << it->first << ":" << it->second<< endl;
    }

    cout << "the hashMap thread safe contains:"<< std::endl;
    stars = "";
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
      stars = "";
      for (int i = 0; i < it->second; i++) {
        stars += "*";
      }
      cout << " " << it->first << ":" << it->second<< endl;
    }

    cout << "the hashMapLetters is:"<< std::endl;
    string temp = "";
    int b = 1;
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
      temp = it->first;
      //std::cout << "Comparing Seq \n key : " <<temp<< "\n value: " << mapComparing.find(temp)->second << "\n with atomic: "<< it->second.x<< '\n';
      if (mapComparing.find(temp)->second != it->second) {
        b = 0;
      }
    }
    if (b==1)
      std::cout << "equal" << '\n';
    else
      std::cout << "not equal" << '\n';
  }
};
