#include <sstream>
#include <vector>
#include "gear.h"
#include "character.h"
#include "arminv.h"
#include "equipment.h"

	Equipment::Equipment(std::vector<Gear> loadOut) {
		this->loadOut = loadOut;
		bEquip.assign(6, false);
	};
	void Equipment::equipArmour(Gear piece, character& hero, ArmInv& bag) {
		int islot = returnSlot(piece);
		if (bEquip[islot] == true) {
			
			hero.armour -= loadOut[islot].armour;
			hero.istats[0] -= loadOut[islot].istats[0];
			hero.istats[1] -= loadOut[islot].istats[1];
			hero.istats[2] -= loadOut[islot].istats[2];
			hero.istats[3] -= loadOut[islot].istats[3];
			hero.istats[4] -= loadOut[islot].istats[4];
			bag.addToInventory(loadOut[islot], 1);

		};
		loadOut[islot] = piece;
		bag.removeFromInventory(piece, 1);
		bEquip[islot] = true;
		hero.armour += piece.armour;
		hero.istats[0] += piece.istats[0];
		hero.istats[1] += piece.istats[1];
		hero.istats[2] += piece.istats[2];
		hero.istats[3] += piece.istats[3];
		hero.istats[4] += piece.istats[4];
	};
	int Equipment::returnSlot(Gear piece) {
		for (int i = 0; i < size(sEquip);i++) {
			if (sEquip[i] == piece.slot) {
				return i;
				break;
			}
		}
		return -1;
	};
	Equipment::operator const char*() {
		std::ostringstream equipStream;
		for (int i = 0; i < size(sEquip);i++) {
			if (bEquip[i] == false) {
				equipStream << sEquip[i] << ": none\n";
			}
			else {
				equipStream << sEquip[i] << ": " << loadOut[i].name
					<< " +" << loadOut[i].armour
					<< " armour ";
				for (int j = 0; j < size(loadOut[i].sstats);j++) {
					if (loadOut[i].istats[j] == 0) {
						continue;
					}
					else {
						equipStream << "+" << loadOut[i].istats[j] << " " << loadOut[i].sstats[j] << " ";
					}
				}
				equipStream << "\n";
			}
		}
		equipString = equipStream.str();
		return equipString.c_str();
	};
