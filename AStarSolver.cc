#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include "AStarSolver.h"

std::vector<std::string> StringMagician::extractInts(std::string str) {
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
	
	results.push_back(newStr); // Get last
	return results;
}

void StringMagician::printAll(std::vector<std::string> aList) {
	for(int i = 0; i < aList.size(); i++) {
		std::cout << aList[i] << std::endl;
	}
}

int main() {
	std::cout << "Introduction\n";
	std::cout << std::endl;
	
	std::string input = "";
	bool stop = false;
	
	StringMagician sm;
	std::vector<std::string> test;
	
	while(!stop) {
		std::cout << "Please enter a 3x3 configuration: ";
		std::getline(std::cin, input);
		
		if(input == "Q" || input == "q") {
			stop = true;
			return 0;
		} else if(input == "print" || input == "PRINT" || input == "Print") {
			// For testing purposes
			sm.printAll(test);
		} else {
			test = sm.extractInts(input);
		}
	}
	
	return 0;
}