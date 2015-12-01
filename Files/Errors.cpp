#include "Errors.h"

#include<iostream>
#include <SDL\SDL.h>

void fatalError(std::string errrorString){
	std::cout << errrorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	exit(1);

}