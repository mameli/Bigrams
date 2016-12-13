#include "mainLetters.h"

int main ()
{
  unordered_map<string, int> hashMapWords;
  unordered_map<string, int> hashMapLetters;

  std::ifstream input("file_prova_small.txt");
  std::stringstream textStream;

  while(input >> textStream.rdbuf());

  string text = textStream.str();
  to_lower(text);
  string temp = "";

  vector<string> vTokens;
  vector<string>::iterator it;
  vector<string>::iterator itPeek;

  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));

  boost::timer timeLetters;
  for (it = vTokens.begin(); it != vTokens.end(); ++it) {
    for (unsigned i = 0; i < it->length(); i++) {
      tokLetter = it->substr(i,2);
      if (tokLetter.length()==2 && hashMapLetters[tokLetter]==0)
        hashMapLetters[tokLetter]=1;
      else if (tokLetter.length()==2 && hashMapLetters[tokLetter]!=0)
        hashMapLetters.find(tokLetter)->second++;
    }
  }
  double elapsed_timeLetters = timeLetters.elapsed();
  std::cout << elapsed_timeLetters << '\n';

  cout << "the hashMapLetters contains:"<< std::endl;
  string stars = "";
  for ( auto it = hashMapLetters.begin(); it != hashMapLetters.end(); ++it ){
    stars = "";
    for (size_t i = 0; i < it->second; i++) {
      stars += "*";
    }
    cout << " " << it->first << ":" << stars<< endl;
  }

  return 0;
}