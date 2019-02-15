#ifndef MAGIC_H
#define MAGIC_H

#include "character.h"
#include <string>
#include <iostream>

class magic {
public:
	std::string name;
	std::string type, status;
	int ieffect, cost, counter, index;
	std::vector<int> statRaise;
	magic();
	magic(std::string name, int ieffect, int cost, std::string type);
	magic(std::string name, int ieffect, int cost, int index, int counter, std::string type);
	magic(std::string name, int ieffect, int cost, std::string status, std::string type);
	void dealDamage(character& hero, character& enemy);
	void healDamage(character& hero);
	void applyStatus(character& hero, character& enemy);
	void applyBuff(character& hero);
	void applyDebuff(character& hero, character& enemy);
	void useSpell(character& hero, character& enemy);
};
#endif
