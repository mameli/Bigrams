g++ -std=c++11 ../compareResult.cpp -o ../bin/compare.out -lboost_system -lpthread

../bin/compare.out

# g++ -std=c++11 ../bigramPar.cpp -o ../bin/par.out -lboost_system -lpthread
# g++ -std=c++11 ../bigramSeq.cpp -o ../bin/seq.out -lboost_system -lpthread
#
# [ -e parResults.txt ] && rm parResults.txt
# ../bin/par.out ../testFiles/file_prova_0.txt>>parResults.txt
# ../bin/par.out ../testFiles/file_prova_1.txt>>parResults.txt
# ../bin/par.out ../testFiles/file_prova_2.txt>>parResults.txt
# ../bin/par.out ../testFiles/file_prova_perm.txt>>parResults.txt
#
# [ -e seqResults.txt ] && rm seqResults.txt
# ../bin/seq.out ../testFiles/file_prova_0.txt>>seqResults.txt
# ../bin/seq.out ../testFiles/file_prova_1.txt>>seqResults.txt
# ../bin/seq.out ../testFiles/file_prova_2.txt>>seqResults.txt
# ../bin/seq.out ../testFiles/file_prova_perm.txt>>seqResults.txt
