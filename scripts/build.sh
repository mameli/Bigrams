#!/bin/bash

c++ -std=c++11 -I /usr/local/include/boost/ \
mainLetters.cpp -o letters.out \
/usr/local/lib/libboost_thread.a \
/usr/local/lib/libboost_chrono.a \
-lboost_system -lpthread

c++ -std=c++11 -I /usr/local/include/boost/ \
mainWords.cpp -o words.out \
/usr/local/lib/libboost_thread.a \
/usr/local/lib/libboost_chrono.a \
-lboost_system -lpthread
