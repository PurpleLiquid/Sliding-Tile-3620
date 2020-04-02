#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <bits/stdc++.h>

struct NotConfig : public std::exception {
	const char * what () const throw () {
    	return "Not a 3x3 Configuration";
    }
};

struct NumPoint {
	int num, x, y;
	
	NumPoint() {}
	NumPoint(int theNum, int numX, int numY)
						: num{theNum}, x{numX}, y{numY} {}
};

struct CompareNums {
	bool operator()(const NumPoint & n1, const NumPoint & n2) {
		return (n1.num < n2.num);
	}
};

class StringMagician {
	public:
		StringMagician() {}
		virtual ~StringMagician() {}
		
		std::vector<std::string> extractInts(const std::string str);
		void printAll(std::vector<std::string> aList);
		
	private:
};

class Board_Tile {
	public:
		Board_Tile() {}
		virtual ~Board_Tile() {}
		Board_Tile(const std::string& str);
		
		std::list<Board_Tile> nextConfigs();
		int numMoves();
		int Manhattan_Distance(const Board_Tile& goalconfig);
		
		std::vector<NumPoint> elements;
		
	private:
		std::string config[3][3];
		std::string movesFromStart = "";
		
};

/*struct CompareConfig {
	bool operator()(const Board_Tile & b1, const Board_Tile & b2) {
		return (b1.)
	}
};*/

class Sliding_Solver {
	public:
		Sliding_Solver() {}
		virtual ~Sliding_Solver() {}
		Sliding_Solver(const std::string&);
		
		void Solve_Puzzle();
		
	private:
		//std::priority_queue<Board_Tile> tileQueue;
};