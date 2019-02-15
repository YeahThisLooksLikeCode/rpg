#ifndef WEAPON_H
#define WEAPON_H

#include <vector>
#include "character.h"
class Weapon {
public:
	int attack, attackMax,attackMin,crit,armour;
	std::vector<int> istats;
	std::vector<std::string> sstats{ "strength","dexterity","constitution","intelligence","wisdom" };
	std::string wtype;
	std::string slot;
	std::string name;
	std::string weaponString;

	Weapon();
	Weapon(std::string name, int armour, std::string slot);;
	Weapon(std::string name, int attack,int crit, std::string wtype, std::string slot);
	void addStats(std::string stat, int n);
	operator const char*();
};

class WeaponInv {
public:
	std::vector<Weapon> Inv;
	std::vector<int> iInv;
	std::vector<std::string> sInv;
	std::string weaponString;

	WeaponInv();
	void addToInventory(Weapon obj, int amount);
	void removeFromInventory(Weapon obj, int amount);
	operator const char*();
};

class WeapEquip {
public:
	std::vector<Weapon> loadOut;
	std::vector<std::string> sEquip{ "Right Hand" , "Left Hand" };
	std::vector<bool>bEquip;
	std::string equipString;
	WeapEquip();
	WeapEquip(std::vector<Weapon> loadOut);
	void equipWeapon(Weapon piece, character& hero, WeaponInv& bag);
	int returnSlot(Weapon piece);;
	operator const char*();
};

#endif