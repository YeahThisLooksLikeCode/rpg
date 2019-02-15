#include "magic.h"
#include <iostream>



	magic::magic() {}
	magic::magic(std::string name, int ieffect, int cost, std::string type) {
		this->name = name;
		this->ieffect = ieffect;
		this->cost = cost;
		this->type = type;
	}
	magic::magic(std::string name, int ieffect, int cost, int index, int counter, std::string type) {
		this->name = name;
		this->cost = cost;
		this->type = type;
		this->counter = counter;
		this->index = index;
		statRaise.assign(5,0);
		statRaise[index] = ieffect;
	}
	magic::magic(std::string name, int ieffect, int cost, std::string status,std::string type) {
		this->name = name;
		this->ieffect = ieffect;
		this->cost = cost;
		this->type = type;
		this->status = status;
	};
	void magic::dealDamage(character& hero, character& enemy) {
		hero.mana -= cost;
		int damage = ieffect + int(0.2*hero.istats[3]);
		enemy.hp -= damage;
		if (enemy.hp < 0) { enemy.hp = 0; };
		std::cout << hero.name <<" casts " << name << " for "<< damage <<" damage.\n";
		std::cout << enemy.name << " has " << enemy.hp <<" HP left.\n";
		std::cout << hero.name << " has " << hero.mana << " MP left.\n";
	}
	void magic::healDamage(character& hero) {
		hero.mana -= cost;
		hero.hp += ieffect;
		if (hero.hp > hero.maxHp) { hero.hp = hero.maxHp; }
		std::cout << hero.name << " cast " << name << " and healed for " << ieffect << " HP.\n";
		std::cout << hero.mana <<" MP remaining.\n";
	}
	void magic::applyStatus(character& hero, character& enemy) {
		hero.mana -= cost;
		enemy.status = status;
		enemy.statCounter = ieffect;
		std::cout << enemy.name << " has been afflicted with " << status << ".\n";
	}
	void magic::applyBuff(character& hero) {
		hero.mana -= cost;
		std::cout << hero.name << " cast " << name << ".\n";
		if (hero.buffed == true) {
			hero.buffCounter = 0;
			hero.checkBuffs();
		}
		hero.buffed = true;
		hero.buffCounter = counter;
		for (int i = 0; i < size(statRaise);i++) {
			hero.istats[i] += statRaise[i];
			hero.statRaises[i] = statRaise[i];
		}
	}
	void magic::applyDebuff(character& hero, character& enemy) {
		hero.mana -= cost;
		std::cout << hero.name << " cast " << name << ".\n";
		if (enemy.debuffed == true) {
			enemy.debuffCounter = 0;
			enemy.checkDebuffs();
		}
		enemy.debuffed = true;
		enemy.debuffCounter = counter;
		for (int i = 0; i < size(enemy.statDecrease);i++) {
			enemy.istats[i] -= statRaise[i];
			enemy.statDecrease[i] = statRaise[i];
		}
	}
	void magic::useSpell(character& hero, character& enemy) {
		if (cost > hero.mana) {
			std::cout << "Not enough mana.\n";
		}
		else {
			if (type == "heal") {
				healDamage(hero);
			}
			else if (type == "damage") {
				dealDamage(hero, enemy);
			}
			else if (type == "status") {
				applyStatus(hero, enemy);
			}
			else if (type == "buff") {
				applyBuff(hero);
			}
			else if (type == "debuff") {
				applyDebuff(hero, enemy);
			}
		}

	}
