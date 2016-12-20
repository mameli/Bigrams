#include "include/Bigrams.hpp"
#include "readFileUtility.cpp"
#include "threadsafe_unordered_map.hpp"

threadsafe_unordered_map<string> hashMapLetters;
unordered_map<string, int> hashMapLettersSeq;

boost::container::vector<string> vTokens;

void threadFunction(size_t bottom, size_t edge);
void sequentialBigram();
void parallelBigram();

int main(int argc, char**argv) {

  ReadFileUtility readFile;

  vTokens = readFile.readInputFile("testFiles/file_prova.txt");

  sequentialBigram();

  parallelBigram();

  hashMapLetters.compare(hashMapLettersSeq);
  return 0;
}

void sequentialBigram(){
  string tokLetter;
  hashMapLettersSeq.rehash(vTokens.size()/4);
  Timer timer;
  timer.start();

  for (size_t i = 0; i < vTokens.size(); i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLettersSeq.count(tokLetter)==0)
          hashMapLettersSeq[tokLetter]=1;
        else
          hashMapLettersSeq.find(tokLetter)->second++;
      }
    }
  }

  timer.stop();
  std::cout << "time sequential " << timer.getElapsedTimeInSec() << " s \n";
}

void parallelBigram(){
  hashMapLetters.rehash(vTokens.size()/4);
  vector<thread> threads;
  int bottom = 0;
  int edge = 0;
  size_t cores = std::thread::hardware_concurrency();

  Timer timer;
  timer.start();

  for (size_t i = 0; i < cores; i++) {
    edge = vTokens.size()*(i+1)/cores;
    threads.push_back(std::thread(threadFunction,bottom,edge));
    bottom = edge;
  }
  for (auto& th : threads) th.join();

  timer.stop();
  std::cout << "time   thread   " << timer.getElapsedTimeInSec() << " s \n";
}

void threadFunction(size_t bottom, size_t edge){
  string tokLetter;
  for (size_t i = bottom; vTokens.size() >= (edge-1) && i < edge; i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLetters.count(tokLetter)==0)
          hashMapLetters.insert(tokLetter);
        else
          hashMapLetters.add(tokLetter);
      }
    }
  }
}
