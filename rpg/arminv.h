#ifndef ARMINV_H
#define ARMINV_H
#include "gear.h"
#include <vector>
class ArmInv {
public:
	std::vector<std::string> sInv;
	std::vector<Gear> Inv;
	std::vector<int> iInv;
	std::string invString;

	ArmInv();
	void addToInventory(Gear obj, int amount);
	void removeFromInventory(Gear obj, int amount);
	operator const char*();
};
#endif
