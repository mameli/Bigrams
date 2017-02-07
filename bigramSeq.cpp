#include "include/Bigrams.hpp"
#include "FileUtility.cpp"
#include "threadsafe_unordered_map.hpp"

unordered_map<string, uint> hashMap;

boost::container::vector<string> words;

void sequentialBigram();

int main (int argc,char const *argv[]){
  FileUtility readFile;

  if (argc == 2){
    string path = argv[1];
    words = readFile.readInputFile(path);
  }else
    words = readFile.readInputFile("../testFiles/file_prova_0.txt");

  sequentialBigram();

  return 0;
}

void sequentialBigram(){
  string bigram;
  hashMap.rehash(words.size()/4);
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
