#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "gear.h"

Gear::Gear() {};

Gear::Gear(std::string name, int armour, std::string weight, std::string slot) {
	this->name = name;
	this->armour = armour;
	this->weight = weight;
	this->slot = slot;

	istats.assign(5, 0);

};

void Gear::addStats(std::string stat, int n) {
	for (int i = 0; i < size(sstats);i++) {
		if (sstats[i] == stat) {
			istats[i] = n;
			break;
		}
	}
};
Gear::operator const char*() {
	std::ostringstream statStream;
	statStream << "Name: " << name << "\n"
		<< "Armour: " << armour << "\n"
		<< "Class: " << weight << "\n"
		<< "Slot: " << slot << "\n";
	for (int i = 0; i < size(sstats);i++) {
		statStream << sstats[i] << ": +" << istats[i] << "\n";
	};
	statString = statStream.str();
	return statString.c_str();

};
