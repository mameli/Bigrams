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

int main(int argc, char**argv) {
    unordered_map<string, int> hashMap;

    hashMap.emplace("bla",1);
    hashMap.emplace("blabla",0);

    std::cout << hashMap["bla"] << '\n';
    std::cout << hashMap["blo"] << '\n';
    std::cout << hashMap.at("blo") << '\n';
    std::string text = "asdf,asdf,asdf";
    std::vector<std::string> vTokens;
    boost::split(vTokens, text, boost::is_any_of(","));
    // If I iterate through the vector there is only one element "John" and not all ?
    for (std::vector<std::string>::iterator pos = vTokens.begin(); pos != vTokens.end(); ++pos) {
        cout << *pos << endl;
    }

    return 0;
}
