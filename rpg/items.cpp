#include "items.h"
#include "character.h"
#include <sstream>
#include <iostream>

	Item::Item() {
	}
	Item::Item(std::string n) {
		name = n;
		type = "key";
	};
	Item::Item(std::string name, int ieffect, std::string type) {
		this->name = name;
		this->ieffect = ieffect;
		this->type = type;
	}
	void Item::effect(character& hero) {
		if (type == "health") {
			hero.hp += ieffect;
			std::cout << hero.name << " healed for " << ieffect << "HP.\n";
			if (hero.hp > hero.maxHp) {
				hero.hp = hero.maxHp;
			};
		}
		else if (type == "mana") {
			hero.mana += ieffect;
			std::cout << hero.name << " restored " << ieffect << " mana.\n";
			if (hero.mana > hero.maxMana) {
				hero.mana = hero.maxMana;
			};
		}
		else { std::cout << "You can not use that at this time.\n"; }

	};
	Item::operator const char*() {
		std::ostringstream itemStream;
		if (type == "key") {
			itemStream << "It's a key. It opens stuff.\n";
		}
		else {
			itemStream << "Restores " << ieffect << " " << type << ".\n";
		}

		itemString = itemStream.str();
		return itemString.c_str();
	};

