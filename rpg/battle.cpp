#include <iostream>
#include <sstream>
#include <ctime>
#include "character.h"
#include "choiceUI.h"
#include "items.h"
#include "battle.h"
#include "magobj.h"
//#include "magic.h"
//#include "inventory.h"
void checkLvlUp(character& hero,std::vector<magic>& spellbook) {
	if (hero.exp >= hero.toNextLvl) {
		hero.level++;
		hero.levelUp();
		std::cout << hero.name <<" has leveled up! " << hero.name <<" is now level "<< hero.level <<".\n";
		if (hero.charClass == "Mage" or hero.charClass == "Black Mage") {
			std::vector<std::string> abCurve{ "Combustion","Poison","Inferno","Enhance Intelligence" ,"Sleep","Mark of Enfeeblement" };
			std::vector<int> levelCurve{ 5,3,9,7,7,5 };
			for (int i = 0; i < size(levelCurve);i++) {
				if (hero.level == levelCurve[i]) {
					spellbook.push_back(returnMagic(abCurve[i]));
					std::cout << hero.name << " has learned " << abCurve[i] << "\n";
				}
			}
		}
		else if (hero.charClass == "Priest") {
			std::vector<std::string> abCurve{ "Heal Light Wounds","Heal Medium Wounds","Heal Grave Wounds","Enhance Strength" };
			std::vector<int> levelCurve{ 3,7,9,5 };
			for (int i = 0; i < size(levelCurve);i++) {
				if (hero.level == levelCurve[i]) {
					spellbook.push_back(returnMagic(abCurve[i]));
					std::cout << hero.name << " has learned " << abCurve[i] << "\n";
				}
			}
		}
	}

}
bool checkCrit(character& attacker) {
	srand(time(NULL) + attacker.maxHp);
	int num = rand() % 100 + 1;
	if (num <= (attacker.crit + (0.2*attacker.istats[1]))) {
		return true;
	}
	else { return false; }
}
void getDamage(character& attacker, character& defender) {
	srand(time(NULL) + attacker.hp);
	int damage;
	if (checkCrit(attacker) == true) {
		damage =( attacker.attackMax + int(0.5*attacker.attackMax)) - defender.armour;
		std::cout << "Critical hit! ";
	}
	else {
		int max = attacker.attackMax + (attacker.istats[0] * 0.2);
		int min = attacker.attackMin + (attacker.istats[1] * 0.2);
		damage = (rand() % max / 2) + min - defender.armour;
	}
	if (damage < 0) { damage = 0; }
	defender.hp -=  damage;
	if (defender.hp < 0) {
		defender.hp = 0;
	};
	std::cout << attacker.name << " attacks for " << damage << " damage.\n";
	std::cout << defender.name << " has " << defender.hp << " HP left.\n";

}
void checkWin(std::vector<character*> enemyList, bool& win) {
	for (int i = 0; i < size(enemyList);i++) {
		character a = *(enemyList[i]);
		if (a.hp != 0) {
			win = false;
			break;
		}
		else if (a.hp == 0 and i == (size(enemyList)-1)) {
			restoreAll(*enemyList[i]);
			std::cout << a.name << " has been defeated.\n";
			win = true;
		}
	}
}
void getPlayerAction(character& hero, std::vector<character*> enemyList, bool& run, Inventory& bag, std::vector<magic> spellbook) {
	std::vector<std::string> a{ "Attack","Item","Magic","Run" };
	std::vector<std::string> b;
	for (int i = 0; i < size(enemyList);i++) {
		character a = *(enemyList[i]);;
		b.push_back(a.name);
	};
	b.push_back("Back");
menu:
	int choice = getChoice(a);
	while (1) {
		if (a[choice] == "Attack") {
			choice = getChoice(b);
			if (choice == (size(b) - 1)) {
				goto menu;
			}
			else {
				getDamage(hero, *enemyList[choice]);
			}
			break;
		}
		else if (a[choice] == "Item") {
			if (size(bag.sInv) == 0) { 
				std::cout << "Inventory is empty.\n"; 
				goto menu;
			}
			else {
				bag.sInv.push_back("Back");
				choice = getChoice(bag.sInv);
				if (choice == (size(bag.sInv) - 1)) {
					bag.sInv.erase(bag.sInv.end()-1);
					goto menu;
				}
				else {
					bag.useItem(bag.Inv[choice], hero);
					bag.sInv.erase(bag.sInv.end() - 1);

					break;
				}
				
			}
			break;
		}
		else if (a[choice] == "Magic") {
			std::vector<std::string> sSpell;
			for (int i = 0; i < size(spellbook);i++) {
				sSpell.push_back(spellbook[i].name);
			}
			sSpell.push_back("Back");
			choice = getChoice(sSpell);
			if (choice == (size(sSpell) - 1)) {
				goto menu;
			}
			else {
				if (spellbook[choice].type == "heal" or spellbook[choice].type == "buff") {
					spellbook[choice].useSpell(hero, *enemyList[0]);
				}
				else {
					int choice2 = getChoice(b);
					spellbook[choice].useSpell(hero, *enemyList[choice2]);
					break;
				}
			}
			
			break;
		}
		else if (a[choice] == "Run") {
			run = true;
			break;
		}
		else { std::cout << "Input not recognized.\n"; }
	};
}
void battleSystem(character& hero, std::vector<character*>& enemyList,Inventory& bag, std::vector<magic>& spellbook){
	bool win = false;
	bool run = false;
	hero.statCounter = 0;
	int exp = 0, gold = 0;
	for (int i = 0; i < size(enemyList);i++) {
		character a = *(enemyList[0]);
		exp += a.expGain;
		gold += a.gold;
	}
	do {
		applyEffect(hero);
		if (hero.turn == true) {
			hero.checkBuffs();
			hero.checkDebuffs();
			hero.refreshStats();
			getPlayerAction(hero, enemyList, run, bag, spellbook);
		}
		checkWin(enemyList,win);
		for (int i = 0;i < size(enemyList);i++) {
			character a = *(enemyList[i]);
			if (a.hp == 0) {
				std::cout << a.name << " has been defeated.\n";
				restoreAll(*enemyList[i]);
				enemyList.erase(enemyList.begin()+i);
				i--;
			}
			else {
				applyEffect(*enemyList[i]);
				checkCounters(*(enemyList[i]));
				if (a.turn == false) {
					continue;
				}
				else {
					getDamage(a, hero);
					std::cout << a.name << " has " << a.hp << " HP remaining.\n";
					if (hero.hp == 0) { run = true; break; };
				}
			}
		}
		checkEffect(hero);
		for (int i = 0;i < size(enemyList);i++) { checkEffect(*enemyList[i]); }

	} while (win == false and run == false);
	if (win == true and hero.hp > 0) {
		std::cout << hero.name << " has received " << exp << " exp and " << gold << " gold.\n";
		hero.exp += exp;
		hero.gold += gold;
		checkLvlUp(hero,spellbook);
		std::cout << hero.name << " now has " << hero.exp << " experience points.  " << hero.toNextLvl - hero.exp << " to next level\n";
	}
	else if (run == true) {
		std::cout << "You successfully escaped.\n";
	}
	hero.refreshStats();
	hero.statCounter = 0;
	hero.buffCounter = 0;
	hero.debuffCounter = 0;
	checkCounters(hero);
}
void checkCounters(character& guy) {
	guy.checkDebuffs();
	guy.checkBuffs();
}
void applyEffect(character& hero) {
	if (hero.status == "poison") {
		hero.hp -= int(0.1*(hero.maxHp));
		std::cout << hero.name << " suffers from poisoning. " << hero.name << " takes " << int(0.1*(hero.maxHp)) << " damage.\n";
		hero.statCounter--;
	}
	else if (hero.status == "sleep") {
		hero.turn = false;
		std::cout << hero.name << " is asleep and unable to act.\n";
		hero.statCounter--;
	}
}
void checkEffect(character& hero) {
	if (hero.statCounter == 0 and hero.status != "normal") {
		hero.status = "normal";
		std::cout << hero.name << " has recovered from status effects.\n";
		hero.turn = true;
	}
}
void restoreAll(character& a) {
		a.hp = a.maxHp;
		a.buffCounter = 0;
		a.statCounter = 0;
		a.debuffCounter = 0;
		checkCounters(a);
		checkEffect(a);
}