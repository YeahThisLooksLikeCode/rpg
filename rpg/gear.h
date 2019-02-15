#ifndef GEAR_H
#define GEAR_H

class Gear {
public:
	int armour;
	std::vector<int> istats;
	std::vector<std::string> sstats{ "strength","dexterity","constitution","intelligence","wisdom" };
	std::string weight;
	std::string slot;
	std::string name;
	std::string statString;

	Gear();
	Gear(std::string name, int armour, std::string weight, std::string slot);
	void addStats(std::string stat, int n);
	operator const char*();

};

#endif
