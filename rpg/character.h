#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
class character {
public:
	int expGain,mana,maxMana;
	std::vector<int> istats,statRaises,statDecrease,statCurve;
	std::vector<std::string> sstats{"strength","dexterity","constitution","intelligence","wisdom"};
	int level, exp, toNextLvl, hp, baseHp,baseMp ,attackMax, attackMin, maxHp,armour,crit;
	std::string charClass;
	std::string name;
	std::string charString;
	std::vector<std::string> armourRest,weaponRest;
	int statCounter, buffCounter, debuffCounter = 0, gold = 0;
	std::string status = "normal";
	bool buffed = false;
	bool debuffed = false;
	bool turn = true;

	character();
	character(std::string name);
	character(std::string name, std::string charClass, int level,int gold);
	character(std::string name, int maxHp,int expGain ,int goldGain,int str, int dex, int con, int intel, int wisd);
	void checkBuffs();
	void checkDebuffs();
	void refreshStats();
	void levelUp();
	operator const char*();
};

#endif
