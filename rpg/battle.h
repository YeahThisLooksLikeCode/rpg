#ifndef BATTLE_H
#define BATTLE_H
//#include "character.h"
#include "inventory.h"
#include "magic.h"
void checkLvlUp(character& hero, std::vector<magic>& spellbook);
bool checkCrit(character& attacker);
void getDamage(character& attacker, character& defender);
void checkWin(std::vector<character*> enemyList, bool& win);
void getPlayerAction(character& hero, std::vector<character*> enemyList, bool& run, Inventory& bag, std::vector<magic> spellbook);
void battleSystem(character& hero, std::vector<character*>& enemyList, Inventory& bag, std::vector<magic>& spellbook);
void checkCounters(character& guy);
void applyEffect(character& hero);
void checkEffect(character& hero);
void restoreAll(character& a);
#endif
