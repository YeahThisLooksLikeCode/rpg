#include <iostream>
#include <string>
#include "choiceUI.h"
#include <conio.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER int(' ')

void printOut(std::vector<std::string> choiceList, int x) {
	std::string sArrw{ "->" };
	std::cout << "\nPress space bar to confirm.\n";
	for (int i = 0; i < size(choiceList);i++) {
		if (x == i) {
			std::cout << sArrw << " " << i + 1<< "-"<<choiceList[x] << "\n";
		}
		else {
			std::cout << i + 1 << "-" << choiceList[i] << "\n";
		};
	}
};

int getChoice(std::vector<std::string> choiceList) {
	int x = 0;
	int c = 0;
	printOut(choiceList, x);
	while (1) {

		switch (c = _getch()) {
		case KEY_UP:
			x--;
			if (x < 0) {
				x = size(choiceList) - 1;
			};
			printOut(choiceList, x);
			break;
		case KEY_DOWN:
			x++;
			if (x > size(choiceList) - 1) {
				x = 0;
			};
			printOut(choiceList, x);
			break;
		case KEY_RIGHT:
			x++;
			if (x > size(choiceList) - 1) {
				x = 0;
			};
			printOut(choiceList, x);
			break;
		case KEY_LEFT:
			x--;
			if (x < 0) {
				x = size(choiceList) - 1;
			};
			printOut(choiceList, x);
			break;
		case ENTER:
			return x;
		};
		//printOut(choiceList,x);
	};//end while
	  //return choiceList[x];
};