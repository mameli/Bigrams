cmake_minimum_required(VERSION 3.3)
project(Bigrams)
find_package( Boost 1.62 COMPONENTS system timer chrono thread REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

include_directories( ${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

add_executable(letters mainLetters.cpp)
add_executable(words   mainWords.cpp)
add_executable(testThreads   boost_test_threads.cpp)

TARGET_LINK_LIBRARIES( letters ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES( words ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES( testThreads ${Boost_LIBRARIES})
