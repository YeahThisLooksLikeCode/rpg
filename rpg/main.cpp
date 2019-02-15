#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <ctime>
#include <sstream>
#include <fstream>
#include "character.h"
#include "battle.h"
#include "inventory.h"
#include "gear.h"
#include "arminv.h"
#include "equipment.h"
#include "weapon.h"
#include "choiceUI.h"
#include "items.h"
#include "magic.h"
#include "magobj.h"
#include "area.h"

void addSpell(magic spell,std::vector<magic>& spellbook) {
	spellbook.push_back(spell);
}
void removeSpell(magic spell,std::vector<magic>& spellbook) {
	for (int i = 0; i < size(spellbook);i++) {
		if (spell.name == spellbook[i].name) {
			spellbook.erase(spellbook.begin()+i);
			break;
		}
		else if ((i == size(spellbook) -1) and (spell.name != spellbook[i].name)) {
			std::cout << "Spell not found.\n";
			break;
		}
	}
}
bool checkArmourRequirements(character& hero,Gear piece) {
	for (int i = 0; i < size(hero.armourRest);i++) {
		if (hero.armourRest[i] == piece.weight) {
			return false;
			break;
		}
	}
	return true;
}
bool checkWeaponRequirements(character& hero, Weapon piece) {
	for (int i = 0; i < size(hero.weaponRest);i++) {
		if (hero.weaponRest[i] == piece.wtype) {
			return false;
			break;
		}
	}
	return true;
}
void showStats(character& hero,Equipment loadOut1,WeapEquip loadOut2) {
	std::cout << hero;
	std::cout << "Equipment: \n";
	std::cout << "---------------\n";
	std::cout << "Weapons \n";
	std::cout << "---------------\n";
	std::cout << loadOut2;
	std::cout << "Armour \n";
	std::cout << "---------------\n";
	std::cout << loadOut1;

}
void showInv(Inventory bag1, ArmInv bag2, WeaponInv bag3) {
	std::cout << "Miscellaneous \n";
	std::cout << "---------------\n";
	std::cout << bag1;
	std::cout << "Armour \n";
	std::cout << "---------------\n";
	std::cout << bag2;
	std::cout << "Weapons \n";
	std::cout << "---------------\n";
	std::cout << bag3;
}
void equipArmour(character& hero,Equipment& loadOut,ArmInv& bag) {
	std::vector<std::string> choices;
	std::vector<std::string> yn{"Yes","No"};
	std::vector<std::string> whatDo{"Stats","Equip","Back"};
	for (int i = 0; i < size(bag.Inv);i++) {
		choices.push_back(bag.Inv[i].name);
	}
	choices.push_back("Back");
	int choice,choice2,choice3;
	menu1:
	choice = getChoice(choices);
	if (choice == size(choices)-1) {
		
	}
	else {
		menu2:
		choice2 = getChoice(whatDo);
		switch (choice2) {
		case 0:
			std::cout << "\n" << bag.Inv[choice] << "\n";
		case 1:
			std::cout << "\nEquip " << bag.Inv[choice].name << "?\n";
			choice3 = getChoice(yn);
			switch (choice3) {
			case 0:
				if (checkArmourRequirements(hero, bag.Inv[choice]) == true) {
					std::cout << bag.Inv[choice].name << " has been equiped.\n";
					loadOut.equipArmour(bag.Inv[choice], hero, bag);
					break;
				}
				else {
					std::cout << "Armour class is restricted.\n";
				}
			case 1:
				goto menu2;
				break;
			}//switch3
			break;
		case 2:
			goto menu1;
		}//switch2
	}
	hero.refreshStats();
}
void equipWeapon(character& hero, WeapEquip& loadOut, WeaponInv& bag) {
	std::vector<std::string> choices;
	std::vector<std::string> yn{ "Yes","No" };
	std::vector<std::string> whatDo{ "Stats","Equip","Back" };
	for (int i = 0; i < size(bag.Inv);i++) {
		choices.push_back(bag.Inv[i].name);
	}
	choices.push_back("Back");
	int choice, choice2, choice3;
menu1:
	choice = getChoice(choices);
	if (choice == size(choices) - 1) {

	}
	else {
	menu2:
		choice2 = getChoice(whatDo);
		switch (choice2) {
		case 0:
			std::cout << "\n" << bag.Inv[choice] << "\n";
		case 1:
			std::cout << "\nEquip " << bag.Inv[choice].name << "?\n";
			choice3 = getChoice(yn);
			switch (choice3) {
			case 0:
				if (checkWeaponRequirements(hero, bag.Inv[choice]) == true) {
					std::cout << bag.Inv[choice].name << " has been equiped.\n";
					loadOut.equipWeapon(bag.Inv[choice], hero, bag);
					break;
				}
				else {
					std::cout << "Weapon type is restricted.\n";
				}
			case 1:
				goto menu2;
				break;
			}//switch3
			break;
		case 2:
			goto menu1;
		}//switch2
	}
	hero.refreshStats();
}
void useItem(character& hero, Inventory& bag) {
	std::vector<std::string> choices = bag.sInv;
	std::vector<std::string> whatDo{"Description","Use","Back"};
	std::vector<std::string> yn{"Yes","No"};
	choices.push_back("Back");
	menu:
	int choice = getChoice(choices);
	if (choice == size(choices)-1) {
		
	}
	else {
		int choice2 = getChoice(whatDo);
		int choice3;
		switch (choice2) {
		case 0:
			std::cout << "\n" << bag.Inv[choice] << "\n";
		case 1:
			std::cout << "Use " << bag.Inv[choice].name << "?\n";
			choice3 = getChoice(yn);
			switch (choice3) {
			case 0:
				std::cout << "Used " << bag.Inv[choice].name << ".\n";
				bag.useItem(bag.Inv[choice], hero);
			case 1:
				goto menu;
			}
			
		case 2:
			goto menu;
		}
		

	}
}
int main() {
	//std::vector<std::string> a{"Warrior","Mage","Priest","Thief"};
	std::vector<Item> Inv;
	std::vector<magic> spellbook;
	
	//Armour Objects / sEquip{ "Head","Chest","Gloves","Boots", "Ring","Trinket" }
	// -chest-
	Gear chest_starter("Peasant's Clothes", 2, "Garbage", "Chest");
	Gear chest_chain("Chain Mail Armour", 12, "Heavy", "Chest");
	Gear chest_chain2("Plate Mail Armour", 18, "Heavy", "Chest");
	chest_chain2.addStats("strength", 2);
	chest_chain2.addStats("constitution", 4);
	Gear chest_chain3("Templar Armour", 18, "Heavy", "Chest");
	Gear chest_leather("Leather Armour", 9, "Medium", "Chest");
	Gear chest_leather2("Studded Leather Armour", 12, "Medium", "Chest");
	chest_leather2.addStats("dexterity", 4);
	chest_leather2.addStats("strength", 2);
	Gear chest_leather3("Assassin's Robes", 16, "Medium", "Chest");
	chest_leather3.addStats("dexterity", 8);
	chest_leather3.addStats("strength", 2);
	Gear chest_cloth("Cloth Robes", 5, "Light", "Chest");
	chest_cloth.addStats("intelligence", 2);
	Gear chest_cloth2("Apprentice's Robes", 8, "Light", "Chest");
	chest_cloth2.addStats("intelligence", 6);
	Gear chest_cloth3("Battle Mage's Robes", 16, "Light", "Chest");
	chest_cloth3.addStats("intelligence", 8);
	chest_cloth3.addStats("constitution", 4);
	//-head-
	Gear helm_starter("Grandma's Collander", 4, "Garbage", "Head");
	Gear helm_chain("Plate Helm", 6, "Heavy", "Head");
	Gear helm_leather1("Guard's Helm", 3, "Medium", "Head");
	Gear helm_cloth("Pointy Hat", 2, "Light", "Head");
	Gear helm_cloth2("Apprentice's Hat",4,"Light","Head");
	helm_cloth2.addStats("intelligence", 4);
	Gear helm_cloth3("Battle Mage's Hood", 4, "Light", "Head");
	helm_cloth3.addStats("intelligence", 5);
	helm_cloth3.addStats("constitution", 4);
	Gear helm("Leather Armour of Mild Protection", 4, "Medium", "Head");
	helm.addStats("strength", 2);
	helm.addStats("constitution", 4);
	//-gloves-
	Gear hands_chain("Plate Gloves", 6, "Heavy", "Gloves");
	Gear hands_leather("Leather Gloves", 3, "Medium", "Gloves");
	hands_leather.addStats("dexterity",1);
	Gear hands_cloth("Cloth Gloves", 1, "Light", "Gloves");
	hands_cloth.addStats("intelligence",1);
	//-boots-
	Gear boots_starter("Worn-Out Shoes", 1, "Garbage", "Boots");
	Gear boots_chain("Plate Greaves", 6, "Heavy", "Boots");
	Gear boots_leather("Leather Boots", 2, "Medium", "Boots");
	boots_leather.addStats("dexterity",1);
	boots_leather.addStats("strength",1);
	Gear boots_cloth("Pointy Shoes", 1, "Light", "Boots");
	boots_cloth.addStats("intelligence",1);

	//
	//Weapon objects
	Weapon shield1("Buckler Shield", 6, "Left Hand");
	shield1.addStats("constitution", 6);
	Weapon sword1("Blade of Reprissal", 12, 2, "Sword", "Right Hand");
	sword1.addStats("strength", 4);
	sword1.addStats("intelligence", 8);
	Weapon sword2("Long Sword", 8, 0, "Sword", "Right Hand");
	Weapon sword_starter("Rusty Sword", 2, 0, "Garbage", "Right Hand");
	Weapon staff1("Oak Staff", 2, 0, "Staff", "Right Hand");
	staff1.addStats("intelligence", 4);
	Weapon staff2("Apprentice's Staff", 2, 0, "Staff", "Right Hand");
	staff2.addStats("intelligence", 6);
	Weapon staff3("Sinister Snair", 4, 0, "Staff", "Right Hand");
	staff3.addStats("intelligence", 12);
	Weapon dagger1("Throaght Cutter R", 8, 2, "Dagger", "Right Hand");
	dagger1.addStats("dexterity",2);
	Weapon dagger2("Throaght Cutter L", 8, 2, "Dagger", "Left Hand");
	dagger2.addStats("dexterity", 2);
	Weapon dagger3("Dagger", 4, 2, "Dagger", "Right Hand");
	//Item objects

	Item hppotion("Small Health Potion", 50, "health");
	Item hppotion2("Medium Health Potion", 75, "health");
	Item hppotion3("Large Health Potion", 100, "health");
	Item mppotion("Small Mana Potion", 50, "mana");
	Item mppotion2("Medium Mana Potion", 75, "mana");
	Item mppotion3("Large Mana Potion", 100, "mana");
	//Enemy Objects
	character slime("Slime","Monster",1,40);
	character goblin("Goblin", "Monster", 1,50);
	character goblin2("Goblin", "Monster", 2,65);
	character orc("Orc", "Warrior", 3,95);
	character wolf("Wolf", "Berserker", 1,40);
	character goblin_warrior("Goblin Warrior", "Warrior", 2,65);
	character goblin_assassin("Goblin Assassin", "Thief", 2,65);

	character enemy1("Minotaur", 200, 1500, 400, 16, 14, 18, 12, 12);
	//Shop Objects
	Shop shop1("Citadel Store", { hppotion,mppotion }, { 50,50 });
	Shop shop_gear1("Citadel Armours", { hands_leather,hands_chain,hands_cloth,helm_leather1,helm_cloth,
		helm,chest_chain,chest_cloth,chest_leather},{75,100,50,115,50,350,300,100,215});
	Shop shop_weapon1("Citadel Weapons", { sword1,sword2,dagger1,dagger2,dagger3,staff1,staff2,staff3 }, {350,50,70,70,25,25,50,75});
	Shop temple1("Temple of Some God", 40);
	//Area Objects
	std::vector<character> enemies1{ goblin2,goblin };
	std::vector<character> enemies2{ goblin };
	std::vector<character> enemies3{slime,goblin};
	std::vector<character> enemies4{ orc, wolf };
	std::vector<character> enemies5{ orc,goblin_assassin,goblin_warrior };
	std::vector<character> enemies6{ goblin_warrior, wolf };
	std::vector<std::vector<character>> encounter2{ enemies1,enemies2 };
	std::vector<std::vector<character>> encounter1{ enemies3,enemies2 };
	std::vector<std::vector<character>> encounter3{ enemies4,enemies1 };
	std::vector<std::vector<character>> encounter4{ enemies5,enemies4,enemies6 };
	std::vector<int> rates{ 25,75 };
	std::vector<int> rates2{ 50,50 };
	std::vector<int> rates3{ 25,50,25 };
	Area area1("Greenbelt Woods", encounter1, rates2);
	Area area2("Hyru Plane", encounter2, rates);
	Area area3("Mysterious Tower", encounter2, rates);
	Area area4("Citadel", { shop1,shop_gear1,shop_weapon1 ,temple1 });
	Area area5("Mountain Pass", encounter3, rates);
	Area area6("Silent Woods", encounter3, rates2);
	Area area7("Mirage Desert", encounter4, rates3);
	Area area8("Black Keep Camps", encounter4, rates3);
	Area area9("Black Keep", encounter4, rates3);
	area1.getAreaDescription("A vast, restful forest. The path you follow is well travelled.\n");
	area1.getAreaDirections("Go east", "Go west");
	area2.getAreaDescription("A vast green plane with scarce trees dotted about.\n");
	area2.getAreaDirections("Go west");
	area3.getAreaDescription("Before you lies a grand tower reaching towards the clouds. There is no obvious way in.\n");
	area3.getAreaDirections("Go east");
	area2.getAreaDirections("Go north");
	area4.getAreaDirections("Go south","Go north");
	area5.getAreaDirections("Go north","Go south");
	area6.getAreaDirections("Go west", "Go south");
	area7.getAreaDirections("Go west","Go east");
	area8.getAreaDirections("Go south","Go east");
	area9.getAreaDirections("Go north");
	//Game Start
	std::cout << "Enter character name: ";
	std::string n;
	getline(std::cin,n);
	std::cout << "Enter character class(Warrior,Priest,Thief,Mage): ";
	std::string m;
	getline(std::cin, m);
	character hero(n,m,2,1000);
	Inventory bag;
	ArmInv bag2;
	WeaponInv bag3;
	
	std::vector<Gear> myStuff(6);
	Equipment loadOut(myStuff);
	std::vector<Weapon> myStuff2(2);
	WeapEquip loadOut2(myStuff2);
	std::cout << "\n" << hero;
	//hero.exp += 1800;
	//checkLvlUp(hero);

	//equip/add stuff
	if (hero.charClass == "Mage") { addSpell(returnMagic("Fire Ball"), spellbook); }
	bag2.addToInventory(helm_starter, 1);
	bag2.addToInventory(chest_starter,1);
	bag2.addToInventory(boots_starter,1);
	loadOut.equipArmour(helm_starter, hero, bag2);
	loadOut.equipArmour(chest_starter, hero, bag2);
	loadOut.equipArmour(boots_starter, hero, bag2);
	bag3.addToInventory(sword_starter, 1);
	loadOut2.equipWeapon(sword_starter, hero, bag3);
	bag.addToInventory(hppotion, 2);
	//test area
	bool gameOver = false;
	int x = 1, y = 0;
	
	std::vector<Area> aMap{ area1,area2,area3,area4,area5,area6,area7,area8,area9 };
	std::vector<std::string> map1{"Mysterious Tower","Greenbelt Woods","Hyru Plane" };
	std::vector<std::string> map2{ "" ,"","Citadel" };
	std::vector<std::string> map3{ "Black Keep","","Mountain Pass" };
	std::vector<std::string> map4{ "Black Keep Camps","Mirage Desert","Silent Woods" };
	std::vector<std::vector<std::string>> map{map1,map2,map3,map4};
	std::vector<std::string> choices{ hero.name,"Inventory","Spell Book","Area" ,"Quit Game"};
	std::vector<std::string> choices2{"Items", "Armours", "Weapons","Back"};
	int choice2;
	bool endGame = false;
	while (endGame == false) {
		gameOver = false;
		int choice = getChoice(choices);
		switch (choice) {
		case 0:
			showStats(hero, loadOut, loadOut2);
			break;
		case 1:
			showInv(bag, bag2, bag3);
			choice2 = getChoice(choices2);
			switch (choice2) {
			case 0:
				useItem(hero, bag);
				break;
			case 1:
				equipArmour(hero, loadOut, bag2);
				break;
			case 2:
				equipWeapon(hero,loadOut2,bag3);
				break;
			case 3:
				break;
			}
			
			break;
		case 2:
			std::cout << "\n";
			for (int i = 0; i < size(spellbook);i++) {
				std::cout << spellbook[i].name << "\n";
			}
			std::cout << "\n";
			break;
		case 3:
			while (gameOver == false) {
				Area location = fetchArea(map[y][x], aMap);
				areaManager(location, x, y, hero, bag, bag2, bag3, spellbook, gameOver);
			};
			break;
		case 4:
			endGame = true;
			break;
		};
	}
	
	std::string j;
	getline(std::cin, j);
	return 0;
}

