#ifndef ITEMS_H
#define ITEMS_H
#include <string>
#include "character.h"
class Item {
public:
	int ieffect;
	std::string name, stat, type, itemString;
	Item();
	Item(std::string n);
	Item(std::string name, int ieffect, std::string type);
	void effect(character& hero);
	operator const char*();
};
#endif

