# Makefile for compiling

all:
        g++ -c -std=c++11 main.cpp
        g++ -c -std=c++11 AI.cpp
        g++ -c -std=c++11 Dictionary.cpp
        g++ -c -std=c++11 AbstractToken.cpp
        g++ -c -std=c++11 KeyWord.cpp
        g++ -c -std=c++11 SpeakObject.cpp

        g++ -o main main.o AI.o Dictionary.o AbstractToken.o KeyWord.o SpeakObject.o

clean:
        rm a.out
