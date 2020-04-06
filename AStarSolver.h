#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stack>
#include <queue>
#include <iterator>
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
		
		std::vector<Board_Tile> nextConfigs();
		int numMoves();
		int Manhattan_Distance(const Board_Tile& goalconfig);
		
		void setMoves(int numM, std::string m);
		std::string getMoves();
		std::string getCurrentConfigString();
		void move(char direction);
		
		std::vector<NumPoint> elements;
		int dScore = 0;
		
	private:
		std::string config[3][3];
		std::string movesFromStart = "";
		
		int numOfMoves = 0;
		
		// add 'U', 'D', 'R', or 'L'
		// each letter stands for Up, Down, Right, and Left respectively
		std::string movesTaken = "";
		
};

struct CompareConfig {
	bool operator()(Board_Tile & b1, Board_Tile & b2) {
		return (b1.dScore > b2.dScore);
	}
};

class Sliding_Solver {
	public:
		Sliding_Solver() {} // Never instantiate an empty Sliding_Solver
		virtual ~Sliding_Solver() {}
		Sliding_Solver(const std::string& str);
		
		void Solve_Puzzle();
		
	private:
		std::priority_queue<Board_Tile, std::vector<Board_Tile>, CompareConfig> tileQueue;
};