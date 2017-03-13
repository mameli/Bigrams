#include "include/Bigrams.hpp"
#include "FileUtility.cpp"
#include "threadsafe_unordered_map.hpp"
#include <cstdlib>
#include <stdio.h>
#include <dirent.h>

unordered_map<string, uint> hashMap;

boost::container::vector<string> words;
boost::container::vector<string> wordsTemp;

void sequentialBigram();

int main (int argc,char const *argv[]){
    FileUtility readFile;
    size_t cores = 0;
    int threshold = 0;
    uint limitWords = 5000000;
    if (argc >= 2){
      if (argc == 3) cores = atoi(argv[2]);
    }

   DIR *dpdf;
  struct dirent *epdf;
  string path = argv[1];
  dpdf = opendir(argv[1]);
  string file = "";
  Timer timer;
  timer.start();
  int counter = 0;
  if (dpdf != NULL){
    while ((epdf = readdir(dpdf)) != NULL){
      if (!strcmp(epdf->d_name, ".") || !strcmp(epdf->d_name, "..")){}
      else{
        file = path + "/" + epdf->d_name;
        wordsTemp = readFile.readInputFile(file);
        if (wordsTemp.size() >= limitWords){
          words = wordsTemp;
          sequentialBigram();
          threshold = 1;
          std::cout << "exec" << std::endl;
          words.clear();
        }
        if (words.size() < limitWords && threshold != 1){
          std::cout << "add" << std::endl;
          words.insert(words.end(), wordsTemp.begin(), wordsTemp.end());
        }
        if (words.size() > limitWords && threshold != 1){
          sequentialBigram();
          words.clear();
        }
        threshold = 0;
        std::cout << file << std::endl;
        counter++;
      }
    }
  }
  if (!words.empty())
    sequentialBigram();
  timer.stop();
  std::cout  << "Time: "<<timer.getElapsedTimeInSec() << "\n";
  closedir (dpdf);

  std::cout  << "File processed " << counter << "\n";

  std::cout  <<hashMap.find("er")->second << "\n";
  return 0;
}

void sequentialBigram(){
  string bigram;
  hashMap.rehash(words.size());
  Timer timer;
  timer.start();

  for (size_t i = 0; i < words.size(); i++) {
    for (size_t j = 0; j < (words[i].length()-1); j++) {
      bigram = words[i].substr(j,2);
      if (hashMap.count(bigram)==0)
        hashMap[bigram]=1;
      else
        hashMap.find(bigram)->second++;
    }
  }

  timer.stop();
  std::cout << timer.getElapsedTimeInSec()<< "\n";
  // std::cout << "time sequential " << timer.getElapsedTimeInSec() << " s \n";
}
