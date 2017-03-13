mkdir -p ../bin
g++ -std=c++11 ../bigramPar.cpp -o ../bin/bigramParallel.out -lboost_system -lpthread

../bin/bigramParallel.out ../testFiles/Italiano/1.txt 4
