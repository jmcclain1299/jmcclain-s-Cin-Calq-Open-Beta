/*This is the file: mob.cpp
This is the implementation for the class Mob.
The interface for the class Mob(and all subclasses) is in 
the header file Mob.h*/
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Mob.h"
#include <cmath>
#include <algorithm>
#include <cstddef>
#include <set>
#include <list>
#include <sstream>
#include <fstream>
namespace jmcclain1299
{
	Mob::Mob()//Constructor for Mobs
	{
		//deliberately empty
	}
	Mob::Mob(const Mob& mob)//Copy Constructor for Mobs
	{
		level = mob.level;
		rarity = mob.rarity;
		baseAttack = mob.baseAttack;
		baseDefense = mob.baseDefense;
		name = mob.name;
		skillName = mob.skillName;
		element = mob.element;
		id = mob.id;
		prom1 = mob.prom1;
		prom2 = mob.prom2;
		prom4 = mob.prom4;
		prom5 = mob.prom5;
		modifier = mob.modifier;
		target = mob.target;
		weakness = mob.weakness;
		tdamage = mob.tdamage;
		tdefense = mob.tdefense;
		tarmor = mob.tarmor;
		typeadv = mob.typeadv;
		followers = mob.followers;
		attack = mob.attack;
		defense = mob.defense;
		promotion = mob.promotion;
		quest = mob.quest;
	}
	Mob::Mob(string name, int attack, int defense, char element, int followers, int id, char weakness)//Constructor for a Mob with att/def
		: name(name), baseAttack(attack), baseDefense(defense), element(element), followers(followers), id(id), target(target), weakness(weakness)
	{
		//deliberately empty
	}
	Mob::Mob(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillName, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		: level(leveln), rarity(rarity), baseAttack(baseAttack), baseDefense(baseDefense), skillName(skillName), name(name), element(element), id(id), prom1(prom1), prom2(prom2), prom4(prom4), prom5(prom5), modifier(modifier), target(target), weakness(weakness), quest(quest)
	{
		//deliberately empty
	}
	//Accesor functions follow
	int Mob::getAttack()
	{
		return attack;
	}
	char Mob::getTarget()
	{
		return target;
	}
	int Mob::getDefense()
	{
		return defense;
	}
	char Mob::getElement()
	{
		return element;
	}
	int Mob::getFollowers()
	{
		return followers;
	}
	string Mob::getName()
	{
		return name;
	}
	string Mob::getSkillName()
	{
		return skillName;
	}
	int Mob::getRarity()
	{
		return rarity;
	}
	int Mob::getId()
	{
		return id;
	}


	Line::Line()//Default line constructor(under construction)
	{
		//intentionally empty
	}
	
	Line::Line(vector<Mob>& lineup)//Constructs an array of class Line with Mob input, with lineup in the call to create the line
	{
		for (int i = 0; i < lineup.size(); i++)
		{
			line.push_back(lineup[i]);
		}
		lineIds = setLineIds();//Sets the lineIds in reverse of the lineup for the calcSeed (as performed by game)
		lineFollowers = setFollowers();//Sets line Followers based on Mob followers
		
	}
	void Line::setStats()//sets all the stats for heroes in a line
	{
		for (int i = 0; i < line.size(); i++)
			line[i].setStats();
	}
	int Line::setFollowers()//Sets the follower amount used by said line
	{
		int sum = 0;
		for (int i = 0; i < line.size(); i++)
			sum += line[i].getFollowers();
		return sum;
	}
	vector<int> Line::setLineIds()//Function that sets the line ids
	{
		vector<int> back;
		for (int i = line.size() - 1; i > -1; i--)
			back.push_back(line[i].getId());
		if (line.size() < 6)
			back.push_back(-1);
		return back;
	}
	vector<Mob> Line::getLine()//returns the line stored by line
	{
		return line;
	}
	void Mob::setLevel(int leveln)//Mutators for Mob Class
	{
		level = leveln;
	}
	void Mob::setLevel(double leveln)//Sets promotion and level if they exist
	{
		level = (leveln / 1);
		int a = leveln;
		int b = ((leveln - a) * 10);
		promotion = b;
	}
	int Mob::getPromotion()//Accessor Functions
	{
		return promotion;
	}

	int Mob::getLevel()
	{
		return level;
	}
	char Mob::getWeakness()
	{
		return weakness;
	}
	void Mob::setPoints()//Mutator Functions, here for points.
	{
		{
			points = level - 1;
			if (rarity == 1)
			{
				points *= 2 * ratio + (rarity + 1)*(promotion >= 3);
			}
			else if (rarity == 2)
			{
				points *= 6 * ratio + (rarity + 1)*(promotion >= 3);
			}
			else if (rarity == 3)
			{
				points *= 12 * ratio + (rarity + 1)*(promotion >= 3);
			}
			else if (rarity == 0)
			{
				points *= 1 * ratio + (rarity + 1)*(promotion >= 3);
			}
		};
	}
	void Mob::setAttack(int& attacks)//Sets the attack stat 
	{
		attack = attacks;
	}
	void Mob::setAttack()//Sets Attack.
	{
		
		if (promotion == 0 && level != 0)
			attack = baseAttack + round((points * baseAttack) / (baseDefense + baseAttack));
		else if (level != 0)
		{
			attack = baseAttack + round((points * baseAttack) / (baseDefense + baseAttack));
			if (promotion >= 2)
				attack += prom2;
			if (promotion >= 4)
				attack += prom4;
		}
		if (rarity == 4)
		{
			attack += 1;
		}
	}
	void Mob::setDefense()//Sets Defense.
	{
		if (promotion == 0 && level != 0)
			defense = baseDefense + round(points * baseDefense / (baseDefense + baseAttack));
		else if (level != 0)
		{
			defense = baseDefense + round(points * baseDefense / (baseDefense + baseAttack));
			if (promotion >= 1)
				defense += prom1;
			if (promotion >= 4)
				defense += prom4;
		}
	}
	void Mob::setDefense(int& defenses)
	{
		defense = defenses;
	}
	void Mob::setStats()//Sets the Attack and Defense with 1 call, same as points(for certain functions).
	{
		setPoints();
		setAttack();
		setDefense();
		if (promotion == 5)
			modifier += prom5;
	}
	extra::extra()//Construct for extra hero of Mob
	{
		//deliberately empty
	}
	extra::extra(const Mob& mob)
		: Mob(mob)
	{
	}
	extra::extra(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		: Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void extra::skillFunction(vector<Mob>& line)//extra function, + armor and hp
	{
		for (int i = 0; i < line.size(); i++)
		{
			if ((target == line[i].getElement()) || (target == 'x'))
			{
				line[i].tdamage += modifier;
				line[i].tarmor += modifier;
			}
		}
	}
	buffahe::buffahe()//Buffahe hero
	{
		//deliberately empty
	}
	buffahe::buffahe(const Mob& mob)
		: Mob(mob)
	{
	}
	buffahe::buffahe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		: Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buffahe::skillFunction(Line& line1, Line& line2)//Heal and Aoe, Aoe affected by bubbles/moak's debuff
	{
		vector<Mob> lane1 = line1.getLine(), lane2 = line2.getLine();
		for (int i = 0; i < lane1.size(); i++)
		{
			if ((lane1[i].tdefense > 0) && (lane1[i].tdefense < lane1[i].getDefense()))
			lane1[i].tdefense += (floor((min(99, level) * modifier)));
		}
		for (int i = 0; i < lane2.size(); i++)
		{
			lane2[i].tdefense -= ((floor((min(99, level) * modifier ))) * line2.debuff);
		}
		line1 = lane1;
		line2 = lane2;
	}
	dmg::dmg()//dmg hero
	{
		//deliberately empty
	}
	dmg::dmg(const Mob& mob)
		: Mob(mob)
	{
	}
	dmg::dmg(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void dmg::skillFunction(Mob& targets)//Sets line[0]'s damage after buff
	{
		if ((target == targets.getElement()) || (target == 'x'))
		{
			targets.tdamage += modifier;
		}
	}
	def::def()//def hero
	{
		//deliberately empty
	}
	def::def(const Mob& mob)
		: Mob(mob)
	{
	}
	def::def(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void def::skillFunction(vector<Mob>& line)//Sets armor of hero
	{
		for (int i = 0; i < line.size(); i++)
		{
			if ((target == line[i].getElement()) || (target == 'x'))
			{
				line[i].tarmor += modifier;
			}
		}
	}
	aoe::aoe()//aoe hero
	{
		//deliberately empty
	}
	aoe::aoe(const Mob& mob)
		: Mob(mob)
	{
	}
	aoe::aoe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void aoe::skillFunction(Line& line, Line& line2)//Aoe damage to line minus the debuff
	{
		vector<Mob> lane = line.getLine();
		for (int i = 0; i < lane.size(); i++)
		{
			int damage = modifier * line.debuff;
			lane[i].tdefense -= modifier;
			line2.totaldamage += damage;
		}
		line = lane;
	}
	heal::heal()//heal hero
	{
		//deliberately empty
	}
	heal::heal(const Mob& mob)
		: Mob(mob)
	{
	}
	heal::heal(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void heal::skillFunction(vector<Mob>& line, Line lane2)//Heals mob if it's alive and not at max hp
	{
		for (int i = 0; i < line.size(); i++)
		{
			
			int moda = (line[i].tdefense + modifier) * lane2.debuff;
			if (((target == line[i].getElement()) || (target == 'x') ) && (line[i].tdefense > 0))
			{
				line[i].tdefense = min(moda, line[i].getDefense());
			}
		}
	}
	rico::rico()//rico hero
	{
		//deliberately empty
	}
	rico::rico(const Mob& mob)
		: Mob(mob)
	{
	}
	rico::rico(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, int target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void rico::skillFunction(Line& line, int& attack)//Ricochet damage after bubbles
	{
		vector<Mob> lane = line.getLine();
		for (int i = 1; (i < lane.size() && i < (target + 1)); i++)
		{
			attack = ((attack * modifier) * line.debuff);
			lane[i].tdefense -= attack;
		}
		line = lane;
	}
	buff::buff()//buff hero
	{
		//deliberately empty
	}
	buff::buff(const Mob& mob)
	: Mob(mob)
	{

	}
	buff::buff(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buff::skillFunction()//Buff for Guem
	{
		attack *= modifier;
	}
	mon::mon()//Mon hero
	{
		//deliberately empty
	}
	mon::mon(const Mob& mob)
		: Mob(mob)
	{
	}
	mon::mon(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void mon::skillFunction(vector<Mob>& line)//Sets gerors attack based on how many mobs are behind him
	{
		int i = 0;
		while (line[i].getSkillName() != "mon")
			i++;
		i++;
		for (i; i < line.size(); i++)
		{
			if (line[i].getSkillName() == "mob")
			{
				attack *= modifier;
				tdefense *= modifier;
			}
		}

	}
	turna::turna()//turna mob
	{
		//deliberately empty
	}
	turna::turna(const Mob& mob)
		: Mob(mob)
	{
	}
	turna::turna(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void turna::skillFunction(Line& line)
	{
		attack += modifier * line.debuff;
	}
	rainbow::rainbow()//rainbow mob
	{
		//deliberately empty
	}

	rainbow::rainbow(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	rainbow::rainbow(const Mob& mob)
		: Mob(mob)
	{
	}
	void rainbow::skillFunction(vector<Mob> lane)//sets aoyuki's attack
	{

		vector<Mob> line = lane;
		int i = 0, a = line.size();
		while (line[i].getSkillName() != "rainbow")
			i++;
		int she = i;
		int moda = lane[she].getAttack();
		if ((a - i) >= 4)
		{
			set<char> rainbows;
			for (i; i < line.size(); i++)
			{
				rainbows.insert(line[i].getElement());
			}
			set<char>::iterator it = rainbows.find('v');
			while (it != rainbows.end())
			{
				if (it != rainbows.end())
				{
					rainbows.erase(it);
					it = rainbows.find('v');
				}
			}
			
			if (rainbows.size() == 4)
			{
				moda = lane[she].getAttack() + modifier;
				attack = moda;
			}
		}
	}
	ban::ban()//Giabyte/ban hero
	{
		//deliberately empty
	}
	ban::ban(const Mob& mob)
		: Mob(mob)
	{
	}
	ban::ban(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void ban::skillFunction(Line line)//Reduces hp * bubbles
	{
		tdefense -= ((tdefense / modifier) * line.debuff);
	}

	purity::purity()//Purity hero
	{
		//deliberately empty
	}
	purity::purity(const Mob& mob)
		: Mob(mob)
	{
	}
	purity::purity(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void purity::skillFunction(Mob& targets) //sets purity's buff
	{
		if ((target == targets.getElement()) || (target == 'x'))
		{
			typeadv = modifier;
		}
	}
	boom::boom()//boom hero
	{
		//deliberately empty
	}
	boom::boom(const Mob& mob)
		: Mob(mob)
	{
	}
	boom::boom(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void boom::skillFunction(Line& lane, Line& lane2)//Damages opposing line based on hp * it's modifier
	{
		int totdamage = 0;
		vector<Mob> line = lane.getLine();
		int damage = attack * modifier;
		for (int i = 0; (i < line.size() && i < target); i++)
		{
			line[i].tdefense -= damage;
			totdamage += damage;
		}
		lane2.totaldamage += totdamage;
		lane = line;
	}
	buffdef::buffdef()//buffdef Hero
	{
		//deliberately empty
	}
	buffdef::buffdef(const Mob& mob)
		: Mob(mob)
	{
	}
	buffdef::buffdef(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buffdef::skillFunction(vector<Mob>& line)//Sets armor of units based on skill modifiers
	{
		for (int i = 0; i < line.size(); i++)
		{
			if ((target == line[i].getElement()) || (target == 'x'))
			{
				int buff = floor(min(level, 99) * modifier);
				line[i].tarmor += buff;
			}
		}
	}
	buffatk::buffatk()//buffatk hero
	{
		//deliberately empty
	}
	buffatk::buffatk(const Mob& mob)
		: Mob(mob)
	{
	}
	buffatk::buffatk(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buffatk::skillFunction(Mob& targets)//Sets first units attack based on skill
	{
		if ((target == targets.getElement()) || (target == 'x'))
		{
			int damage = floor(min(level, 99) * modifier);
			targets.tdamage += damage;
		}
	}
	buffboth::buffboth()//buffboth hero
	{
		//deliberately empty
	}
	buffboth::buffboth(const Mob& mob)
		: Mob(mob)
	{
	}
	buffboth::buffboth(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buffboth::skillFunction(vector<Mob>& line)//Sets turn attack and turnarmor according to skills
	{
		for (int i = 0; i < line.size(); i++)
		if ((target == line[i].getElement()) || (target == 'x'))
		{
			int amount = floor(min(level, 99) * modifier);
			line[i].tdamage += amount;
			line[i].tarmor += amount;
		}
	}
	buffaoe::buffaoe()//buff aoe hero
	{
		//deliberately empty
	}
	buffaoe::buffaoe(const Mob& mob)
		: Mob(mob)
	{
	}
	buffaoe::buffaoe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)//Constructs a Mob with the "extra" skill.
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buffaoe::skillFunction(Line& lane, Line& lane2)//sets enemy hp * bubbles
	{
		vector<Mob> line = lane.getLine();
		int damage = floor(min(level, 99) * modifier);
		for (int i = 0; i < line.size(); i++)
		{
			line[i].tdefense -= damage * lane.debuff; 
			lane2.totaldamage += damage;
		}
		lane = line;
	}
	buffheal::buffheal()//buffheal hero
	{
		//deliberately empty
	}
	buffheal::buffheal(const Mob& mob)
		: Mob(mob)
	{
	}
	buffheal::buffheal(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void buffheal::skillFunction(vector<Mob>& line, Line line2)//Heals line against enemy debuff
	{
		int modb = ((floor(min(99, level) * modifier)) * line2.debuff);
		for (int i = 0; i < line.size(); i++)
		{
			if (((target == line[i].getElement()) || (target == 'x')) && (line[i].tdefense > 0))
			{
				int moda = ((line[i].tdefense + modb ));
				line[i].tdefense = min(moda, line[i].getDefense());
			}
		}
	}
	debuff::debuff()//Debuff hero, bubbles/moak
	{
		//deliberately empty
	}
	debuff::debuff(const Mob& mob)
		: Mob(mob)
	{
	}
	debuff::debuff(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void debuff::skillFunction(Line& lane)
	{
	
			lane.debuff = modifier;
	}
	ratio::ratio()//ratio hero
	{
		//deliberately empty
	}
	ratio::ratio(const Mob& mob)
		: Mob(mob)
	{
	}
	ratio::ratio(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void ratio::skillFunction(Line& lane1, Line& lane2)//Reduces enemy hp by % * enemy modifier;
	{
		vector<Mob> line1 = lane1.getLine(), line2 = lane2.getLine();
		if (line2[0].getRarity() == 5)
		{
			return;
		}
		double percent = 1;
		double i = line1.size();
		double j = line2.size() + modifier;
		if (i < j)
		{

			percent = (i / j);
			for (int i = 0; i < line2.size(); i++)
			{
				int a = line2[i].tdefense;
				line2[i].tdefense *= (percent * lane2.debuff);
				int b = line2[i].tdefense;
				lane1.totaldamage += a - b;
			}
		}
		lane2 = line2;
	}
	evo::evo()//evo hero
	{
		//deliberately empty
	}
	evo::evo(const Mob& mob)
		: Mob(mob)
	{
	}
	evo::evo(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void evo::skillFunction()//Sets stats in battle * modifier
	{
		ratio = modifier;
		setStats();
	}
	paoe::paoe()//paoe hero
	{
		//deliberately empty
	}
	paoe::paoe(const Mob& mob)
		: Mob(mob)
	{
	}
	paoe::paoe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}

	void paoe::skillFunction(Line& line)//sets enemy hp * enemy debuff
	{
		vector<Mob> lane = line.getLine();
		for (int i = 0; i < lane.size(); i++)
		{
			lane[i].tdefense -= ((modifier * level) * line.debuff);
		}
		line = lane;
	}
	counter::counter()//counter hero
	{
		//deliberately empty
	}
	counter::counter(const Mob& mob)
		: Mob(mob)
	{
	}
	counter::counter(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void counter::skillFunction(int& damage)//sets attack to be returned
	{
		damage *= modifier;
	}
	ratk::ratk()//ratk hero
	{
		//deliberately empty
	}
	ratk::ratk(const Mob& mob)
		: Mob(mob)
	{
	}
	ratk::ratk(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void ratk::skillFunction(int seed)//Sets attack/defense according to seed
	{
		modifier = (seed % (static_cast<int>(modifier)) + 1);
		defense += modifier;
		attack += modifier;
	}
	rtrg::rtrg()//rtrg hero
	{
		//deliberately empty
	}
	rtrg::rtrg(const Mob& mob)
		: Mob(mob)
	{
	}
	rtrg::rtrg(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	int rtrg::skillFunction(Line& lane, int turns)//sets target of hero
	{

		vector<Mob> line = lane.getLine();
		vector <int> swaps(line.size());
		swaps.push_back(1);
		int x = (line.size());
		int *mapa;
		mapa = new int[x];
		int64_t seed = calcSeed(lane.lineIds, turns);
		for (int y = 0; y < x; y++)
		{
			seed = (9301 * seed + 49297) % 233280;
			double temp = seed;
			temp = temp / 233280;
			temp = temp * x;
			temp = int64_t(temp) | 0;
			mapa[y] = temp;
		}
		int j = x - 1;
		for (int i = j; i > 0; i--)
		{
			if (mapa[j - i] < 0)
			{
				mapa[j - i] = (mapa[j - i] + x);
			}
			swap(swaps[i], swaps[mapa[j - i]]);
		}
		int i = 0;
		int r = 0;
		for (i; i < swaps.size(); i++)
		{
			if (swaps[i] > 0)
				r = i;
		}
		delete[] mapa;
		return r;
	}
	rcrit::rcrit()//rcrit hero
	{
		//deliberately empty
	}
	rcrit::rcrit(const Mob& mob)
		: Mob(mob)
	{
	}
	rcrit::rcrit(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void rcrit::skillFunction(int seed)//determines crit
	{
		double a = 1;
		if ((seed % 2) == 0)
		{
			a = modifier;
		}
		typeadv = a;
	}
	moob::moob()//moob hero
	{
		//deliberately empty
	}
	moob::moob(const Mob& mob)
		: Mob(mob)
	{
	}
	moob::moob(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void moob::skillFunction(vector<Mob>& line)//damages enemy line
	{
		for (int i = 0; i < line.size(); i++)
			line[i].tdefense -= modifier;
	}
	tank::tank()//tank hero
	{
		//deliberately empty
	}
	tank::tank(const Mob& mob)
		: Mob(mob)
	{
	}
	tank::tank(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void tank::skillFunction(int& damage)//sets stats accordingly
	{
		tdefense -= (damage * modifier);
		damage -= (damage * modifier);
	}
	elem::elem()//elem hero
	{
		//deliberately empty
	}
	elem::elem(const Mob& mob)
		: Mob(mob)
	{
	}
	elem::elem(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void elem::skillFunction(Mob& targets)//sets typeadv if target is met
	{
		if (targets.getElement() == target)
		typeadv += modifier;
	}
	dampen::dampen()//dampen hero
	{
		//deliberately empty
	}
	dampen::dampen(const Mob& mob)
		: Mob(mob)
	{
	}
	dampen::dampen(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void dampen::skillFunction(int& damage)//sets damage to 0 if it's over 15000
	{
		if (damage > 15000)
			damage = 0;
	}
	explosion::explosion()//explosion hero
	{
		//deliberately empty
	}
	explosion::explosion(const Mob& mob)
		: Mob(mob)
	{
	}
	explosion::explosion(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void explosion::skillFunction(int& damage)//sets attack to be applied
	{
		damage = modifier;
	}
	leech::leech()//leech hero
	{
		//deliberately empty
	}
	leech::leech(const Mob& mob)
		: Mob(mob)
	{
	}
	leech::leech(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void leech::skillFunction(int& damage)//sets tdefense according to damage done
	{
		damage = tdefense + (modifier * damage);
	}
	evolve::evolve()//evolve hero
	{
		//deliberately empty
	}
	evolve::evolve(const Mob& mob)
		: Mob(mob)
	{
	}
	evolve::evolve(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void evolve::skillFunction(int& damage)//sets attack according to damage recieved
	{
		attack += modifier * damage;
	}
	anarchy::anarchy()//anarchy hero
	{
		//deliberately empty
	}
	anarchy::anarchy(const Mob& mob)
		: Mob(mob)
	{
	}
	anarchy::anarchy(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void anarchy::skillFunction(int& damage, Mob& targets)//sets targets defense - damage done * modifier
	{
		damage = damage * modifier;
	}
	amoob::amoob()//amoob hero
	{
		//deliberately empty
	}
	amoob::amoob(const Mob& mob)
		: Mob(mob)
	{
	}
	amoob::amoob(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void amoob::skillFunction(vector<Mob>& line)//sets enemy hp -damage
	{
		int damage = (level - 1) * modifier;
		for (int i = 0; i < line.size(); i++)
			line[i].tdefense -= damage;
	}
	otk::otk()//otk hero
	{
		//deliberately empty
	}
	otk::otk(const Mob& mob)
		: Mob(mob)
	{
	}
	otk::otk(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void otk::skillFunction(int& defense, Mob& targets, int& attack)//sets tdamage if kill condition is met
	{
		if ((targets.tdefense - attack) <= (defense * modifier))
			attack = max(targets.tdefense + 1, attack);
	}
	armor::armor()//armor hero
	{
		//deliberately empty
	}
	armor::armor(const Mob& mob)
		: Mob(mob)
	{
	}
	armor::armor(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void armor::skillFunction(int& damage)//adjusts attack according to skill
	{
		modifier *= (min(99, level) / 9.0);
		damage -= damage * modifier;
	}
	reflect::reflect()//reflect hero
	{
		//deliberately empty
	}
	reflect::reflect(const Mob& mob)
		: Mob(mob)
	{
	}
	reflect::reflect(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void reflect::skillFunction(int& damage, Line& line)//reflects aoe based on modifier and debuff
	{
		vector<Mob> lane = line.getLine();
		modifier = (modifier * (min(level, 99) / 3.0));
		damage *= modifier * line.debuff;
		for (int i = 0; i < lane.size(); i++)
			lane[i].tdefense -= damage;
		line = lane;
		
	}
	amplify::amplify()//amplify hero
	{
		//deliberately empty
	}
	amplify::amplify(const Mob& mob)
		: Mob(mob)
	{
	}
	amplify::amplify(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	int amplify::skillFunction(int& damage, Mob& targets)//increases attack based on targets defense
	{
		modifier *= (min(99, level) / 9.0);
		int amp = targets.tdefense * modifier;
		damage += amp;
		return damage;
	}
	guardian::guardian()//guardian hero
	{
		//deliberately empty
	}
	guardian::guardian(const Mob& mob)
		: Mob(mob)
	{
	}
	guardian::guardian(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void guardian::skillFunction(Line& line, Line& line2, int target)//sets line hps/defenses according to skills
	{
		vector<Mob> lane = line.getLine(), lane2 = line2.getLine();
		int modifierd =((modifier * (min(99, (level)) / 9.0)) * line2.debuff);
		int p = 1;
		if (promotion == 5)
			p = 1.1;
		int modifiera = (((modifier + p) * (min(99, (level - 1)) / 9.0)) * line2.debuff);
		for (int i = 0; i < lane.size(); i++)
		{
			if (lane[i].tdefense > 0)
				lane[i].tdefense = min(lane[i].tdefense + modifierd, lane[i].getDefense());
		}
		for (int i = 0; i < lane2.size(); i++)
		{
			lane2[i].tdefense -= modifiera;
		}
		lane[target].tdefense -= modifiera;
		line = lane, line2 = lane2;
	}
	posbonus::posbonus()//posbonus hero
	{
		//deliberately empty
	}
	posbonus::posbonus(const Mob& mob)
		: Mob(mob)
	{
	}
	posbonus::posbonus(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void posbonus::skillFunction(vector<Mob>& line)//increases attack and defense by units behind
	{
		int i = 0;
		while (line[i].getSkillName() != "posbonus")
			i++;
		int j = (line.size() - 1);
		i = j - i;
		modifier *= i;
		attack += modifier;
		defense += modifier;
	}
	aposbonus::aposbonus()//aposbonus hero
	{
		//deliberately empty
	}
	aposbonus::aposbonus(const Mob& mob)
		: Mob(mob)
	{
	}
	aposbonus::aposbonus(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void aposbonus::skillFunction(vector<Mob>& line)//sets attack/defense based on units behind
	{
		int i = 0;
		while (line[i].getSkillName() != "aposbonus")
			i++;
		int j = (line.size() - 1);
		i = j - i;
		modifier = round(modifier * level * i);
		attack += modifier;
		defense += modifier;
	}
	friends::friends()//friends hero
	{
		//deliberately empty
	}
	friends::friends(const Mob& mob)
		: Mob(mob)
	{
	}
	friends::friends(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void friends::skillFunction(vector<Mob>& line, int mob)//heals/increases attack of other units
	{
		int j = mob;
		for (int i = 0; i < line.size(); i++)
		{
			if (i != j)
			{
				int k = line[i].getAttack();
				int moda = attack * modifier;
				int m = k + moda;
				line[i].setAttack(m);
				if (line[i].tdefense >= 0)
				line[i].tdefense += (defense * modifier);
			}
		}
	}
	voids::voids()//void hero
	{
		//deliberately empty
	}
	voids::voids(const Mob& mob)
		: Mob(mob)
	{
	}
	voids::voids(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void voids::skillFunction(Mob& targets)//Increases type effectiveness if enemy is not void
	{
		if (targets.getElement() != 'v')
			typeadv += modifier;
	}
	bday::bday()//bday hero
	{
		//deliberately empty
	}
	bday::bday(const Mob& mob)
		: Mob(mob)
	{
	}
	bday::bday(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void bday::skillFunction(Line& line)//damages last enemy in the line
	{
		vector<Mob> lane = line.getLine();
		int moda = ((attack * modifier) * line.debuff);
		int i = lane.size() - 1;
		lane[i].tdefense -= moda;
		line = lane;
	}
	infiltered::infiltered()//infiltered hero
	{
		//deliberately empty
	}
	infiltered::infiltered(const Mob& mob)
		: Mob(mob)
	{
	}
	infiltered::infiltered(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest)
		:Mob(leveln, rarity, baseAttack, baseDefense, name, skillname, element, id, prom1, prom2, prom4, prom5, modifier, target, weakness, quest)
	{
		//deliberately empty
	}
	void infiltered::skillFunction(Line& lane, Line& lane2)//damages both lanes
	{
		vector<Mob> line1 = lane.getLine();
		vector<Mob> line2 = lane2.getLine();
		int x = (tdamage * modifier);
		int y = ((tdamage * modifier) * lane2.debuff);
		for (int i = 1; i < line1.size(); i++)
			line1[i].tdefense -= x;
		for (int i = 0; i < line2.size(); i++)
			line2[i].tdefense -= y;
		lane = line1;
		lane2 = line2;
	}
	int64_t calcSeed(vector<int> ids, int turns)
	{
		int64_t seed = 1;
		for (int i = 0; i < ids.size(); ++i)
		{
			seed = ((seed*abs(ids[i])) + 1) % 2147483647;
		}
		for (int i = 0; i < turns; ++i)
		{
			seed = (seed * 16807) % 2147483647;
		}
		return seed;
	}
	void Line::setLineBIds()
	{
		int e = lineIds.size();
		vector<int> v = lineIds;
		for (int i = 0; i < e; i++)
		{
			if (v[i] == -1)
			{
				v.erase(v.begin() + i);
				v.insert(v.begin(), -1);
				v.resize(6);
			}
		}
	}
	 int doBattle(Line line1, Line line2)//does battle between the grids
	 {
		 line2.setLineBIds();
		 line1.setStats(); line2.setStats();
		 vector<int> ids2 = line2.lineIds;
		 vector<int> ids = line1.lineIds;
		 int turns = 100;
		 int64_t seedA = 0, seedB = 0;
		 seedA = calcSeed(line2.lineIds, turns);
		 seedB = calcSeed(line1.lineIds, turns);
		 vector<Mob> lane = line1.getLine();
		 for (int i = 0; i < line1.getLine().size(); i++)
		 {
			 lane[i].tdefense = lane[i].getDefense();
		 }
		 line1 = lane;
		 vector<Mob> lane2 = line2.getLine();
		 for (int i = 0; i < line2.getLine().size(); i++)
		 {

			 lane2[i].tdefense = lane2[i].getDefense();
		 }
		 line2 = lane2;
		 while (anyDead(lane, lane2))
		 {
			 killUnits(line1, line2);
			 killUnits(line2, line1);
			 lane = line1.getLine(); lane2 = line2.getLine();

		 }
		 if (bubbles(line1))
		 {
			 vector<Mob> lane = line1.getLine();
			 int j = 0;
			 for (int i = 0; i < lane.size(); i++)
			 if (lane[i].getSkillName() == "debuff")
				 j = i;
			 debuff b(lane[j]);
			 b.skillFunction(line1);
		 }
		 if (bool(bubbles(line2)))
		 {
			 vector<Mob> lane = line2.getLine();
			 int j = 0;
			 for (int i = 0; i < lane.size(); i++)
				 if (lane[i].getSkillName() == "debuff")
					 j = i;
			 debuff b(lane[j]);
			 b.skillFunction(line2);
		 }
		 line1.lineIds = ids;
		 line2.lineIds = ids2;
		 calcTurn0(line1, line2, seedB);
		 lane = line1.getLine();
		 line1.lineIds = ids;
		 line2.lineIds = ids2;
		 calcTurn0(line2, line1, seedA);
		 lane2 = line2.getLine();
		 while (anyDead(lane, lane2))
		 {
			 killUnits(line1, line2);
			 killUnits(line2, line1);
			 lane = line1.getLine(); lane2 = line2.getLine();
		 }
		 turns--;
		 while ((isAlive(line1) && isAlive(line2)) && (turns > 0))
		 {
			 line1.debuff = 0;
			 line2.debuff = 0;
			 if (bubbles(line1))
			 {
				 vector<Mob> lane = line1.getLine();
				 int j = 0;
				 for (int i = 0; i < lane.size(); i++)
					 if (lane[i].getSkillName() == "debuff")
						 j = i;
				 debuff b(lane[j]);
				 b.skillFunction(line1);
			 }
			 if (bubbles(line2))
			 {
				 vector<Mob> lane = line2.getLine();
				 int j = 0;
				 for (int i = 0; i < lane.size(); i++)
					 if (lane[i].getSkillName() == "debuff")
						 j = i;
				 debuff b(lane[j]);
				 b.skillFunction(line2);
			 }
			 line1.lineIds = ids;
			 line2.lineIds = ids2;
			 calcTurn(line1, line2, calcSeed(line2.lineIds, turns), turns);
			 line1.lineIds = ids;
			 line2.lineIds = ids2;
			 calcTurn(line2, line1, calcSeed(line1.lineIds, turns), turns);
			 line1.lineIds = ids;
			 line2.lineIds = ids2;
			 doTurn(line1, line2, turns);
			 line1.lineIds = ids;
			 line2.lineIds = ids2;
			 doTurn(line2, line1, turns);
			 do {
				 killUnits(line1, line2);
				 killUnits(line2, line1);
				 lane = line1.getLine(); lane2 = line2.getLine();
				} while (anyDead(lane, lane2));
			 turns--;
		 }
		 return isAlive(line1);
	 }
	 void calcTurn0(Line& linea, Line& lineb, int64_t seed)
	 {
		 vector<Mob> a = linea.getLine();
		 vector<Mob> c = lineb.getLine();
		 for (int i = 0; i < a.size(); i++)
		 {
			 Mob b = a[i];
			 Mob d = c[0];
			 string sklnme = b.getSkillName();
			 if (sklnme == "paoe" || sklnme == "ratio")
			 {
				 if (sklnme == "paoe")
				 {
					 paoe b(a[i]);
					 b.skillFunction(lineb);
					 c = lineb.getLine();
				 }
				 else if (sklnme == "ratio")
				 {
					 ratio b(a[i]);
					 b.skillFunction(linea, lineb);
					 c = lineb.getLine();
				 }
			 }
			 else if (sklnme == "posbonus" || sklnme == "aposbonus")
			 {
				 if (sklnme == "posbonus")
				 {
					 posbonus b(a[i]);
					 b.skillFunction(a);
					 a[i] = b;
				 }
				 else if (sklnme == "aposbonus")
				 {
					 aposbonus b(a[i]);
					 b.skillFunction(a);
					 a[i] = b;
				 }
			 }
			 else if (sklnme == "def")
			 {
				 def b(a[i]);
				 b.skillFunction(a);
			 }
			 else if (sklnme == "dmg")
			 {
				 dmg b(a[i]);
				 b.skillFunction(a[0]);
			 }
			 else if (sklnme == "mon")
			 {
				 mon b(a[i]);
				 b.skillFunction(a);
				 a[i] = b;
			 }
			 else if (sklnme == "rainbow")
			 {
				 rainbow b(a[i]);
				 b.skillFunction(a);
				 a[i] = b;
			 }
			 else if (sklnme == "buffatk")
			 {
				 buffatk b(a[i]);
				 b.skillFunction(a[0]);
			 }
			 else if (sklnme == "buffdef")
			 {
				 buffdef b(a[i]);
				 b.skillFunction(a);
				 b = a[i];
				 a[i] = b;
			 }
			 else if (sklnme == "debuff")
			 {
				 debuff b(a[i]);
				 b.skillFunction(linea);
			 }
			 else if (sklnme == "evo")
			 {
				 evo b(a[i]);
				 b.skillFunction();
				 a[i] = b;
			 }
			 else if (sklnme == "ratk")
			 {
				 ratk b(a[i]);
				 b.skillFunction(seed);
				 a[i] = b;
			 }
			 else if (sklnme == "elem")
			 {
				 elem b(a[i]);
				 b.skillFunction(d);
				 a[i] = b;
			 }
			 else if (sklnme == "dampen")
			 {
				 dampen b(a[i]);
				 b.skillFunction(d.tdamage);
				 c[0] = d;
			 }
		 }
		 linea = a;
		 lineb = c;
	 }
	 void doTurn(Line& LineA, Line& LineB, int turns)
	 {
		 vector<Mob> a = LineA.getLine(), b = LineB.getLine();
		 int attack = a[0].tdamage, target = 0, atotaldamage = LineA.totaldamage, btotaldamage = LineB.totaldamage;
		 int cDamage = LineB.cDamage, dDamage = LineA.cDamage;
		 int aDamage = LineA.aDamage, bDamage = LineB.aDamage, adebuff = LineA.debuff, bdebuff = LineB.debuff;
		 Mob A = a[0];
		 string v = A.getSkillName();
		 if (v == "rtrg")
		 {
			 rtrg A(a[0]);
			 target = A.skillFunction(LineB, turns) - 1;
		 }
		 Mob B = b[target];
		 B.tarmor = b[target].tarmor;
		 string w = B.getSkillName();
		 char e = B.getWeakness(), t = A.getElement();
		 int basehp = B.getDefense();
		 if ( (e == t) && (v != "purity") && (v != "elem") && (v != "rcrit"))
			 A.typeadv += .5;
		 if (( v == "amplify" ) && (B.getRarity() != 4))
		 {
			 amplify A(a[0]);
			 A.skillFunction(attack,B);
		 }
		 A.tdamage = attack;
		 int eatk = A.tdamage;
		 attack = max(0, (static_cast<int>(A.tdamage * A.typeadv) - B.tarmor));
		 int rattack = attack;
		 if (w == "armor")
		 {
			 armor B(b[0]);
			 B.skillFunction(attack);
		 }
		 int catk = 0;
		 if (neil(LineB))
		 {
			 if (target == 0)
			 {
				 int n = 0;
				 for (int i = 0; i < b.size(); i++)
				 {
					 if (b[i].getSkillName() == "tank")
						 n = i;
				 }
				 tank B(b[n]);
				 int d1 = B.tdefense;
				 B.skillFunction(attack);
				 int d2 = B.tdefense;
				 if (n == (b.size() - 1))
				 atotaldamage += d1 - d2;
				 b[n] = B;
				 B = b[target];
			 }
		 }
		 if (v == "otk")
		 {
			 otk A(a[0]);
			 A.skillFunction(basehp,B, attack);
		 }
		 if (w == "dampen")
		 {
			 dampen B(b[0]);
			 B.skillFunction(attack);
		 }
		 B.tdefense -= attack;
		 attack = rattack;
		 b[target] = B;
		 for (int i = 0; i < b.size(); i++)
		 {
			 b[i].tarmor = 0;
		 }
		 LineB = b;
		 LineB.debuff = bdebuff;
		 if (v == "rico")
		 {
			 rico A(a[0]);
			 A.skillFunction(LineB, rattack);
			 b = LineB.getLine();
			 LineB.debuff = bdebuff;
			 B = b[target];
		 }
		 if (v == "bday")
		 {
			 bday A(a[0]);
			 A.skillFunction(LineB);
			 b = LineB.getLine();
			 LineB.debuff = bdebuff;
			 B = b[target];
		 }
		 else if (v == "buff")
		 {
			 buff A(a[0]);
			 A.skillFunction();
			 a[0] = A;
		 }
		 for (int i = 0; i < a.size(); i++)
		 {
			 if (a[i].getSkillName() == "aoe")
			 {
				 aoe A(a[i]);
				 A.skillFunction(LineB, LineA);
				 b = LineB.getLine();
				 LineB.debuff = bdebuff;
				 B = b[target];
			 }
			 else if (a[i].getSkillName() == "buffaoe")
			 {
				 buffaoe A(a[i]);
				 A.skillFunction(LineB, LineA);
				 b = LineB.getLine();
				 LineB.debuff = bdebuff;
				 B = b[target];
			 }
		 }
		 if (v == "infiltered")
		 {
			 infiltered A(a[0]);
			 A.tdamage = attack;
			 A.skillFunction(LineA, LineB);
			 LineA.debuff = adebuff, LineB.debuff = bdebuff;
			 b = LineB.getLine();
			 a = LineA.getLine();
			 B = b[target];
		 }
		 if ((v == "leech") && (A.tdefense > 0))
		 {
			 leech A(a[0]);
			 A.skillFunction(attack);
			 A.tdefense = attack;
			 a[0] = A;
		 }
		 for (int i = 0; i < a.size(); i++)
		 {
			 string x = a[i].getSkillName();
			 if (x == "turna")
			 {
				 turna A(a[i]);
				 A.skillFunction(LineA);
				 a[i] = A;
			 }
		 }
		 if (Gaia(LineB))
		 {
			for (int i = 0; i < b.size(); i++)
			{
				w = b[i].getSkillName();
				if (w == "ban")
				{
					ban B(b[i]);
					B.skillFunction(LineB);
					b[i] = B;
					LineB = b;
					LineB.debuff = bdebuff;
				}
			 }
		 }
		 for (int i = 0; i < b.size(); i++)
		 {
			 string w = b[i].getSkillName();
			 if (w == "buffahe")
			 {
				 a[0] = A;
				 LineA = a;
				 LineA.debuff = adebuff;
				 b[target] = B;
				 LineB = b;
				 LineB.debuff = bdebuff;
				 buffahe B(b[i]);
				 B.skillFunction(LineA, LineB);
				 a = LineA.getLine();
				 b = LineB.getLine();
				 B = b[target];
			 }
		 }
			 for (int i = 0; i < b.size(); i++)
			 {
				 if (b[i].getSkillName() == "heal")
				 {
					 heal B(b[i]);
					 B.skillFunction(b, LineA);
					 LineB = b;
					 LineB.debuff = bdebuff;
					 B = b[i];
				 }
				 else if (b[i].getSkillName() == "buffheal")
				 {
					 buffheal B(b[i]);
					 B.skillFunction(b, LineA);
					 LineB = b;
					 LineB.debuff = bdebuff;
					 B = b[target];
				 }
				 else if (b[i].getSkillName() == "guardian")
				 {
					 guardian B(b[i]);
					 LineB = b, LineA = a;
					 LineB.debuff = bdebuff, LineA.debuff = adebuff;
					 B.skillFunction(LineB, LineA, target);
					 b = LineB.getLine();
					 a = LineA.getLine();
					 B = b[target];
				 }

			 }
			 if (w == "anarchy")
			 {
				 anarchy B(b[target]);
				 B.skillFunction(attack, B);
				 bDamage = attack;
			 }			 
			 if (w == "counter")
			 {
				 catk = attack;
				 counter B(b[target]);
				 B.skillFunction(catk);
				 btotaldamage += catk;
			 }
			 else if (w == "reflect")
			 {
				 reflect B(b[target]);
				 B.skillFunction(attack, LineA);
				 for (int i = 0; i < a.size(); i++)
				 {
					 a[i].tdefense -= attack;
					 btotaldamage += attack;
				 }
			 }
			 if (((v == "moob") || (v == "amoob")) && (B.tdefense <= 0))
			 {
				 if (v == "moob")
				 {
					 moob A(a[0]);
					 A.skillFunction(b);
				 }
				 else if (v == "amoob")
				 {
					 amoob A(a[0]);
					 A.skillFunction(b);
				 }
				 LineB = b;
				 LineB.debuff = bdebuff;
			 }
			 if (w == "evolve")
			 {
				 evolve B(b[target]);
				 B.skillFunction(eatk);
				 b[target] = B;
				 LineB = b;
				 LineB.debuff = bdebuff;
			 }
			 A = a[0];
			 A.typeadv = 1;
			 a[0] = A;
			 LineA = a;
			 LineA.debuff = adebuff;
			 LineA.aDamage = aDamage;
			 LineB.cDamage = catk;
			 LineA.cDamage = dDamage;
			 LineB.aDamage = bDamage;
			 LineB.totaldamage += btotaldamage;
			 LineA.totaldamage += attack + atotaldamage;
			 LineB.getLine()[target] = B;
	 }
	 bool neil(Line line)//checks if neil is in the line
	 {
		 vector<Mob> lane = line.getLine();
		 for (int i = 0; i < lane.size(); i++)
		 {
			 if ((lane[i].getSkillName() == "tank") && ( i != 0))
				 return true;
		 }
		 return false;
	 }
	 bool bubbles(Line line)//checks if bubbles is in the line
	 {
		 vector<Mob> lane = line.getLine();
		 for (int i = 0; i < lane.size(); i++)
		 {
			 if ((lane[i].getSkillName() == "debuff") && (i != 0))
				 return true;
			 else
				 return false;
		 }
	 }
	 bool Gaia(Line line)//checks if gaia is in the line
	 {
		 vector<Mob> lane = line.getLine();
		 for (int i = 0; i < lane.size(); i++)
		 {
			 if (lane[i].getSkillName() == "ban")
				 return true;
			 else
				 return false;
		 }
	 }
	 void killUnits(Line& line, Line& line2)//removes dead units
	 {
		 vector<Mob> lane = line.getLine();
		 int cDamage = line2.cDamage, cDamage1 = line.cDamage;
		 int aDamage = line2.aDamage, aDamage1 = line.aDamage;
		 vector<Mob> lane2 = line2.getLine();
		 int totaldamage = line.totaldamage;
			 for (int i = 0; i < lane.size(); i++)
			 {
				 string v = lane[i].getSkillName();
				 if (v == "counter")
				 {
					 for (int i = 0; i < lane2.size(); i++)
					 {
						 if (lane2[i].tdefense > 0)
						 {
							 lane2[i].tdefense -= line.cDamage;
							 line2 = lane2;
							 line2.cDamage = cDamage;
							 line2.aDamage = aDamage;
							 line.cDamage = 0;
							 break;
						 }
					 }
				 }
				 if ((v == "anarchy") && (lane2.size() != 0))
				 {
					 int maxhp = 0;
					 for (int i = 0; i < lane2.size(); i++)
					 {
						 if (lane2[maxhp].tdefense < lane2[i].tdefense)
						 {
							 maxhp = i;
							 i = 0;
						 }
					 }
					 lane2[maxhp].tdefense -= line.aDamage;
					 line2 = lane2;
					 line2.cDamage = cDamage;
					 line2.aDamage = aDamage;
					 line.aDamage = 0;

				 }
				 if (lane[i].tdefense <= 0)
				 {
					 if (v == "explosion")
					 {
						 explosion B(lane[i]);
						 int attack = 0;
						 B.skillFunction(attack);
						 for (int i = 0; i < lane2.size(); i++)
						 {
							 if (lane2[i].tdefense > 0)
							 {
								 lane2[i].tdefense -= attack;
								 line.totaldamage += attack;
								 line2 = lane2;
								 line2.aDamage = aDamage;
								 line2.cDamage = cDamage;
							 }
						 }
					 }
					 else if (v == "boom")
					 {
						 boom B(lane[i]);
						 B.skillFunction(line2, line);
						 lane = line.getLine();
						 lane2 = line2.getLine();
						 line2 = lane2;
						 line2.aDamage = aDamage;
						 line2.cDamage = cDamage;
					 }
					 else if (v == "friends")
					 {
						 friends B(lane[i]);
						 B.skillFunction(lane, i);
						 line = lane;
						 line.aDamage = aDamage1;
						 line.cDamage = cDamage1;
						 
					 }
				 }
			 }
			 int i = 0;
		 for ( i; i < lane.size(); i++)
		 {
			 if (lane[i].tdefense <= 0)
			 {
				 lane.erase(lane.begin() + i);
				 i = -1;
			 }
		 }
		 line = lane;
		 line.cDamage = cDamage1;
		 line.aDamage = aDamage1;
		 line2 = lane2;
		 line2.cDamage = cDamage;
		 line2.aDamage = aDamage;
		 line.totaldamage = totaldamage;
	 }
	 bool isAlive(Line line)//Checks to see if line is alive
	 {
		 vector<Mob> lane = line.getLine();
	     if (lane.size() == 0)
			 return false;
		 else 
			 return true;

	 }
	 void calcTurn(Line& LineA, Line& LineB, int64_t seed, int turns)//Sets buffs
	 {
		 vector<Mob> line1 = LineA.getLine(), line2 = LineB.getLine();
		 Mob A = line1[0], B = line2[0];
		 string v = A.getSkillName();
		 for (int i = 0; i < line1.size(); i++)
		 {
			 line1[i].tdamage = line1[i].getAttack();
			 line1[i].tarmor = 0;
		 }
		 if (v == "purity")
		 {
			 purity A(line1[0]);
			 A.skillFunction(B);
			 line1[0] = A;
		 }
		 else  if (v == "void")
		 {
			 voids A(line1[0]);
			 A.skillFunction(B);
			 line1[0] = A;
		 }
		 else if (v == "elem")
		 {
			 elem A(line1[0]);
			 A.skillFunction(B);
			 line1[0] = A;
		 }
		 else if (v == "rcrit")
		 {
			 rcrit A(line1[0]);
			 A.skillFunction(seed);
			 line1[0] = A;
		 }
		 for (int i = 0; i < line1.size(); i++)
		 {
			 Mob a = line1[i];
			 string y = line1[i].getSkillName();
			 if (y == "def")
			 {
				 def A(a);
				 A.skillFunction(line1);
			 }
			 else if (y == "dmg")
			 {
				 dmg A(a);
				 A.skillFunction(line1[0]);
			 }
			 else if (y == "buffatk")
			 {
				 buffatk A(a);
				 A.skillFunction(line1[0]);
			 }
			 else if (y == "buffdef")
			 {
				 buffdef A(a);
				 A.skillFunction(line1);
			 }
			 else if (y == "extra")
			 {
				 extra A(a);
				 A.skillFunction(line1);
			 }
			 else if (y == "buffboth")
			 {
				 buffboth A(a);
				 A.skillFunction(line1);
			 }

		 }
		 LineA = line1;
	 }
	 bool anyDead(vector<Mob> line, vector<Mob> line2)
	 {
		 for (int i = 0; i < line.size(); i++)
		 {
			 if (line[i].tdefense <= 0)
				 return true;
		 }
		 for (int i = 0; i < line2.size(); i++)
		 {
			 if (line2[i].tdefense <= 0)
				 return true;
		 }
		 return false;
	 }
//jmcclain1299
void getResult(list<Mob> heat, Line selfl, int upperlimit, int lowerlimit, Line enemyl)
{
	list<Mob>::iterator j = heat.begin(), k = heat.begin(), l = heat.begin(), m = heat.begin(),//iterators for iteratiing through the list
		n = heat.begin(), o = heat.begin(), oe = heat.end(), me = heat.end(), ne = heat.end(),
		le = heat.end(), ke = heat.end(), je = heat.end();//end iterators are for a stopping condition
	je--, ke--, oe--, me--, ne--, le--; //pointing the iterators the last mob, a few steps faster than ending all the for loops
	j++;//priming j
	vector<Mob> self = { *j, *k, *l, *m, *n, *o };//first combination
	string dup = "nop";//to check for duplicate hero, an invalid condition
	string won = "no";//a flag for stopping, will optimize at a later point
	char ans = 'y';//to continue iteration to 5/6 mobs
	int a = 1, b = 1;//a flag to determing if the user wanted to continue or not
	for (o; o != heat.end();)//self[6] iterator
	{
		for (n; n != heat.end();)//self[5] iterator
		{
			for (m; m != heat.end();)//self[4] iterator
			{
				for (l; l != heat.end();)//self[3] iterator
				{
					for (k; k != heat.end();)//self[2] iterator
					{
						for (j; j != heat.end();)//self[1] iterator
						{
						redo: //a flag to restart the sequence if a duplicate was found
							self = { *j, *k, *l, *m, *n, *o }; // creats a vector out of the iterated mobs
							if (self[0].getId() < -1) //if the 1st index is a hero
							{
								if (j == k || j == l || j == m || j == n || j == o)//if the id matches any others, same as asking if the iterators are pointing at the same thing
								{
									j++;//move to next mob in the list
									if (j == heat.end())//if j is at the end, move out of this for loop into the next one, incrementing the k iterator up one
										break;
									goto redo;//try again from the redo flag
								}
								if (self[1].getId() < -1)//if k points at a hero
									if (k == l || k == m || k == n || k == o)//if k is equal to another iterator, meaning same hero is referenced...
									{
										k++;//move k iterator up...
										if (k == heat.end())
											goto donek;// move k/l iterators up, and tryagain if k's not done
										goto redo;
									}
								if (self[2].getId() < -1)//same thing for l
									if (l == m || l == n || l == o)
									{
										l++;
										if (l == heat.end())
											goto donel;
										goto redo;
									}
								if (self[3].getId() < -1)//same for m
									if (m == n || m == o)
									{
										m++;
										if (m == heat.end())
											goto donem;
										goto redo;
									}
								if (self[4].getId() < -1)//same for n
									if (n == o)
									{
										n++;
										if (n == heat.end())
											goto donen;
										goto redo;
									}
							}
							if (((selfl.lineFollowers < upperlimit) && (selfl.lineFollowers > lowerlimit)) || (selfl.lineFollowers == 0))//if the line is within the paramaters for upper and lower limits
							{
								selfl = self;//make a line out of the self vector
								if (doBattle(selfl, enemyl))//Returns 1 if the first line is alive and the second one is not, which is the only winning condition I am concerned with for this exercise. 
								{
									doBattle(selfl, enemyl);
									won = "won";//flag that a battle has been one. This will be optimized later with a goto flag
									break;
								}
							}
							j++;//increments j up if the battle isn't won
						}
						if (won == "won")
							break;
						if (j == heat.end())//resets j
							j = heat.begin();
						do {

							dup = "nop";//flag to restart the do loop if k is a duplicate 
							k++;
							if (k != heat.end())//to make sure that nothing is broken
								self[1] = *k;
							if (self[1].getId() < -1)//check for duplications
							{
								if (k == l || k == m || k == n || k == o)
									dup = "dup";//sets flag if duplicate
							}
							if (k == heat.end())//if k's done, reset it and increment l
							{
								k = heat.begin();
								goto donek;
							}
						} while (dup == "dup");//while condintion is invalid
					}
				donek://same thing as k, but for l
					if (won == "won")
						break;
					if (k == heat.end())
						k = heat.begin();
					do {
						l++;
						dup = "nop";
						if (l != heat.end())
							self[2] = *l;
						if (self[2].getId() < -1)
						{
							if (l == m || l == n || l == o)
								dup = "dup";
						}
						if (l == heat.end())
						{
							l = heat.begin();
							goto donel;
						}
					} while (dup == "dup");
				}
			donel://same for m
				if (won == "won")
					break;
				if (l == heat.end())
					l = heat.begin();
				do {
					m++;
					dup = "nop";
					if (m != heat.end())
						self[3] = *m;
					if (self[3].getId() < -1)
					{
						if (m == n || m == o)
							dup = "dup";
					}
					if (m == heat.end())
					{
						m = heat.begin();
						if (n == heat.end())//minor optimization to cut out a few steps if these conditions had already been met.
						{
							n == heat.begin();
							goto donen;
							if (o == heat.end())
								goto doneo;
						}
						goto donem;//incremement n...
						break;
					}
				} while (dup == "dup");
			}
		donem://same for m, but now for n
			if (ans == 'n')
				break;
			if (won == "won")
				break;
			if (a == 0)// a check for increasing the difficulty of solution and decreasing of rewards.
			{
				cout << "Couldn't find a solution for a line of 4 mobs.\n"
					"Would you like to continue?[y/n]\n";
				cin >> ans;
				if (ans == 'n')
				{
					a = 1;
					break;
				}
				a = 1;//either way, the player doesn't need to be asked if they want to continue on every loop, there are a few hundred thousand per heat
			}
			if (m == heat.end())
				m = heat.begin();
			do {
				n++;
				dup = "nop";
				if (n != heat.end())
					self[4] = *n;
				if (self[4].getId() < -1)
				{
					if (n == o)
						dup = "dup";
				}
				if ((n == heat.end()) && (dup == "dup"))
				{
					n = heat.begin();
					goto donen;
				}
			} while (dup == "dup");
		}
	donen://same as n, now for o
		if (won == "won")
			break;
		if (ans == 'n')
			goto doneo;
		if (b == 0)//again, a check to move onto increased difficulty with decreased rewards
		{
			cout << "Couldn't find a solution for a line of 5 mobs.\n"
				"Would you like to continue?[y/n]\n";
			cin >> ans;
			if (ans == 'n')
			{
				b = 1;
				goto doneo;
			}
			b = 1;
		}
		if ((o == oe) && (m == me) && (n == ne) && (l == le) && (k == ke) && (j == je))//if everything is pointing to the last valid combination, move on
			break;
		if (won == "won")
			break;
		if (n == heat.end())
			n = heat.begin();
		o++;
	}
doneo://once done trying all solutions/finding a winning solution

	if (won == "no")
		cout << "No winning combination found";//informs the player no solution was found
	for (int i = 0; i < self.size(); i++)
	{
		if (self[i].getName() == "null")//removes "blank" mobs from the line. they have a use with certain heroes, but the player doesn't need to see them/won't understand them at this current point. if the game is updated to include different heroes that requires this, the change will be made
		{
			self.erase(self.begin() + i);
			i = 0;
		}
	}
	if (won == "won")//gives a readout of the winning mobs in an order the player will understand
	{
		cout << "Winning line found.\n";
		for (int i = (self.size() - 1); i > -1; i--)
		{
			cout << self[i].getName();
			if (i == 0)
				break;
			cout << ", ";
		}
	}
	cout << endl;
	stringstream x;
	vector<Mob> v = selfl.getLine();
	vector<Mob> h;
	vector<Mob> e = enemyl.getLine();
	vector<Mob> eh;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getSkillName() != "mob")
			h.push_back(v[i]);
	}
	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].getSkillName() != "mob")
			eh.push_back(e[i]);
	}

	x << "{\"setup\":[";
	for (int i = 0; i < selfl.lineIds.size(); i++)
	{
		x << selfl.lineIds[i];
		if (i < selfl.lineIds.size() - 1)
			x << ",";
	}
	x << "],\"shero\":{";
	for (int i = 0; i < h.size(); i++)
	{
		x << "\"" << (abs(h[i].getId()) - 2) << "\":" << h[i].getLevel();
		if (i != h.size() - 1)
			x << ",";
	}
	x << "},\"spromo\":{";
	for (int i = 0; i < h.size(); i++)
	{
		x << "\"" << (abs(h[i].getId()) - 2) << "\":" << h[i].getPromotion();
		if (i != h.size() - 1)
			x << ",";
	}
	x << "},\"player\":[";
	for (int i = 0; i < enemyl.lineIds.size(); i++)
	{
		x << enemyl.lineIds[i];
		if (i < enemyl.lineIds.size() - 1)
			x << ",";
	}
	x << "],\"phero\":{";
	for (int i = 0; i < eh.size(); i++)
	{
		x << "\"" << (abs(eh[i].getId()) - 2) << "\":" << eh[i].getLevel();
		if (i != eh.size() - 1)
			x << ",";
	}
	x << "},\"ppromo\":{";
	for (int i = 0; i < eh.size(); i++)
	{
		x << "\"" << (abs(eh[i].getId()) - 2) << "\":" << eh[i].getPromotion();
		if (i != eh.size() - 1)
			x << ",";
	}
	x << "}}";
	string unencoded = x.str();
	string y = base64_encode((const unsigned char*)unencoded.c_str(), (int)unencoded.size());
	ostringstream xy;
	xy << "{\"validSolution\" : {\"target\":{\"followers\":" << enemyl.lineFollowers << ",\"monsters\":[";
	for (int i = 0; i < e.size(); i++)
	{
		xy << "{\"id\":" << e[i].getId();
		if (e[i].getId() < -1)
			xy << ",\"level\":" << e[i].getLevel();
		xy << "}";
		if (i < e.size() - 1)
			xy << ",";
	}
	xy << "]},\"solution\":{\"followers\":" << selfl.lineFollowers << ",\"monsters\":[{";
	for (int i = 0; i < v.size(); i++)
	{
		xy << "{\"id\":" << v[i].getId();
		if (v[i].getId() < -1)
			xy << ",\"level\":" << v[i].getLevel();
		xy << "}";
		if (i < v.size() - 1)
			xy << ",";
	}
	xy << "]},\"time\":0,\"fights\":0,\"replay\":\"" << y << "\"}}";
	cout << xy.str();
	cout << endl;
}
string base64_encode(BYTE const* buf, unsigned int bufLen) {
	std::string ret;
	int i = 0;
	int j = 0;
	BYTE char_array_3[3];
	BYTE char_array_4[4];

	while (bufLen--) {
		char_array_3[i++] = *(buf++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}

	return ret;
}
void getPromotional(list<Mob> heat, Line selfl, int upperlimit, int lowerlimit, Line enemyl, int id)
{
	list<Mob>::iterator j = heat.begin(), k = heat.begin(), l = heat.begin();
	k++, l++, l++;
	vector<Mob> self = { *j, *k, *l };
	string won = "no";
	for (l; l != heat.end();)
	{
		for (k; k != heat.end();)
		{
			for (j; j != heat.end();)
			{
			redo:
				if (j == heat.end())
					goto donej;
				self = { *j, *k, *l };
				if ((self[0].getId() != id) && (self[1].getId() != id) && (self[2].getId() != id))
				{
					j++;
					goto redo;
				}
				if (self[0].getId() < -1)
				{
					if (j == k || j == l)
						goto redo;
				}
				if (self[1].getId() < -1)
				{
					if (k == l)
					{
						k++;
						if (k == heat.end())
							goto donek;
						goto redo;
					}
				}
				selfl = self;
				if (doBattle(selfl, enemyl))
				{
					won = "won";
					goto donel;
				}
			}
		donej:
			j = heat.begin();
		redok:
			k++;
			if (k == heat.end())
				goto donek;
			else self[1] = *k;
			if (self[1].getId() < -1)
			{
				if (k == l)
					goto redok;
			}
		}
	donek:
		k = heat.begin();
		l++;
		if (l == heat.end())
			cout << "No winning line found for this promotion attempt";
	}
donel:
	if (won == "won")
	{
		cout << "Winning line found\n";
		for (int i = (self.size() - 1); i > -1; i--)
		{
			cout << self[i].getName();
			if (i == 0)
				break;
			cout << ", ";
		}
	}
	cout << endl;
	stringstream x;
	vector<Mob> v = selfl.getLine();
	vector<Mob> h;
	vector<Mob> e = enemyl.getLine();
	vector<Mob> eh;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getSkillName() != "mob")
			h.push_back(v[i]);
	}
	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].getSkillName() != "mob")
			eh.push_back(e[i]);
	}

	x << "{\"setup\":[";
	for (int i = 0; i < selfl.lineIds.size(); i++)
	{
		x << selfl.lineIds[i];
		if (i < selfl.lineIds.size() - 1)
			x << ",";
	}
	x << "],\"shero\":{";
	for (int i = 0; i < h.size(); i++)
	{
		x << "\"" << (abs(h[i].getId()) - 2) << "\":" << h[i].getLevel();
		if (i != h.size() - 1)
			x << ",";
	}
	x << "},\"spromo\":{";
	for (int i = 0; i < h.size(); i++)
	{
		x << "\"" << (abs(h[i].getId()) - 2) << "\":" << h[i].getPromotion();
		if (i != h.size() - 1)
			x << ",";
	}
	x << "},\"player\":[";
	for (int i = 0; i < enemyl.lineIds.size(); i++)
	{
		x << enemyl.lineIds[i];
		if (i < enemyl.lineIds.size() - 1)
			x << ",";
	}
	x << "],\"phero\":{";
	for (int i = 0; i < eh.size(); i++)
	{
		x << "\"" << (abs(eh[i].getId()) - 2) << "\":" << eh[i].getLevel();
		if (i != eh.size() - 1)
			x << ",";
	}
	x << "},\"ppromo\":{";
	for (int i = 0; i < eh.size(); i++)
	{
		x << "\"" << (abs(eh[i].getId()) - 2) << "\":" << eh[i].getPromotion();
		if (i != eh.size() - 1)
			x << ",";
	}
	x << "}}";
	string unencoded = x.str();
	string y = base64_encode((const unsigned char*)unencoded.c_str(), (int)unencoded.size());
	ostringstream xy;
	xy << "{\"validSolution\" : {\"target\":{\"followers\":" << enemyl.lineFollowers << ",\"monsters\":[";
	for (int i = 0; i < e.size(); i++)
	{
		xy << "{\"id\":" << e[i].getId();
		if (e[i].getId() < -1)
			xy << ",\"level\":" << e[i].getLevel();
		xy << "}";
		if (i < e.size() - 1)
			xy << ",";
	}
	xy << "]},\"solution\":{\"followers\":" << selfl.lineFollowers << ",\"monsters\":[{";
	for (int i = 0; i < v.size(); i++)
	{
		xy << "{\"id\":" << v[i].getId();
		if (v[i].getId() < -1)
			xy << ",\"level\":" << v[i].getLevel();
		xy << "}";
		if (i < v.size() - 1)
			xy << ",";
	}
	xy << "]},\"time\":0,\"fights\":0,\"replay\":\"" << y << "\"}}";
	cout << xy.str();
	cout << endl;
}
}
/*"}}*/