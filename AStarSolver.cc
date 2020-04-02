#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
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
	return results;
}

void StringMagician::printAll(std::vector<std::string> aList) {
	for(int i = 0; i < aList.size(); i++) {
		std::cout << aList[i] << std::endl;
	}
}

void BinaryHeap::insert(std::string str) {
	if(BinaryHeap::currentSize == BinaryHeap::heap.size() - 1) {
		BinaryHeap::heap.resize(BinaryHeap::heap.size() * 2);
	}
	
	// Percolate Up
	int hole = BinaryHeap::currentSize++;
	std::string temp = "";
	std::string copy = str;
	BinaryHeap::heap.push_back(copy);
	
	for(; std::stoi(str) < std::stoi(BinaryHeap::heap[hole/2]); hole /= 2) {
		temp = BinaryHeap::heap[hole/2];
		BinaryHeap::heap[hole/2] = BinaryHeap::heap[hole];
		BinaryHeap::heap[hole] = temp;
	}
}

void BinaryHeap::printAll() {
	for(int i = 0; i < BinaryHeap::heap.size(); i++) {
		std::cout << BinaryHeap::heap[i] << std::endl;
	}
}

Board_Tile::Board_Tile(const std::string& str) {
	StringMagician sm;
	
	std::vector<std::string> ints = sm.extractInts(str);
	int indl = 0;
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			Board_Tile::config[i][j] = ints[indl];
			indl++;
		}
	}
}

int main() {
	std::cout << "Introduction\n";
	std::cout << std::endl;
	
	std::string input = "";
	bool stop = false;
	
	std::vector<std::string> test;
	
	while(!stop) {
		std::cout << "Please enter a 3x3 configuration: ";
		std::getline(std::cin, input);
		
		if(input == "Q" || input == "q") {
			stop = true;
			return 0;
		} else if(input == "print" || input == "PRINT" || input == "Print") {
			// For testing purposes
			// bh.printAll();
		} else {
			Board_Tile bt(input);
		}
	}
	
	return 0;
}