#include "headers/mainWords.hpp"
#include "threadsafe_unordered_map.hpp"

unordered_map<std::string,int> hashMapLetters;
vector<string> vTokens;

void threadFunction(size_t bottom, size_t edge);

int main(int argc, char**argv) {
  std::ifstream input("testFiles/file_prova_ez.txt");
  std::stringstream textStream;

  while(input >> textStream.rdbuf());

  string text = textStream.str();
  to_lower(text);

  vector<string>::iterator it;

  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));

  hashMapLetters.rehash(20);
  boost::timer timeLetters;
  int bottom = 0;
  for (size_t i = 0; i < 4; i++) {
    int edge = vTokens.size()*(i+1)/4;
    std::cout << "bottom: " << bottom << '\n';
    std::cout << "edge: " << edge << '\n';
    threadFunction(bottom,edge);
    bottom = edge;
  }
  double elapsed_timeLetters = timeLetters.elapsed();
  std::cout << elapsed_timeLetters << " splitted\n";

  cout << "the hashMapLetters contains:"<< std::endl;
  string stars = "";
  for ( auto it = hashMapLetters.begin(); it != hashMapLetters.end(); ++it ){
    stars = "";
    for (int i = 0; i < it->second; i++) {
      stars += "*";
    }
    cout << " " << it->first << ":" << stars<< endl;
  }

  return 0;
}

void threadFunction(size_t bottom, size_t edge){
  string tokLetter;
  for (size_t i = bottom; vTokens.size() >= (edge-1) && i < edge; i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLetters.count(tokLetter)==0)
          hashMapLetters[tokLetter]=1;
        else
          hashMapLetters.find(tokLetter)->second++;
      }
    }
  }
}
