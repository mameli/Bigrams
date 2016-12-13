#include "mainWords.h"

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

  boost::timer timeWords;
  for (it = vTokens.begin(); it != vTokens.end(); ++it) {
    itPeek = boost::next(it, 1);
    temp = *it+" "+*itPeek;
    if (*itPeek != ""){
      if (hashMapWords[temp]==0)
        hashMapWords[temp]=1;
      else
        hashMapWords.find(temp)->second++;
    }
  }
  double elapsed_timeWords = timeWords.elapsed();
  std::cout << elapsed_timeWords << '\n';

  cout << "the hashMapWords contains:"<< std::endl;
  string stars = "";
  for ( auto it = hashMapWords.begin(); it != hashMapWords.end(); ++it ){
    stars = "";
    for (size_t i = 0; i < it->second; i++)
      stars += "*";
    cout << " " << it->first << ":" << stars<< endl;
  }

  return 0;
}
