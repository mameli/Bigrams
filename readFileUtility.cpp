#include "include/Timer.cpp"
#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/container/vector.hpp>

using namespace std;
using namespace boost;

class ReadFileUtility {
private:
  boost::container::vector<string> vTokens;
public:

  boost::container::vector<string> readInputFile(string path){
    ifstream input(path);
    stringstream textStream;

    Timer timer;
    timer.start();

    while(input >> textStream.rdbuf());
    string text = textStream.str();
    to_lower(text);
    boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));

    timer.stop();
    cout << "time  load file " << timer.getElapsedTimeInSec() << " s \n";

    return vTokens;
  }
};
