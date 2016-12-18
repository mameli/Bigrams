#include "headers/mainWords.hpp"
#include "threadsafe_unordered_map.hpp"

threadsafe_unordered_map<std::string> hashMapLetters;
unordered_map<string, int> hashMapLettersSeq;
vector<string> vTokens;

void foo(size_t bottom, size_t edge){
  string tokLetter;
  for (size_t i = bottom; i < edge; i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLettersSeq.count(tokLetter)==0)
          hashMapLetters.insert(tokLetter,1);
        else
          hashMapLetters.add(tokLetter,1);
      }
    }
  }
}

int main(int argc, char**argv) {
  hashMapLettersSeq.rehash(256);
  std::ifstream input("testFiles/file_prova.txt");
  std::stringstream textStream;

  while(input >> textStream.rdbuf());

  string text = textStream.str();
  to_lower(text);

  vector<string>::iterator it;

  string tokLetter;
  boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));

  vector<std::thread> threads;
  boost::timer timeLettersSeq;

  for (it = vTokens.begin(); it != vTokens.end(); ++it) {
    for (unsigned i = 0; i < it->length(); i++) {
      tokLetter = it->substr(i,2);
      if (tokLetter.length()==2){
        if (hashMapLettersSeq.count(tokLetter)==0)
          hashMapLettersSeq[tokLetter]=1;
        else
          hashMapLettersSeq.find(tokLetter)->second++;
      }
    }
  }
  double elapsed_timeLettersSeq = timeLettersSeq.elapsed();
  std::cout << elapsed_timeLettersSeq << '\n';

  boost::timer timeLetters;
  // for (it = vTokens.begin(); it != vTokens.end(); ++it) {
  //   for (unsigned i = 0; i < it->length(); i++) {
  //     tokLetter = it->substr(i,2);
  //     if (tokLetter.length()==2){
  //       if (hashMapLetters.count(tokLetter)==0)
  //         hashMapLetters.insert(tokLetter,1);
  //       else
  //         hashMapLetters.add(tokLetter,1);
  //     }
  //   }
  // }
  for (size_t i = 0; i < 3; i++) {
    int bottom = i;
    int edge = vTokens.size()*(i+1)/4;
    threads.push_back(std::thread(foo,bottom,edge));
  }
  double elapsed_timeLetters = timeLetters.elapsed();
  std::cout << elapsed_timeLetters << " thread safe\n";
  hashMapLetters.compare(hashMapLettersSeq);

  return 0;
}
