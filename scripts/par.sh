g++ -std=c++11 ../bigramPar.cpp -o ../bin/bigrammiParallelo.out -lboost_system -lpthread
../bin/bigrammiParallelo.out ../testFiles/file_prova_1.txt 4

# [ -e parResultsSpeedUp.txt ] && rm parResultsSpeedUp.txt
# ../bin/bigrammiParallelo.out ../testFiles/file_prova_1.txt 1 >> parResultsSpeedUp.txt
# ../bin/bigrammiParallelo.out ../testFiles/file_prova_1.txt 2 >> parResultsSpeedUp.txt
# ../bin/bigrammiParallelo.out ../testFiles/file_prova_1.txt 3 >> parResultsSpeedUp.txt
# ../bin/bigrammiParallelo.out ../testFiles/file_prova_1.txt 4 >> parResultsSpeedUp.txt
