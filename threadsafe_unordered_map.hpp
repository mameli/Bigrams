#include <atomic>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <utility>

using namespace std;

template<typename keyType>  class threadsafe_unordered_map {

private:
  unordered_map<keyType, atomic<uint> > hashtable;
  mutex mtx;

public:
  void add(const keyType& key){
      hashtable.at(key)++;
  }

  void insert(const keyType& key){
    std::lock_guard<std::mutex> guard{mtx};
    hashtable[key]++;
  }

  int count(const keyType& key){
    return hashtable.count(key);
  }

  void rehash(int val){
    hashtable.rehash(val);
  }

  static bool comp(pair<keyType, uint> a, pair<keyType, uint> b) {
    return a.second > b.second;
  }

  void writeHtmlFile(string path){
    ofstream htmlFile;
    htmlFile.open (path);
    htmlFile << "<!DOCTYPE html><html><head></head>";
    htmlFile << "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css\" integrity=\"sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ\" crossorigin=\"anonymous\">";
    htmlFile << "<body>";
    htmlFile << "<h1>Bigrams</h1>";
    htmlFile << "<ul class=\"col-sm-12 list-group\">\n";

    std::vector<std::pair<keyType, uint>> orderedElements;
    std::pair<keyType, uint> temp;
    uint iTemp;
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
        iTemp = it->second;
        temp = std::make_pair(it->first, iTemp);
        orderedElements.push_back(temp);
    }
    std::sort(orderedElements.begin(), orderedElements.end(), comp);

    for ( auto it = orderedElements.begin(); it != orderedElements.end(); ++it ){
     htmlFile << "<li class=\"list-group-item justify-content-between\"> <span style=\"min-width:5%\">" << it->first << "</span>";
     htmlFile << "<HR style=\"height:10px; margin-left:30px; width:"<<it->second<< "px; max-width:80%\" COLOR=\"#03c1e3\" ALIGN=\"LEFT\">";
     htmlFile << "<span class=\"badge badge-default badge-pill\"</span>"<< it->second<< "</li>\n";
    }

    htmlFile << "</ul>";
    htmlFile << "</body></html>";
    htmlFile.close();
  }

  /*Debug function*/
  void compare(std::unordered_map<keyType, uint> mapComparing){
    std::lock_guard<std::mutex> guard{mtx};


    int stars = 0;
    cout << "the hashMap thread safe contains:"<< std::endl;
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
     stars = 0;
     for (int i = 0; i < it->second; i++) {
       stars++;
     }
     cout << " " << it->first << ":" << stars<< endl;
    }

    cout << "the hashMaps are: ";
    string temp = "";
    int b = 1;
    for ( auto it = hashtable.begin(); it != hashtable.end(); ++it ){
      temp = it->first;
      // std::cout << "Comparing Seq \n key : " <<temp<< "\n value: " << mapComparing.find(temp)->second << "\n with atomic: "<< it->second<< '\n';
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
