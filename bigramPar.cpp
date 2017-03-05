#include "include/Bigrams.hpp"
#include "FileUtility.cpp"
#include "threadsafe_unordered_map.hpp"
#include <cstdlib>
#include <stdio.h>
#include <dirent.h>

threadsafe_unordered_map<string> hashMap;

boost::container::vector<string> words;

void countFunction(size_t bottom, size_t edge);
void parallelBigram(size_t nCores);

int main(int argc, char**argv) {
  FileUtility readFile;
  size_t cores = 0;

  if (argc >= 2){
    // string path = argv[1];
    // words = readFile.readInputFile(path);
    if (argc == 3) cores = atoi(argv[2]);
  }

  DIR *dpdf;
  struct dirent *epdf;
  string path = argv[1];
  dpdf = opendir(argv[1]);
  Timer timer;
  timer.start();
  if (dpdf != NULL){
      while ((epdf = readdir(dpdf))){
          string file = path +"/"+ epdf->d_name;
          words = readFile.readInputFile(file);
          parallelBigram(cores);
          std::cout << file << std::endl;
    }
  }
  closedir (dpdf);
  hashMap.writeHtmlFile("./bigrams.html");
  std::cout  << "Index.html done" << "\n";

  timer.stop();
  std::cout  << timer.getElapsedTimeInSec() << "\n";

  return 0;
}

void parallelBigram(size_t nCores){
  hashMap.rehash(words.size());
  vector<thread> threads;
  int bottom = 0;
  int edge = 0;
  size_t cores = 0;

  if (nCores > 0){
    cores = nCores;
  }else cores = std::thread::hardware_concurrency();

  Timer timer;
  timer.start();

  for (size_t i = 0; i < cores; i++) {
    edge = words.size()*(i+1)/cores;
    threads.push_back(std::thread(countFunction,bottom,edge));
    bottom = edge;
  }
  for (auto& th : threads) th.join();

  timer.stop();
  std::cout  << timer.getElapsedTimeInSec() << "\n";
}

void countFunction(size_t bottom, size_t edge){
  string bigram;
  for (size_t i = bottom; words.size() >= (edge-1) && i < edge; i++) {
    for (size_t j = 0; j < (words[i].length()-1); j++) {
      bigram = words[i].substr(j,2);
      if (hashMap.count(bigram)==0)
        hashMap.insert(bigram);
      else
        hashMap.add(bigram);
    }
  }
}
