#include<iostream>
#include "listD.h"
#include <array>

int main(int argc, char* argv) {
	std::array<int, 3> bbb;
	auto iter = bbb.begin();

	DoublLinkedList<int> arr;

	arr.push_back(1);

	arr.push_back(3);

	arr.push_back(7); 
	
	arr.push_back(4);
	
	arr.push_back(10);
	arr.Print();
	std::cout << "\n";
	
	arr.fill(5, 3);
	arr.Print();
	
	
	return 0;
}