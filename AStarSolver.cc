#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <queue>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <bits/stdc++.h>
#include "AStarSolver.h"

// Requested Functions
Board_Tile::Board_Tile(const std::string& str) {
	StringMagician sm;
	
	// If exception occurs should terminate program
	std::vector<std::string> ints = sm.extractInts(str);
	int indl = 0;
	
	for(int y = 0; y < 3; y++) {
		for(int x = 0; x < 3; x++) {
			Board_Tile::config[y][x] = ints[indl];
			
			NumPoint n = {
				.num = std::stoi(ints.at(indl)),
				.x = x,
				.y = y
			};
			
			elements.push_back(n);
			indl++;
		}
	}
	
	// should be sorted from least to greatest
	// i.e. from 0 to 8
	std::sort(elements.begin(), elements.end(), CompareNums());
}

Sliding_Solver::Sliding_Solver(const std::string& str) {
	// First node
	Board_Tile bt(str);
	tileQueue.push(bt);
}

int Board_Tile::numMoves() {
	return Board_Tile::numOfMoves;
}

std::vector<Board_Tile> Board_Tile::nextConfigs() {
	// Should get 0 tile
	NumPoint blankPoint = elements.at(0);
	
	int initX = blankPoint.x;
	int initY = blankPoint.y;
	
	std::string availableMoves;
	
	// All situations
	if(initX == 0 && initY == 0) { // 0 is at top-left
		availableMoves = "DR"; // Down and Right
	} else if(initX == 1 && initY == 0) { // 0 is top-middle
		availableMoves = "DRL"; // Down, Left, and Right
	} else if(initX == 2 && initY == 0) { // 0 is top-right
		availableMoves = "DL"; // Down and Left
	} else if(initX == 0 && initY == 1) { // 0 is middle-left
		availableMoves = "UDR"; // Up, Down, and Right
	} else if(initX == 2 && initY == 1) { // 0 is middle-right
		availableMoves = "UDL"; // Up, Down, and Left
	} else if(initX == 0 && initY == 2) { // 0 is bottom-left
		availableMoves = "UR"; // Up and Right
	} else if(initX == 1 && initY == 2) { // 0 is bottom-middle
		availableMoves = "URL"; // Up, Left, and Right
	} else if(initX == 2 && initY == 2) { // 0 is bottom-right
		availableMoves = "UL"; // Up and Left
	} else { // 0 is in the middle
		availableMoves = "UDRL"; // unrestricted
	}
	
	// Make all possible moves
	std::vector<Board_Tile> possibleMoves;
	for(int i = 0; i < availableMoves.size(); i++) {
		Board_Tile possibleConfig(getCurrentConfigString());
		possibleConfig.setMoves(numOfMoves, movesFromStart);
		possibleConfig.move(availableMoves.at(i));
		possibleMoves.push_back(possibleConfig);
	}
	
	return possibleMoves;
}

int Board_Tile::Manhattan_Distance(const Board_Tile& goalconfig) {
	std::vector<NumPoint> goalEle = goalconfig.elements;
	int sum = 0;
	
	// Go through all elements of configuration excluding 0
	for(int i = 1; i < 9; i++) {
		NumPoint initN = elements.at(i);
		NumPoint goalN = goalEle.at(i);
		
		sum += (std::abs(initN.x - goalN.x) + std::abs(initN.y - goalN.y));
	}
	
	sum += numMoves();
	
	// Formula is D(C) = A(C) + E(C)
	// in other words
	// Manhattan_Distance = (Moves needed/moves already taken) + (sum of distance of all displaced tiles to their target)
	return sum;
}

// This function will initiate A* Search
bool Sliding_Solver::Solve_Puzzle(Board_Tile goalConfig) {
	bool firstDone = false;
	Board_Tile lastAttempt;
	
	while(tileQueue.empty() == false) {
		Board_Tile config = tileQueue.top();
		lastAttempt = config;
		tileQueue.pop();
		
		if(!firstDone) {
			config.dScore = config.Manhattan_Distance(goalConfig);
			firstDone = true;
		}
		
		if(config == goalConfig) {
			std::cout << "Solution found!!\n";
			std::cout << "Number of moves needed: " << config.numMoves() << std::endl;
			std::cout << "Moves taken: " << config.getMoves() << std::endl;
			
			return true;
		}
		
		int mDistance = config.Manhattan_Distance(goalConfig);
		
		std::vector<Board_Tile> nextConf = config.nextConfigs();
		for(int i = 0; i < nextConf.size(); i++) {
			Board_Tile nextTile = nextConf.at(i);
			int nextMDistance = nextTile.Manhattan_Distance(goalConfig);
			nextTile.dScore = nextMDistance;
			
			if((nextTile.dScore <= config.dScore && Sliding_Solver::excludeRepeat(nextTile))) {
				tileQueue.push(nextTile);
			}
		}
	}
	
	// No solution found
	std::cout << "No Solution found...\n";
	std::cout << "Displaying best attempt\n";
	std::cout << "Number of moves made: " << lastAttempt.numMoves() << std::endl;
	std::cout << "Moves taken: " << lastAttempt.getMoves() << std::endl;
	return false;
}

// Main
int main() {
	std::cout << "Introduction\n";
	std::cout << std::endl;
	
	std::string input = "";
	bool stop = false;
	
	Sliding_Solver ss;
	Board_Tile goalBt;
	
	// First Prompt
	while(!stop) {
		std::cout << "Please enter an initial 3x3 configuration: ";
		std::getline(std::cin, input);
		
		if(input == "Q" || input == "q") {
			stop = true;
			return 0;
		} else {
			Sliding_Solver temp(input);
			ss = temp;
			stop = true;
		}
	}
	
	stop = false;
	
	// Second Prompt
	while(!stop) {
		std::cout << "Please enter a goal 3x3 configuration: ";
		std::getline(std::cin, input);
		
		if(input == "Q" || input == "q") {
			stop = true;
			return 0;
		} else {
			Board_Tile tempBt(input);
			goalBt = tempBt;
			stop = true;
		}
	}
	
	std::cout << "Processing..." << std::endl;
	ss.Solve_Puzzle(goalBt);
	
	return 0;
}

// Extra functions
bool Sliding_Solver::excludeRepeat(Board_Tile config) {
	int configSize = config.getMoves().size();
	
	if(configSize >= 2) {
		char lastMove = config.getMoves().at(configSize - 2);
		char currentMove = config.getMoves().at(configSize - 1);
		
		if(lastMove == 'U' && currentMove == 'D') {
			return false;
		} else if(lastMove == 'R' && currentMove == 'L') {
			return false;
		} else if(lastMove == 'L' && currentMove == 'R') {
			return false;
		} else if(lastMove == 'D' && currentMove == 'U') {
			return false;
		}
	}
	
	return true;
}

void Board_Tile::move(char direction) {
	// Should be the 0 tile
	NumPoint blankPoint = elements.at(0);
	
	int initX = blankPoint.x;
	int initY = blankPoint.y;
	
	int targetX, targetY;
	
	switch (direction){
		case 'u':
		case 'U':
			targetX = initX;
			targetY = initY - 1;
			break;
		case 'd':
		case 'D':
			targetX = initX;
			targetY = initY + 1;
			break;
		case 'r':
		case 'R':
			targetX = initX + 1;
			targetY = initY;
			break;
		case 'l':
		case 'L':
			targetX = initX - 1;
			targetY = initY;
			break;
	}
	
	std::string targetElement = config[targetY][targetX];
	
	// Just in case
	if(targetX < 0) {
		targetX = 0;
	} else if(targetX > 2) {
		targetX = 2;
	}
	
	if(targetY < 0) {
		targetY = 0;
	} else if(targetY > 2) {
		targetY = 2;
	}
	
	// Replace
	config[targetY][targetX] = "0";
	config[initY][initX] = targetElement;
	
	// Re-add to list
	NumPoint zeroN = {
		.num = 0,
		.x = targetX,
		.y = targetY
	};
	
	NumPoint targetN = {
		.num = std::stoi(targetElement),
		.x = initX,
		.y = initY
	};
	
	elements[0] = zeroN;
	elements[std::stoi(targetElement)] = targetN;
	numOfMoves++;
	movesFromStart += direction;
}

std::string Board_Tile::getMoves() {
	return Board_Tile::movesFromStart;
}

std::string Board_Tile::getCurrentConfigString() {
	std::string currentConfig = "";
	
	for(int y = 0; y < 3; y++) {
		for(int x = 0; x < 3; x++) {
			if(x == 2 && y == 2) {
				currentConfig += config[y][x];
			} else {
				currentConfig += config[y][x] + " ";
			}
		}
	}
	
	return currentConfig;
}

void Board_Tile::setMoves(int numM, std::string m) {
	numOfMoves = numM;
	movesFromStart = m;
}

std::vector<std::string> StringMagician::extractInts(const std::string str) {
	std::vector<std::string> results;
	
	std::string newStr = "";
	
	for(int i = 0; i < str.length(); i++) {
		if(std::isdigit(str[i])) {
			newStr += str[i];
		} else {
			results.push_back(newStr);
			newStr = "";
		}
	}
	
	results.push_back(newStr); // Get last string
	
	if(results.size() != 9) {
		std::cout << results.size() << std::endl;
		throw NotConfig();
	}
	
	return results;
}

void StringMagician::printAll(std::vector<std::string> aList) {
	for(int i = 0; i < aList.size(); i++) {
		std::cout << aList[i] << std::endl;
	}
}