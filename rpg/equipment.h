#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <vector>
#include "gear.h"
class Equipment;

class Equipment {
public:
	std::vector<Gear> loadOut;
	std::vector<std::string> sEquip{ "Head","Chest","Gloves","Boots", "Ring","Trinket" };
	std::vector<bool>bEquip;
	std::string equipString;

	Equipment(std::vector<Gear> loadOut);
	void equipArmour(Gear piece, character& hero, ArmInv& bag);
	int returnSlot(Gear piece);
	operator const char*();
};

#endif