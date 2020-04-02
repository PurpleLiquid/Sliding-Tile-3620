#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

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
		
	private:
		std::string config[3][3];
		std::string movesFromStart = "";
};

class BinaryHeap {
	public:
		BinaryHeap() {}
		
		virtual ~BinaryHeap() {}
		void insert(std::string str);
		void printAll();
	
	private:
		int currentSize = 0;
		std::vector<std::string> heap;
};

class Sliding_Solver {
	public:
		Sliding_Solver() {}
		virtual ~Sliding_Solver() {}
		Sliding_Solver(const std::string&);
		
		void Solve_Puzzle();
		
	private:
		
};