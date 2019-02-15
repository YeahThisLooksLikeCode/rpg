#include "weapon.h"
#include "character.h"
#include <string>
#include <sstream>
#include <iostream>

	//Weapon objects
	Weapon::Weapon() {
	};
	Weapon::Weapon(std::string name, int armour, std::string slot) {
		this->name = name;
		this->armour = armour;
		this->slot = slot;
		wtype = "Shield";
		istats.assign(5, 0);
	}
	Weapon::Weapon(std::string name, int attack, int crit, std::string wtype, std::string slot) {
		this->attack = attack;
		this->name = name;
		this->wtype = wtype;
		this->slot = slot;
		this->crit = crit;
		attackMax = attack;
		attackMin = attack / 2;
		istats.assign(5, 0);
	};
	void Weapon::addStats(std::string stat, int n) {
		for (int i = 0; i < size(sstats);i++) {
			if (sstats[i] == stat) {
				istats[i] += n;
				break;
			}
		}
	};
	Weapon::operator const char*() {
		std::ostringstream weaponStream;
		weaponStream << "Weapon: " << name << "\n"
			"Type: " << wtype << "\n"
			<< "Slot: " << slot << "\n";
		if (wtype == "Shield") {
			weaponStream << "Armour: " << armour << "\n";
		}
		else {
			weaponStream << "Attack: " << attack << "\n";
		}
		for (int i = 0; i < size(sstats);i++) {
			if (istats[i] == 0) { continue; }
			else {
				weaponStream << sstats[i] << " +" << istats[i] << "\n";
			}
		}
		weaponString = weaponStream.str();
		return weaponString.c_str();
	};

	//Weapon Inventory objects
	WeaponInv::WeaponInv() {

		}
	void WeaponInv::addToInventory(Weapon obj, int amount) {
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
	void WeaponInv::removeFromInventory(Weapon obj, int amount) {
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
	WeaponInv::operator const char*() {
			std::ostringstream weaponStream;
			for (int i = 0;i < size(Inv); i++) {
				weaponStream << i +1 << "- " << Inv[i].name << " x" << iInv[i] << "\n";
			}
			weaponString = weaponStream.str();
			return weaponString.c_str();
		}

	//Weapon Loadout
	WeapEquip::WeapEquip() {};
	WeapEquip::WeapEquip(std::vector<Weapon> loadOut) {
			this->loadOut = loadOut;
			bEquip.assign(2, false);
		};
	void WeapEquip::equipWeapon(Weapon piece, character& hero, WeaponInv& bag) {
			int islot = returnSlot(piece);
			if (bEquip[islot] == true) {
				hero.attackMax -= loadOut[islot].attack;
				hero.attackMin -= loadOut[islot].attackMin;
				hero.crit -= loadOut[islot].crit;
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
			hero.attackMax += piece.attack;
			hero.attackMin += piece.attackMin;
			hero.crit += piece.crit;
			hero.armour += piece.armour;
			hero.istats[0] += piece.istats[0];
			hero.istats[1] += piece.istats[1];
			hero.istats[2] += piece.istats[2];
			hero.istats[3] += piece.istats[3];
			hero.istats[4] += piece.istats[4];
		};
	int WeapEquip::returnSlot(Weapon piece) {
			for (int i = 0; i < size(sEquip);i++) {
				if (sEquip[i] == piece.slot) {
					return i;
					break;
				}
			}
			return -1;
		};
	WeapEquip::operator const char*() {
			std::ostringstream equipStream;
			for (int i = 0; i < size(sEquip);i++) {
				if (bEquip[i] == false) {
					equipStream << sEquip[i] << ": none\n";
				}
				else {
					equipStream << sEquip[i] << ": " << loadOut[i].name << " ";
					if (loadOut[i].wtype == "Shield") {
						equipStream << loadOut[i].armour << " armour ";
					}
					else {
						equipStream << loadOut[i].attackMin << "-" << loadOut[i].attackMax
							<< " atk " << loadOut[i].crit << "% crit ";
					}
						
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

