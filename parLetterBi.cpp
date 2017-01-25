#include "include/Bigrams.hpp"
#include "readFileUtility.cpp"
#include "threadsafe_unordered_map.hpp"

threadsafe_unordered_map<string> hashMap;

boost::container::vector<string> vTokens;

void threadFunction(size_t bottom, size_t edge);
void parallelBigram();

int main(int argc, char**argv) {
  ReadFileUtility readFile;

  if (argc == 2){
    string path = argv[1];
    // std::cout <<"File usato : "<< path << '\n';
    vTokens = readFile.readInputFile(path);
  }

  parallelBigram();

  return 0;
}

void parallelBigram(){
  hashMap.rehash(vTokens.size());
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
  std::cout  << timer.getElapsedTimeInSec() << "\n";
  // std::cout << "time   thread   " << timer.getElapsedTimeInSec() << " s \n";
}

void threadFunction(size_t bottom, size_t edge){
  string tokLetter;
  for (size_t i = bottom; vTokens.size() >= (edge-1) && i < edge; i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMap.count(tokLetter)==0)
          hashMap.insert(tokLetter);
        else
          hashMap.add(tokLetter);
      }
    }
  }
}
