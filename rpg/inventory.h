#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include "items.h"

class Inventory {
public:
	std::vector<std::string> sInv;
	std::vector<Item> Inv;
	std::vector<int> iInv;
	std::string invString;

	Inventory();
	void addToInventory(Item obj, int amount);
	void removeFromInventory(Item obj, int amount);
	void useItem(Item obj,character& hero);
	operator const char*();
};
#endif
