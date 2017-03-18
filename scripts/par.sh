mkdir -p ../bin
g++ -std=c++11 ../bigramPar.cpp -o ../bin/bigramParallel.out -lboost_system -lpthread

../bin/bigramParallel.out ../testFiles/file_prova_2.txt 4
