#include "headers/mainWords.hpp"

int main(int argc, char**argv) {
  unordered_map<string, int> hashMapLetters;

  std::ifstream input("testFiles/file_prova.txt");
  std::stringstream textStream;

  while(input >> textStream.rdbuf());

  string text = textStream.str();
  to_lower(text);

  vector<string> vTokens;
  vector<string>::iterator it;

  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));

  boost::timer timeLetters;
  for (it = vTokens.begin(); it != vTokens.end(); ++it) {
    for (unsigned i = 0; i < it->length(); i++) {
      tokLetter = it->substr(i,2);
      if (tokLetter.length()==2){
        if (hashMapLetters.count(tokLetter)==0)
          hashMapLetters.emplace(tokLetter,1);
        else
          hashMapLetters.find(tokLetter)->second++;
      }
    }
  }
  double elapsed_timeLetters = timeLetters.elapsed();
  std::cout << elapsed_timeLetters << '\n';

  return 0;
}
