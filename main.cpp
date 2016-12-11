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
  unordered_map<string, int> hashMap;

  string text = "blu rosso blu rosso verde blu verde rosso verde";
  cout << text << '\n';

  vector<string> vTokens;
  vector<string>::iterator it;
  vector<string>::iterator itPeek;
  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" "));
  for (it = vTokens.begin(); it != vTokens.end(); ++it) {
    itPeek = boost::next(it, 1);
    if (*itPeek != "")
      hashMap.emplace(*it+" "+*itPeek,0);
    for (unsigned i = 0; i < it->length(); i += 2) {
      tokLetter = it->substr(i,2);
      if (tokLetter.length()==2) {
        std::cout << tokLetter << '\n';
      }
    }

  }

  for ( auto itMap = hashMap.begin(); itMap != hashMap.end(); ++itMap ){
    for (it = vTokens.begin(); it != vTokens.end(); ++it) {
      itPeek = boost::next(it, 1);
      if (itMap->first == *it+" "+*itPeek)
          itMap->second++;
    }
  }

  cout << "the hashmap contains:"<< std::endl;
  for ( auto it = hashMap.begin(); it != hashMap.end(); ++it )
    cout << " " << it->first << ":" << it->second<< endl;

  return 0;
}
