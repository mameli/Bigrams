#include "headers/mainLetters.hpp"
#include "threadsafe_unordered_map.hpp"
#include <chrono>

threadsafe_unordered_map<string> hashMapLetters;
unordered_map<string, int> hashMapLettersSeq;
vector<string> vTokens;
string tokLetter;

void threadFunction(size_t bottom, size_t edge);
void sequentialBigram();
void parallelBigram();
void readInputFile();

int main(int argc, char**argv) {

  readInputFile();

  sequentialBigram();

  parallelBigram();

  hashMapLetters.compare(hashMapLettersSeq);
  return 0;
}

void sequentialBigram(){
  hashMapLettersSeq.rehash(vTokens.size()/4);
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  for (size_t i = 0; i < vTokens.size(); i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLettersSeq.count(tokLetter)==0)
          hashMapLettersSeq[tokLetter]=1;
        else
          hashMapLettersSeq.find(tokLetter)->second++;
      }
    }
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << time_span.count()  << " seconds "<<"Sequential "<<endl;
}

void parallelBigram(){
  hashMapLetters.rehash(vTokens.size()/4);
  vector<std::thread> threads;
  int bottom = 0;
  int edge = 0;
  size_t cores = std::thread::hardware_concurrency();
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  for (size_t i = 0; i < cores; i++) {
    edge = vTokens.size()*(i+1)/cores;
    threads.push_back(std::thread(threadFunction,bottom,edge));
    bottom = edge;
  }
  for (auto& th : threads) th.join();
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << time_span.count()  << " seconds "<<"Thread safe "<<endl;
}

void threadFunction(size_t bottom, size_t edge){
  string tokLetter;
  for (size_t i = bottom; vTokens.size() >= (edge-1) && i < edge; i++) {
    for (size_t j = 0; j < vTokens[i].length(); j++) {
      tokLetter = vTokens[i].substr(j,2);
      if (tokLetter.length()==2){
        if (hashMapLetters.count(tokLetter)==0)
          hashMapLetters.insert(tokLetter);
        else
          hashMapLetters.add(tokLetter);
      }
    }
  }
}

void readInputFile(){
  std::ifstream input("testFiles/file_prova_ez.txt");
  std::stringstream textStream;
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  while(input >> textStream.rdbuf());
  string text = textStream.str();
  to_lower(text);
  boost::split(vTokens, text, boost::is_any_of(" \n,.:)*('\""));
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << time_span.count()  << " seconds "<<"Tempo di caricamento del file "<<endl;
}
