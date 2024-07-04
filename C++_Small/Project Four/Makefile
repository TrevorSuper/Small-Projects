Clock: Clock.o
	g++ Clock.o -std=c++11 -o Clock
Clock.o: Clock.cpp Clock.h
	g++ -c -std=c++11 Clock.cpp
target: dependencies
	action
clean:
	rm *.o Clock