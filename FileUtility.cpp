#include "include/Timer.cpp"
#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/container/vector.hpp>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

class FileUtility {
private:
  boost::container::vector<string> words;
public:

  boost::container::vector<string> readInputFile(string path){
    ifstream input(path);
    stringstream textStream;

    while(input >> textStream.rdbuf());
    string text = textStream.str();

    char_separator<char> sep(".;:)(*',_?!-#$%&[]{}<>\t\n\\\r\'\"\a\f\b\v ");
    tokenizer<char_separator<char>> tokens(text, sep);
    BOOST_FOREACH(string s, tokens){
      words.push_back(s);
    }
    return words;
  }
};
