#include <iostream>
#include <string>
#include <sstream>
#include "character.h"



	character::character() {
		level = 1;
		exp = 0;
		toNextLvl = 300;
		charClass = "Adventurer";
		istats.assign(5, 0);
	}
	character::character(std::string name) {
		this->name = name;
		level = 1;
		exp = 0;
		istats.assign(5, 0);
		statRaises.assign(5, 0);
		statDecrease.assign(5, 0);
		charClass = "Adventurer";
		toNextLvl = 300;
		istats[0] = 12 + level;
		istats[1] = 10 + level;
		istats[2] = 12 + level;
		istats[3] = 11 + level;
		istats[4] = 10 + level;
		maxHp = 100 + ((istats[2] * 2)*level);
		hp = maxHp;
	};
	character::character(std::string name, std::string charClass, int level, int gold) {
		this->name = name;
		this->level = level;
		this->charClass = charClass;
		this->gold = gold;
		istats.assign(5, 0);
		statRaises.assign(5, 0);
		statDecrease.assign(5, 0);
		exp = 0;
		expGain = 300;
		armour = 0;
		crit = 10;
		istats[0] = 12;
		istats[1] = 10;
		istats[2] = 12;
		istats[3] = 11;
		istats[4] = 10;
		baseHp = 100;
		baseMp = 20;
		armourRest = { "" };
		weaponRest = { "" };
		if (charClass == "Warrior") {
			statCurve = {2,1,2,0,0};
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
			
		}
		else if (charClass == "Mage") {
			statCurve = {1,0,1,3,0};
			baseMp = 40;
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
			armourRest = {"Heavy","Medium"};
			weaponRest = {"Sword","Axe","Spear","Mace"};
		}
		else if (charClass == "Priest") {
			statCurve = { 2,0,1,0,2 };
			baseHp = 120;
			baseMp = 40;
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
			armourRest = {"Heavy"};
		}
		else if (charClass == "Thief") {
			baseHp = 70;
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			statCurve = { 2,2,0,0,0 };
			crit += 0.5 * level;
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
			armourRest = {"Heavy"};
			weaponRest = {"Axe","Mace","Spear"};
		}
		else if (charClass == "Onion Knight") {
			baseHp = 120;
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			statCurve = { 2,1,3,1,1 };
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
		}
		else if (charClass == "Berserker") {
			baseHp = 70;
			baseHp += baseHp * 0.05 * level;
			baseMp += baseMp * 0.10 * level;
			statCurve = { 4,3,0,0,0 };
			crit += 0.5 * level;
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
			armourRest = {"Heavy","Medium","Light"};
			weaponRest = {"Shield"};
		}
		else if (charClass == "Black Mage") {
			baseHp = 100;
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			statCurve = { 0,0,0,7,0 };
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
			armourRest = {"Heavy","Medium"};
		}
		else {
			baseHp = 100;
			baseHp += baseHp * 0.10 * level;
			baseMp += baseMp * 0.10 * level;
			statCurve = { 1,1,1,1,1 };
			for (int i = 0; i < size(istats);i++) {
				istats[i] += statCurve[i] * level;
			}
		};
		attackMin = istats[0]/2 + (istats[1])*0.2;
		attackMax =  istats[0];
		maxHp =baseHp + (istats[2] * 2);
		maxMana = baseMp + (istats[3] * 2);
		hp = maxHp;
		mana = maxMana;
		toNextLvl = 300 * level;
	};
	character::character(std::string name, int maxHp, int expGain,int goldGain ,int str, int dex, int con, int intel, int wisd) {

		charClass = "Monster";
		istats.assign(5, 0);
		statRaises.assign(5, 0);
		statDecrease.assign(5, 0);
		armour = 0;
		crit = 10;
		this->name = name;
		this->maxHp = maxHp;
		this->expGain = expGain;
		gold = goldGain;
		this->istats[0] = str;
		this->istats[1] = dex;
		this->istats[2] = con;
		this->istats[3] = intel;
		this->istats[4] = wisd;
		attackMin = istats[0] + (istats[1])*0.2;
		attackMax = 2 * istats[0];
		hp = maxHp;

	};
	void character::checkBuffs() {
		if (buffed == true) {
			buffCounter--;
			if (buffCounter == 0) {
				for (int i = 0; i < size(statRaises);i++) {
					istats[i] -= statRaises[i];
					statRaises[i] = 0;
				}
				std::cout << "Enhancement has worn off.\n";
				buffed = false;
			}
		}
	}
	void character::checkDebuffs() {
		if (debuffed == true) {
			debuffCounter--;
			if (debuffCounter == 0) {
				for (int i = 0; i < size(statDecrease);i++) {
					istats[i] += statDecrease[i];
					statDecrease[i] = 0;
				}
				std::cout << "Debuff has worn off.\n";
				debuffed = false;
			}
		}
	}
	void character::refreshStats() {
		if (attackMin > attackMax) { attackMin = attackMax; };
		maxHp = baseHp + (istats[2] * 2);
		maxMana = baseMp + (istats[3] * 2);
	}
	void character::levelUp() {
		for (int i = 0; i < size(istats);i++) {
			istats[i] += statCurve[i];
		}
		if (charClass == "Thief") {
			crit += 0.5;
		}
		//attackMin += istats[0];
		//attackMax = 2 * istats[0];
		baseHp += int(baseHp*0.10);
		baseMp += int(baseMp*0.10);
		refreshStats();
		hp = maxHp;
		mana = maxMana;
		exp = exp - toNextLvl;
		toNextLvl = 2 * toNextLvl;
	}
	
	character::operator const char*() {
		std::ostringstream charStream;
		charStream << "Name: " << name << "\n" <<
			"Level: " << level << "\n"
			<< "Class: " << charClass << "\n"
			<< "HP " << hp << "/" << maxHp << "\n"
			<< "MP " << mana << "/" << maxMana << "\n"
			<< "Attack: " << int(attackMin + (istats[1]*0.2))<< "-"<< int(attackMax + (istats[0]*0.2))<<"\n"
			<< "Armour: " << armour << "\n" 
			<< "Crit. Chance: " << crit + (0.2*istats[1])  << "%\n"
			<< "Strength " << istats[0] << "\n"
			<< "Dexterity " << istats[1] << "\n"
			<< "Constitution " << istats[2] << "\n"
			<< "Intelligence " << istats[3] << "\n"
			<< "Wisdom " << istats[4] << "\n"
			<< "Gold " << gold << "\n"
			<< "EXP: " << exp << "/" << toNextLvl << "\n";
		charString = charStream.str();
		return charString.c_str();
	}