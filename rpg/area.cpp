#include "area.h"
#include <ctime>

//Shop objects

	Shop::Shop(std::string n, std::vector<Item> w, std::vector<int> p) {
		waresItems = w;
		name = n;
		prices = p;
		type = "shop";
		typeSwitch = 0;
		for (int i = 0; i < size(waresItems);i++) {
			wareNames.push_back(waresItems[i].name);
		}
		wareNames.push_back("Leave");
	}
	Shop::Shop(std::string n, std::vector<Gear> w, std::vector<int> p) {
		name = n;
		waresGear = w;
		prices = p;
		type = "shop";
		typeSwitch = 1;
		for (int i = 0; i < size(waresGear);i++) {
			wareNames.push_back(waresGear[i].name);
		}
		wareNames.push_back("Leave");
	}
	Shop::Shop(std::string n, std::vector<Weapon> w, std::vector<int> p) {
		name = n;
		waresWeapon = w;
		prices = p;
		type = "shop";
		typeSwitch = 2;
		for (int i = 0; i < size(waresWeapon);i++) {
			wareNames.push_back(waresWeapon[i].name);
		}
		wareNames.push_back("Leave");
	}
	Shop::Shop(std::string n,int cost) {
		name = n;
		prices = { cost };
		type = "inn";
	};
	void Shop::enterTemple(character& hero) {
		std::vector<std::string> yn{ "Yes", "No" };
		std::cout << "Pay " << prices[0] << "gold and restore health and mana?\n";
		int choice = getChoice(yn);
		switch (choice) {
		case 0:
			if (hero.gold < prices[0]) {
				std::cout << "Not enough gold.\n";
			}
			else{
				hero.gold -= prices[0];
				hero.hp = hero.maxHp;
				hero.mana = hero.maxMana;
				std::cout << "You have been fully restored.\n";
			}
			
		case 1:
			std::cout << "Farewell.\n";
			break;
		}
	}
	void Shop::enterShop(character& hero, Inventory& bag, ArmInv& bag2, WeaponInv& bag3) {
	menu2:
		std::cout << "Welcome to the " << name << " shop.\n";
		int choice1 = getChoice(wareNames);
		if (choice1 == size(wareNames) - 1) {
		leave:
			std::cout << "Farewell!\n";
		}
		else {
			std::vector<std::string> yn{ "Yes","No" };
			int amount;
			std::cout << "Purchase amount: ";
			std::cin >> amount;
			std::cout << "Purchase " << wareNames[choice1] << " x"  << amount <<" for " << prices[choice1] * amount << "?\n";
			int choice2 = getChoice(yn);
			switch (choice2) {
			case 0:
				if (hero.gold < (prices[choice1]*amount)) {
					std::cout << "Not enough gold.\n";
				}
				else {
					hero.gold -= prices[choice1] * amount;
					if (typeSwitch == 0) {
						bag.addToInventory(waresItems[choice1], amount);
					}
					else if (typeSwitch == 1) {
						bag2.addToInventory(waresGear[choice1], amount);
					}
					else if (typeSwitch == 2) {
						bag3.addToInventory(waresWeapon[choice1], amount);
					}
				}
				std::cout << "Anything else?\n";
				choice2 = getChoice(yn);
				switch (choice2) {
				case 0:
					goto menu2;
				case 1:
					goto leave;
				}
			case 1:
				goto menu2;
			}
		}
	}


//Area objects
	Area::Area(std::string name,std::vector<Shop> s) {
		this->name = name;
		this->shops = s;
		type = "City";
		choices[0] = "Shops";
		for (int i = 0; i < size(shops); i++) {
			shopList.push_back(shops[i].name);
		}
		shopList.push_back("Back");
	};
	Area::Area(std::string name, std::vector<std::vector<character>> encounters, std::vector<int> encounterRates) {
		this->name = name;
		this->encounters = encounters;
		this->encounterRates = encounterRates;
		type = "Wilds";
	};
	void Area::getAreaDescription(std::string description) {
		this->description = description;
	}
	void Area::getAreaDirections(std::string dir1) {
		choices.push_back(dir1);
	};
	void Area::getAreaDirections(std::string dir1, std::string dir2) {
		choices.push_back(dir1);
		choices.push_back(dir2);
	}
	void Area::enterArea() {
		std::cout << "\n";
		std::cout << "\n" << name << "\n"
			<< "____________________\n"
			<< description << "\n";
	}
	std::vector<character> Area::getEncounter() {
		std::vector<character> enemyList;
		srand(time(NULL));
		int x = rand() % 100 + 1;
		if (x <= encounterRates[0]) {
			enemyList = encounters[0];
		}
		else {
			for (int i = 1; i < size(encounters);i++) {
				if (i == size(encounters) - 1) { enemyList = encounters[i]; break; }
				else {
					if ((x <= encounterRates[i] + encounterRates[i + 1]) and x >(encounterRates[i - 1])) {
						enemyList = encounters[i];
						break;
					}
				}
			}
		}
		return enemyList;
	};
	bool Area::checkEncounter(character& hero, Inventory& bag, std::vector<magic>& spellbook) {
		srand(time(NULL) - hero.hp);
		int x = rand() % 100 + 1;
		if (x <= 25) {
			std::vector<character> y = getEncounter();
			std::vector<character*> z;
			std::cout << "Ambushed!\n";
			for (int i = 0; i < size(y);i++) {
				z.push_back(&y[i]);
				std::cout << y[i].name << " has appeared.\n";
			}
			battleSystem(hero, z, bag, spellbook);
			return true;
		}
		else { return false; }
	}
//area non-object functions
void checkDirection(std::string dir, int& x, int& y) {
	if (dir == "Go east") { x++; }
	else if (dir == "Go west") { x--; }
	else if (dir == "Go north") { y++; }
	else if (dir == "Go south") { y--; }
	else { std::cout << "Error: Direction not found.\n"; }
}
void areaManager(Area zone, int& x, int& y, character& hero, Inventory& bag, ArmInv& bag2,WeaponInv& bag3 ,std::vector<magic>& spellbook, bool& gameOver) {
	std::string j;
menu:
	zone.enterArea();
	int choice = getChoice(zone.choices);
	switch (choice) {
	case 0:
		if (zone.type == "Wilds") {
			if (zone.checkEncounter(hero, bag, spellbook) == false) { std::cout << "\nNothing happened.\n"; };
			goto menu;
		}
		else if (zone.type == "City") {
			int choice2 = getChoice(zone.shopList);
			if (choice2 == size(zone.shopList) - 1) {
				goto menu;
			}
			else {
				if (zone.shops[choice2].type == "shop") {
					zone.shops[choice2].enterShop(hero, bag, bag2, bag3);
					goto menu;
				}
				else {
					zone.shops[choice2].enterTemple(hero);
					goto menu;
				}
				

			}
		}
	case 1:
		std::cout << "\n" << bag << "\n";
		getline(std::cin, j);
		goto menu;
	case 2:
		std::cout << "\n";
		for (int i = 0; i < size(spellbook);i++) {
			std::cout <<  spellbook[i].name << "\n";
		}
		getline(std::cin, j);
		goto menu;
	case 3:
		std::cout << "\n" << hero << "\n";
		getline(std::cin, j);
		goto menu;
	case 4:
		gameOver = true;
		break;
	case 5:
		if (zone.type == "Wilds") {
			zone.checkEncounter(hero, bag, spellbook);
		}
		checkDirection(zone.choices[choice], x, y);
		break;
	case 6:
		if (zone.type == "Wilds") {
			zone.checkEncounter(hero, bag, spellbook);
		}
		checkDirection(zone.choices[choice], x, y);
		break;
	case 7:
		if (zone.type == "Wilds") {
			zone.checkEncounter(hero, bag, spellbook);
		}
		checkDirection(zone.choices[choice], x, y);
		break;
	case 8:
		if (zone.type == "Wilds") {
			zone.checkEncounter(hero, bag, spellbook);
		}
		checkDirection(zone.choices[choice], x, y);
		break;
	};
}
Area fetchArea(std::string name, std::vector<Area> myVec) {
	for (int i = 0; i < size(myVec);i++) {
		if (myVec[i].name == name) {
			return myVec[i];
			break;
		}
	}
}