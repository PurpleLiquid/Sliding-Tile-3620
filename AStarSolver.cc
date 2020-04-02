#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <queue>
#include <algorithm>
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
			
			elements.push_back(n);
			indl++;
		}
	}
	
	std::sort(elements.begin(), elements.end(), CompareNums());
}

/*void Board_Tile::move(char direction) {
	// Should be zero
	NumPoint blankPoint = elementQueue.top();
	elementQueue.pop();
	
	int initX = blankPoint.x;
	int initY = blankPoint.y;
	
	int targetX, targetY;
	
	switch (direction){
		case 'u':
			targetX = initX;
			targetY = inity - 1;
			break;
		case 'd':
			targetX = initX;
			targetY = inity + 1;
			break;
		case 'r':
			targetX = initX + 1;
			targetY = inity;
			break;
		case 'l':
			targetX = initX - 1;
			targetY = inity;
			break;
	}
	
	std::string targetElement = config[targetX][targetY];
	
	config[targetX][targetY] = "0";
	config[initX][initY] = targetElement;
	
	// Re-add to priority_queue
	NumPoint n = {
		.x = targetX,
		.y = targetY
	};
	
	elementQueue.push(n);
}*/

int Board_Tile::Manhattan_Distance(const Board_Tile& goalconfig) {
	std::vector<NumPoint> goalEle = goalconfig.elements;
	int sum = 0;
	
	for(int i = 1; i < 9; i++) {
		NumPoint initN = elements.at(i);
		NumPoint goalN = goalEle.at(i);
		
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
	std::cout << "Sum: " << initBt.Manhattan_Distance(goalBt) << std::endl;
	
	return 0;
}