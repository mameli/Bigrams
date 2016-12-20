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
  unordered_map<keyType, atomic<uint> > hashtable;
  mutex mtx;

public:
  void rehash(int val){
    hashtable.rehash(val);
  }
  uint find(const keyType& key) {
    return hashtable[key];
  }

  void insert(const keyType& key){
    std::lock_guard<std::mutex> guard{mtx};
    hashtable[key]++;
  }

  int count(const keyType& key){
    return hashtable.count(key);
  }

  void add(const keyType& key){
      hashtable.at(key)++;
  }

  /*Debug function*/
  void compare(std::unordered_map<keyType, uint> mapComparing){
    std::lock_guard<std::mutex> guard{mtx};

    cout << "the hashMaps are: ";
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
      std::cout << "equal"<< std::endl;
    else
      std::cout << "not equal"<< std::endl;
  }
};
