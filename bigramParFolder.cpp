#include "include/Bigrams.hpp"
#include "FileUtility.cpp"
#include "threadsafe_unordered_map.hpp"
#include <cstdlib>
#include <stdio.h>
#include <dirent.h>

threadsafe_unordered_map<string> hashMap;

boost::container::vector<string> words;
boost::container::vector<string> wordsTemp;

void countFunction(size_t bottom, size_t edge);
void parallelBigram(size_t nCores);

int main(int argc, char **argv)
{
  FileUtility readFile;
  size_t cores = 0;
  int threshold = 0;
  uint limitWords = 5000000;
  if (argc >= 2)
  {
    if (argc == 3)
      cores = atoi(argv[2]);
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
          parallelBigram(cores);
          threshold = 1;
          std::cout << "exec" << std::endl;
          words.clear();
        }
        if (words.size() < limitWords && threshold != 1){
          std::cout << "add" << file << std::endl;
          words.insert(words.end(), wordsTemp.begin(), wordsTemp.end());
          counter++;
        }
        if (words.size() > limitWords && threshold != 1){
          parallelBigram(cores);
          words.clear();
        }
        threshold = 0;
      }
    }
  }
  if (!words.empty())
    parallelBigram(cores);
  timer.stop();
  std::cout  << timer.getElapsedTimeInSec() << "\n";
  closedir (dpdf);
  hashMap.writeHtmlFile("./bigrams.html");
  std::cout  << "File processed " << counter << "\n";
  std::cout  << "Index.html done" << "\n";

  return 0;
}

void parallelBigram(size_t nCores)
{
  hashMap.rehash(words.size()*4);
  vector<thread> threads;
  int bottom = 0;
  int edge = 0;
  size_t cores = 0;

  if (nCores > 0)
  {
    cores = nCores;
  }
  else
    cores = std::thread::hardware_concurrency();

  Timer timer;
  timer.start();

  for (size_t i = 0; i < cores; i++)
  {
    edge = words.size() * (i + 1) / cores;
    threads.push_back(std::thread(countFunction, bottom, edge));
    bottom = edge;
  }
  for (auto &th : threads)
    th.join();

  timer.stop();
  std::cout << timer.getElapsedTimeInSec() << "\n";
}

void countFunction(size_t bottom, size_t edge)
{
  string bigram;
  for (size_t i = bottom; words.size() >= (edge - 1) && i < edge; i++)
  {
    for (size_t j = 0; j < (words[i].length() - 1); j++)
    {
      bigram = words[i].substr(j, 2);
      if (hashMap.count(bigram) == 0)
        hashMap.insert(bigram);
      else
        hashMap.add(bigram);
    }
  }
}
