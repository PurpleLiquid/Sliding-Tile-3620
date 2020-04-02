#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <queue>
#include <cstdlib>
#include <bits/stdc++.h>
#include "AStarSolver.h"

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
			
			elementQueue.push(n);
			indl++;
		}
	}
}

int Board_Tile::Manhattan_Distance(const Board_Tile& goalconfig) {
	std::priority_queue<NumPoint, std::vector<NumPoint>, CompareNums> goalEle = goalconfig.elementQueue;
	int sum = 0;
	
	for(int i = 1; i < 9; i++) {
		NumPoint initN = Board_Tile::elementQueue.top();
		Board_Tile::elementQueue.pop();
		NumPoint goalN = goalEle.top();
		goalEle.pop();
		
		sum += (std::abs(initN.x - goalN.x) + std::abs(initN.y - goalN.y));
		
		std::cout << goalN.num << " " << (std::abs(initN.x - goalN.x) + std::abs(initN.y - goalN.y)) << std::endl;
	}
	
	// Formula is D(C) = A(C) + E(C)
	// in other words
	// Manhattan_Distance = 0 + sum of distance of all displaced tiles to their target
	return sum;
}

int main() {
	std::cout << "Introduction\n";
	std::cout << std::endl;
	
	std::string input = "";
	bool stop = false;
	
	Board_Tile initBt;
	Board_Tile goalBt;
	
	// First Prompt
	while(!stop) {
		std::cout << "Please enter an initial 3x3 configuration: ";
		std::getline(std::cin, input);
		
		if(input == "Q" || input == "q") {
			stop = true;
			return 0;
		} else {
			Board_Tile tempBt(input);
			initBt = tempBt;
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
	initBt.Manhattan_Distance(goalBt);
	
	return 0;
}