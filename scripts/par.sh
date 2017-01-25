g++ -std=c++11 ../parLetterBi.cpp -o ../bin/par.out -lboost_system -lpthread

[ -e parResultsSpeedUp.txt ] && rm parResultsSpeedUp.txt
../bin/par.out ../testFiles/file_prova_2.txt 1 >> parResultsSpeedUp.txt
../bin/par.out ../testFiles/file_prova_2.txt 2 >> parResultsSpeedUp.txt
../bin/par.out ../testFiles/file_prova_2.txt 3 >> parResultsSpeedUp.txt
../bin/par.out ../testFiles/file_prova_2.txt 4 >> parResultsSpeedUp.txt
