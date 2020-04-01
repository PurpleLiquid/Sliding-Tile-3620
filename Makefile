CXX=g++
CXXFLAGS= -std=c++11 -g -lpthread

all: main

main: AStarSolver.o
	$(CXX) $(CXXFLAGS) $^ -o $@

AStarSolver.o: AStarSolver.h

clean:
	rm -rf *.o *~ *% *# .#*
	
clean-all: clean
	rm -rf main