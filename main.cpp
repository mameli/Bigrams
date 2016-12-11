#include <iostream>
#include <unordered_map>
#include <string.h>
#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace boost;

int main ()
{
  unordered_map<string, int> hashMapWords;
  unordered_map<string, int> hashMapLetters;
  string text = "blu rosso blu rosso verde blu verde rosso verde";
  cout <<"Stringa di prova:\n"+text << '\n';

  vector<string> vTokens;
  vector<string>::iterator it;
  vector<string>::iterator itPeek;
  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" "));
  for (it = vTokens.begin(); it != vTokens.end(); ++it) {
    itPeek = boost::next(it, 1);
    if (*itPeek != "") hashMapWords.emplace(*it+" "+*itPeek,0);

    for (unsigned i = 0; i < it->length(); ++i) {
      tokLetter = it->substr(i,2);
      if (tokLetter.length()==2) hashMapLetters.emplace(*it,0);
    }

  }

  for ( auto itMap = hashMapLetters.begin(); itMap != hashMapLetters.end(); ++itMap ){
    for (it = vTokens.begin(); it != vTokens.end(); ++it) {
      itPeek = boost::next(it, 1);
      if (itMap->first == *it+" "+*itPeek)
          itMap->second++;
  }

  }  for ( auto itMap = hashMapWords.begin(); itMap != hashMapWords.end(); ++itMap ){
    for (it = vTokens.begin(); it != vTokens.end(); ++it) {
      itPeek = boost::next(it, 1);
      if (itMap->first == *it+" "+*itPeek)
          itMap->second++;
    }
  }
  cout << "Bigrammi di parole" << '\n';
  cout << "the hashMapWords contains:"<< std::endl;
  for ( auto it = hashMapWords.begin(); it != hashMapWords.end(); ++it )
    cout << " " << it->first << ":" << it->second<< endl;

  return 0;
}
