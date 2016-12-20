#include "include/Bigrams.hpp"
#include "readFileUtility.cpp"
#include "threadsafe_unordered_map.hpp"

unordered_map<string, int> hashMap;

boost::container::vector<string> vTokens;

void sequentialBigram();

int main (int argc,char const *argv[]){
  ReadFileUtility readFile;

  if (argc == 2){
    string path = argv[1]; std::cout << path << '\n';
    vTokens = readFile.readInputFile(path);
  }else
    vTokens = readFile.readInputFile("testFiles/file_prova.txt");

  sequentialBigram();

  return 0;
}

void sequentialBigram(){
  string tokLetter;
  hashMap.rehash(vTokens.size()/4);
  Timer timer;
  timer.start();

  for (size_t i = 0; i < vTokens.size(); i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMap.count(tokLetter)==0)
          hashMap[tokLetter]=1;
        else
          hashMap.find(tokLetter)->second++;
      }
    }
  }

  timer.stop();
  std::cout << "time sequential " << timer.getElapsedTimeInSec() << " s \n";
}
