#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>

class Board_Tile{
	public:
		Board_Tile() {}
		virtual ~Board_Tile() {}
		Board Tile(const std::string&);
		
		std::list<Board_Tile> nextConfigs();
		int numMoves();
		int Manhattan_Distance(const Board_Tile& goalconfig);
		
	private:
		std::string config[3][3];
};

class Sliding_Solver{
	public:
		Sliding_Solver() {}
		virtual ~Sliding_Solver() {}
		Sliding_Solver(const std::string&);
		
		void Solve_Puzzle();
		
	private:
		
};

class BinaryHeap {
	public:
		void insert(std::string str) {
			
		}
		
		BinaryNode* getHead() {
			return root;
		}
	
	private:
		int currentSize = 0;
		std::vector<std::string> heap;
		
		void insert(std::string str) {
			
		}
};