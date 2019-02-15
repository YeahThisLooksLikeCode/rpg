#ifndef AREA_H
#define AREA_H

#include <iostream>
#include <vector>
#include <string>
#include "character.h"
#include "inventory.h"
#include "magic.h"
#include "battle.h"
#include "choiceUI.h"
#include "arminv.h"
#include "gear.h"
#include "weapon.h"
//shop object
class Shop {
public:
	std::vector<Item> waresItems;
	std::vector<Gear> waresGear;
	std::vector<Weapon> waresWeapon;
	std::vector<std::string> wareNames;
	std::vector<int> prices;
	std::string name, type;
	int typeSwitch;
	Shop(std::string n, std::vector<Item> w, std::vector<int> p);
	Shop(std::string n, std::vector<Gear> w, std::vector<int> p);
	Shop(std::string n, std::vector<Weapon> w, std::vector<int> p);
	Shop(std::string n,int cost);
	void enterTemple(character& hero);
	void enterShop(character& hero, Inventory& bag, ArmInv& bag2, WeaponInv& bag3);
};


//Area object
class Area {
public:
	bool localSwitchA, localSwitchB, localSwitchC;
	std::string name, description, type;
	std::vector<Shop> shops;
	std::vector<int> encounterRates;
	std::vector<std::vector<character>> encounters;
	std::vector<std::string> shopList;
	std::vector<std::string> choices{ "Walk around", "Inventory", "Spellbook", "Stats","Back"};
	Area(std::string name,std::vector<Shop> shops);
	Area(std::string name, std::vector<std::vector<character>> encounters, std::vector<int> encounterRates);
	void getAreaDescription(std::string description);
	void getAreaDirections(std::string dir1);
	void getAreaDirections(std::string dir1, std::string dir2);
	void enterArea();
	std::vector<character> getEncounter();
	bool checkEncounter(character& hero, Inventory& bag, std::vector<magic>& spellbook);
};

//Area functions
void checkDirection(std::string dir, int& x, int& y);
void areaManager(Area zone, int& x, int& y, character& hero, Inventory& bag, ArmInv& bag2,WeaponInv& bag3 ,std::vector<magic>& spellbook, bool& gameOver);
Area fetchArea(std::string name, std::vector<Area> myVec);
#endif
