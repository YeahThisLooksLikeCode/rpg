#include <iostream>
#include <sstream>
#include <string>
#include "inventory.h"
#include "character.h"
#include "items.h"

	Inventory::Inventory() {

	};
	void Inventory::addToInventory(Item obj, int amount) {
		if (size(sInv) < 1) {
			sInv.push_back(obj.name);
			iInv.push_back(amount);
			Inv.push_back(obj);
		}
		else {
			for (int i = 0;i < size(sInv); i++) {
				if (sInv[i] == obj.name) {
					iInv[i] += amount;
					break;
				}
				if ((sInv[i] != obj.name) and (i == (size(sInv) - 1))) {
					sInv.push_back(obj.name);
					iInv.push_back(amount);
					Inv.push_back(obj);
					break;
				}
			}
		}
	};
	void Inventory::removeFromInventory(Item obj, int amount) {
		for (int i = 0; i < size(sInv);i++) {
			if (obj.name == sInv[i]) {
				iInv[i] -= amount;
				if (iInv[i] <= 0) {
					sInv.erase(sInv.begin() + i);
					iInv.erase(iInv.begin() + i);
					Inv.erase(Inv.begin() + i);
					break;
				}
				
			}//obj == sinv
			else if (obj.name != sInv[i] and i == (size(sInv) - 1)) {
				std::cout << "Object not found.\n";
			}
		}//for i
	};
	void Inventory::useItem(Item obj, character& hero) {
		obj.effect(hero);
		removeFromInventory(obj,1);
	};
	Inventory::operator const char*() {
		std::ostringstream invStream;
		for (int i = 0;i < size(sInv); i++) {
			invStream << i + 1 << "- " << sInv[i] << " x" << iInv[i] << "\n";
		}
		invString = invStream.str();
		return invString.c_str();
	}