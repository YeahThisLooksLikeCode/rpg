#include "magobj.h"


magic returnMagic(std::string name) {
	//magic objects
	magic fireball("Fire Ball", 35, 15, "damage");
	magic fireball2("Combustion", 70, 40, "damage");
	magic fireball3("Inferno", 150, 90, "damage");
	magic cure1("Heal Light Wounds", 35, 15, "heal");
	magic cure2("Heal Medium Wounds", 100, 40, "heal");
	magic cure3("Heal Grave Wounds", 200, 80, "heal");
	magic sleep1("Sleep", 4, 35, "sleep", "status");
	magic sleep2("Dream State", 7, 70, "sleep", "status");
	magic str_buff("Enhance Strength", 4, 35, 0, 4, "buff");
	magic dex_buff("Enhance Dexterity", 4, 35, 1, 4, "buff");
	magic int_buff("Enhance Intelligence", 4, 35, 3, 4, "buff");
	magic wisd_buff("Enhance Wisdom", 4, 35, 4, 4, "buff");
	magic str_debuff("Mark of Enfeeblement", 4, 35, 0, 4, "debuff");
	magic dex_debuff("Mark of Blunder", 4, 35, 1, 4, "debuff");
	magic int_debuff("Mark of Foolishness", 4, 35, 3, 4, "debuff");
	magic wisd_debuff("Mark of Ignorance", 4, 35, 0, 4, "debuff");
	magic poison1("Poison", 7, 35, "poison", "status");
	magic poison2("Miasma", 11, 65, "poison", "status");
	
	std::vector<magic> abilities{fireball,fireball2,fireball3,cure1,cure2,cure3,sleep1,sleep2,
		str_buff,dex_buff,int_buff,wisd_buff,str_debuff,dex_debuff,int_debuff,wisd_debuff,
	poison1,poison2};
	for (int i = 0; i < size(abilities);i++) {
		if (name == abilities[i].name) {
			return abilities[i];
		}
	}

}