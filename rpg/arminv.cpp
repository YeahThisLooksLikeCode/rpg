#include <sstream>
#include <vector>
#include <iostream>
#include "arminv.h"
#include "gear.h"

	ArmInv::ArmInv() {

	}
	void ArmInv::addToInventory(Gear obj, int amount) {
		if (size(Inv) < 1) {
			Inv.push_back(obj);
			iInv.push_back(amount);
		}
		else {
			for (int i = 0;i < size(Inv); i++) {
				if (Inv[i].name == obj.name) {
					iInv[i] += amount;
					break;
				}
				else if ((Inv[i].name != obj.name) and (i == (size(Inv) - 1))) {
					Inv.push_back(obj);
					iInv.push_back(amount);
					break;
				}
			}
		}
	}
	void ArmInv::removeFromInventory(Gear obj, int amount) {
		for (int i = 0; i < size(Inv);i++) {
			if (obj.name == Inv[i].name) {
				iInv[i] -= amount;
				if (iInv[i] <= 0) {
					Inv.erase(Inv.begin() + i);
					iInv.erase(iInv.begin() + i);
					break;
				}
			}//obj == sinv
			else if (obj.name != Inv[i].name and i == (size(Inv) - 1)) {
				std::cout << "Object not found.\n";
			}
		}//for i
	};
	ArmInv::operator const char*() {
		std::ostringstream invStream;
		for (int i = 0;i < size(Inv); i++) {
			invStream << i + 1 << "- " << Inv[i].name << " x" << iInv[i] << "\n";
		}
		invString = invStream.str();
		return invString.c_str();
	}
