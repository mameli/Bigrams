#include "headers/mainWords.hpp"
#include "threadsafe_unordered_map.hpp"

threadsafe_unordered_map<std::string> hashMapLetters;
vector<string> vTokens;

void threadFunction(size_t bottom, size_t edge);

int main(int argc, char**argv) {
  std::ifstream input("testFiles/file_prova.txt");
  std::stringstream textStream;

  while(input >> textStream.rdbuf());

  string text = textStream.str();
  to_lower(text);

  vector<string>::iterator it;

  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));

  vector<std::thread> threads;

  boost::timer timeLetters;
  for (size_t i = 0; i < 3; i++) {
    int bottom = i;
    int edge = vTokens.size()*(i+1)/4;
    threads.push_back(std::thread(threadFunction,bottom,edge));
  }
  double elapsed_timeLetters = timeLetters.elapsed();
  std::cout << elapsed_timeLetters << " thread safe\n";

  return 0;
}

void threadFunction(size_t bottom, size_t edge){
  string tokLetter;
  for (size_t i = bottom; i < edge; i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLetters.count(tokLetter)==0)
          hashMapLetters.insert(tokLetter,1);
        else
          hashMapLetters.add(tokLetter,1);
      }
    }
  }
}
