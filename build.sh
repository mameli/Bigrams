mkdir -p bin

g++ -std=c++11 bigramPar.cpp -o bin/bigramParallel.out -lboost_system -lpthread
g++ -std=c++11 bigramSeq.cpp -o bin/bigramSequential.out -lboost_system -lpthread
