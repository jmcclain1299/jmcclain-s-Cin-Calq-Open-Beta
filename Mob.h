/*This is the header file for Monster.H This is the interface for the monster class used to populate
lines for the grid. The line interface and grid interface will be defined here as well.*/
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <list>
#include <map>
#ifndef MOB_H
#define MOB_H
using namespace std;
namespace jmcclain1299//Namespace for Mob functions
{
	class Mob//Class of unit
	{
	public:
		Mob();//Default constructor
		Mob(string name, int attack, int defense, char Element, int Followers, int id, char weakness);//Constructs a unit of class Mob
		Mob(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillName, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest); //Constructor for objects
		Mob(const Mob& mob);//Copy constructor
		int getAttack();//Returns attack
		int getDefense();//Returns defense
		char getElement();//Returns element
		int getFollowers();//Returns Followers
		void setLevel(int leveln);//Sets level without promotion
		void setLevel(double leveln);//Sets level with promotion
		int getLevel();//Returns level
		int getPromotion();//Returns Promotion
		char getTarget();//Returns Target
		char getWeakness();//Returns Weakness
		virtual void skillFunction() { cout << "I'm a mob mon."; };//Prints to the screen, informing me if an object was not created succesfully
		string getName();//Returns name
		string getSkillName();//Returns Skill Name
		void setPoints();//Sets Points, an interger used for determining stats, promotion, and other items.
		void setStats();//Sets the units Attack/ Defense
		void setAttack();//Sets the units Attack
		void setDefense();//Sets the units Defense
		void setAttack(int& attacks);//Changes the units Attack
		void setDefense(int& defenses);//Changes the units Defense
		int getRarity();//Returns the rarity
		int getId();//Returns the id
		int tdamage = 0;//Returns the turn damage
		int tdefense;//Returns the turn defense
		int tarmor = 0, tank;// Turn armor and tank value, tank being used with Neil.
		string quest = "questnone";
		double typeadv = 1;//Type multiplier
	protected://Member elements
		char element = 'e', target = 'e', weakness = 'e';
		int promotion = 0, level = 0, baseAttack = 0, baseDefense = 0, rarity = 0, id = 0,
			ratio = 1, prom1 = 1, prom2 = 1, prom4 = 1, points = 0, attack = baseAttack, defense = baseDefense,
			followers = 0;
		double prom5 = 0.0, modifier = 0.0;
		string name = "a", skillName = "mob";

	};
	class Line//Line of 5 Monsters.
	{
	public:
		Line();//Default constructor
		Line(vector<Mob>& lineup);/*Constructor based on an iterated list of units. Once it's created,
					 it does not need to be changed in any way.
					 It is simply a vector of size 1-6(0-5 in array notation).*/
		vector<Mob> getLine();//Returns line
		vector<int> lineIds;//line ids used by certain heroes/functions
		vector<int> setLineIds();//sets line ids, used during line creation
		void setStats();//sets stats, needs to be called when copying vectors to lines
		void setLineBIds();//lineB has different lineIds thanks to a bug in the game code(not mine, but the developer likes to call these... unintended features, or bonus implementations.)
		int setFollowers();//Sets the line followers for certain users, if they need that information.
		int lineFollowers = 0, aoedamage = 1, percaoedamage = 1, percmodifier = 1, debuff = 1, totaldamage = 0;//sets certain variables used by certain heroes
		int cDamage = 0, aDamage = 0;//more variables used by 2 specific heroes.
	private:
		vector<Mob> line;//the line of the mobs
	};
	class extra : public Mob//A mob that increases att/defense.
	{
	public:
		extra();
		extra(const Mob& mob);
		extra(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line);//increase each units att/def.

	};
	class buffahe : public Mob//a mob that heals it's own line and damages the enemies
	{
	public:
		buffahe();
		buffahe(const Mob& mob);
		buffahe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& line1, Line& line2);//does the healing/damaging

	};
	class dmg : public Mob//a mob that increases the attack of it's own line
	{
	public:
		dmg();
		dmg(const Mob& mob);
		dmg(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Mob& targets);//does the increasing

	};
	class def : public Mob//increases armor of own line
	{
	public:
		def();
		def(const Mob& mob);
		def(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line);//sets the armor

	};
	class aoe : public Mob//a mob that does aoe to enemy line
	{
	public:
		aoe();
		aoe(const Mob& mob);
		aoe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& line, Line& line2);//does the damage...

	};
	class heal : public Mob//heals own line
	{
	public:
		heal();
		heal(const Mob& mob);
		heal(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line,Line lane2);

	};
	class rico : public Mob//applies ricochete damage to enemy line
	{
	public:
		rico();
		rico(const Mob& mob);
		rico(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, int target, char weakness, string quest);
		virtual void skillFunction(Line& line, int& attack);
	};
	class buff : public Mob//increases it's own attack
	{
	public:
		buff();
		buff(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		buff(const Mob& mob);
		virtual void skillFunction();

	};
	class mon : public Mob//increases it's attack if mobs are behind it
	{
	public:
		mon();
		mon(const Mob& mob);
		mon(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line);

	};
	class turna : public Mob//gains stats every turn
	{
	public:
		turna();
		turna(const Mob& mob);
		turna(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& line);

	};
	class purity : public Mob//gains bonus damage if enemy is of same element
	{
	public:
		purity();
		purity(const Mob& mob);
		purity(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Mob& targets);

	};
	class rainbow : public Mob//increases attack/def if there are 4 unique elements behind it
	{
	public:
		rainbow();
		rainbow(const Mob& mob);
		rainbow(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob> lane);

	};
	class ban : public Mob//loses hp every turn
	{
	public:
		ban();
		ban(const Mob& mob);
		ban(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line line);

	};
	class boom : public Mob//does ricochet on death
	{
	public:
		boom();
		boom(const Mob& mob);
		boom(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillName, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& lane, Line& lane2);
	};
	class buffdef : public Mob//increases armor, the value dependant on mob's level
	{
	public:
		buffdef();
		buffdef(const Mob& mob);
		buffdef(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line);

	};
	class buffatk : public Mob//increases attack, value dependant
	{
	public:
		buffatk();
		buffatk(const Mob& mob);
		buffatk(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Mob& targets);

	};
	class buffboth : public Mob//increases attack and armor, value dependant
	{
	public:
		buffboth();
		buffboth(const Mob& mob);
		buffboth(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line);

	};
	class buffaoe : public Mob//does aoe dependent on users level
	{
	public:
		buffaoe();
		buffaoe(const Mob& mob);
		buffaoe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& lane, Line& lane2);

	};
	class buffheal : public Mob//heals dependent
	{
	public:
		buffheal();
		buffheal(const Mob& mob);
		buffheal(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(vector<Mob>& line, Line line2);

	};
	class debuff : public Mob//reduces enemy ricochet and healing, also causes units that buff/damage themselves to be receduced to the debuff%
	{
	public:
		debuff();
		debuff(const Mob& mob);
		debuff(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& lane);
	};
	class ratio : public Mob//reduces enemies hps to line.size()/enemyline.size()% of original hp. if there are 3 on left and 6 on right, 3/6 = .5, each enemy is only allowed 50% of it's original hp for starting the battle.
	{
	public:
		ratio();
		ratio(const Mob& mob);
		ratio(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& lane1, Line& lane2);

	};
	class evo : public Mob//gains extra stats in combat
	{
	public:
		evo();
		evo(const Mob& mob);
		evo(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction();
	};
	class paoe : public Mob//does an aoe at the start of the battle
	{
	public:
		paoe();
		paoe(const Mob& mob);
		paoe(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(Line& line);
	};
	class counter : public Mob//reflects some damage back at the attacker, stored in cDamage
	{
	public:
		counter();
		counter(const Mob& mob);
		counter(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		virtual void skillFunction(int& damage);
	};
	class ratk : public Mob//randomly gets extra attack at start of battle
	{
	public:
		ratk();
		ratk(const Mob& mob);
		ratk(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int seed);
	};
	class rtrg : public Mob//randomly targets a mob every turn for doing damage
	{
	public:
		rtrg();
		rtrg(const Mob& mob);
		rtrg(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		int skillFunction(Line& lane, int turns);
	};
	class rcrit : public Mob//randomly gets a type adv bonus
	{
	public:
		rcrit();
		rcrit(const Mob& mob);
		rcrit(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int seed);
	};
	class moob : public Mob//does splash damage if it kills a mob
	{
	public:
		moob();
		moob(const Mob& mob);
		moob(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(vector<Mob>& line);
	};
	class tank : public Mob//soaks up some damage from the lead mob
	{
	public:
		tank();
		tank(const Mob& mob);
		tank(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage);
	};
	class elem : public Mob//does bonues typeadv damage if it's target is weak to it's own type, f > e, a > w, e >a, w > f. normal is 150%, here it's 225% up to p4, then the value is mob dependent, stored below
	{
	public:
		elem();
		elem(const Mob& mob);
		elem(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(Mob& target);
	};
	class dampen : public Mob//sets enemy attack to 0 if it's over 15000
	{
	public:
		dampen();
		dampen(const Mob& mob);
		dampen(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage);
	};
	class explosion : public Mob//mob does damage to enemy if it dies
	{
	public:
		explosion();
		explosion(const Mob& mob);
		explosion(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage);
	};
	class leech : public Mob//gains hp from attacking enemy mobs
	{
	public:
		leech();
		leech(const Mob& mob);
		leech(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage);
	};
	class evolve : public Mob//gains attack from receiving damage
	{
	public:
		evolve();
		evolve(const Mob& mob);
		evolve(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage);
	};
	class anarchy : public Mob//reflects damage to highest hp enemy
	{
	public:
		anarchy();
		anarchy(const Mob& mob);
		anarchy(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage, Mob& targets);
	};
	class amoob : public Mob//same as moob, but more damage
	{
	public:
		amoob();
		amoob(const Mob& mob);
		amoob(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(vector<Mob>& line);
	};
	class otk : public Mob//kills enemy if their hp is below a threshold after they are attacked
	{
	public:
		otk();
		otk(const Mob& mob);
		otk(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& defense, Mob& targets, int& attack);
	};
	class armor : public Mob//attacks do -3x% of enemies baseattack as damage
	{
	public:
		armor();
		armor(const Mob& mob);
		armor(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage);
	};
	class reflect : public Mob//reflects damage done to them to the enemy line
	{
	public:
		reflect();
		reflect(const Mob& mob);
		reflect(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(int& damage, Line& line);
	};
	class amplify : public Mob//attacks do +3x% of enemies basehp as damage
	{
	public:
		amplify();
		amplify(const Mob& mob);
		amplify(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		int skillFunction(int& damage, Mob& targets);
	};
	class guardian : public Mob//hurts itself and enemy, heals own line except itself
	{
	public:
		guardian();
		guardian(const Mob& mob);
		guardian(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(Line& line, Line& line2, int target);
	};
	class posbonus : public Mob//gains bonus points for being near the front
	{
	public:
		posbonus();
		posbonus(const Mob& mob);
		posbonus(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(vector<Mob>& line);
	};
	class aposbonus : public Mob//same as posbonus
	{
	public:
		aposbonus();
		aposbonus(const Mob& mob);
		aposbonus(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(vector<Mob>& line);
	};
	class friends : public Mob//gives friendly units attack and def if it dies
	{
	public:
		friends();
		friends(const Mob& mob);
		friends(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(vector<Mob>& line, int mob);
	};
	class voids : public Mob//gains a type bonus against everything but void mobs
	{
	public:
		voids();
		voids(const Mob& mob);
		voids(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(Mob& targets);
	};
	class bday : public Mob//does bonus damage to last mob in enemy line
	{
	public:
		bday();
		bday(const Mob& mob);
		bday(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(Line& line);
	};
	class infiltered : public Mob//does ricochete damage to own and enemy line, minus itself
	{
	public:
		infiltered();
		infiltered(const Mob& mob);
		infiltered(int leveln, int rarity, int baseAttack, int baseDefense, string name, string skillname, char element, int id, int prom1, int prom2, int prom4, double prom5, double modifier, char target, char weakness, string quest);
		void skillFunction(Line& lane, Line& lane2);
	};
	int64_t calcSeed(vector<int> ids, int turns);//function for generating a seed
	static Mob a1("a1", 8, 20, 'a', 1000, 0, 'e');//Creates a Monster with ("name",attack, defense, element, followers, and id)
	static Mob a2("a2", 6, 48, 'a', 3900, 4, 'e');
	static Mob a3("a3", 12, 36, 'a', 8000, 8, 'e');
	static Mob a4("a4", 26, 24, 'a', 15000, 12, 'e');
	static Mob a5("a5", 20, 60, 'a', 41000, 16, 'e');
	static Mob a6("a6", 34, 62, 'a', 96000, 20, 'e');
	static Mob a7("a7", 26, 106, 'a', 144000, 24, 'e');
	static Mob a8("a8", 52, 78, 'a', 257000, 28, 'e');
	static Mob a9("a9", 54, 116, 'a', 495000, 32, 'e');
	static Mob a10("a10", 60, 142, 'a', 785000, 36, 'e');
	static Mob a11("a11", 110, 114, 'a', 1403000, 40, 'e');
	static Mob a12("a12", 88, 164, 'a', 1733000, 44, 'e');
	static Mob a13("a13", 94, 210, 'a', 2772000, 48, 'e');
	static Mob a14("a14", 142, 200, 'a', 4785000, 52, 'e');
	static Mob a15("a15", 190, 226, 'a', 8897000, 56, 'e');
	static Mob a16("a16", 196, 280, 'a', 12855000, 60, 'e');
	static Mob a17("a17", 206, 318, 'a', 16765000, 64, 'e');
	static Mob a18("a18", 280, 280, 'a', 21951000, 68, 'e');
	static Mob a19("a19", 206, 440, 'a', 27288000, 72, 'e');
	static Mob a20("a20", 268, 378, 'a', 32242000, 76, 'e');
	static Mob a21("a21", 286, 428, 'a', 42826000, 80, 'e');
	static Mob a22("a22", 320, 454, 'a', 55373000, 84, 'e');
	static Mob a23("a23", 348, 500, 'a', 72580000, 88, 'e');
	static Mob a24("a24", 374, 554, 'a', 94312000, 92, 'e');
	static Mob a25("a25", 430, 580, 'a', 124550000, 96, 'e');
	static Mob a26("a26", 528, 496, 'a', 155100000, 100, 'e');
	static Mob a27("a27", 484, 712, 'a', 202290000, 104, 'e');
	static Mob a28("a28", 642, 644, 'a', 265850000, 108, 'e');
	static Mob a29("a29", 616, 834, 'a', 368230000, 112, 'e');
	static Mob a30("a30", 906, 700, 'a', 505060000, 116, 'e');
	static Mob e1("e1", 4, 44, 'e', 1300, 1, 'f');
	static Mob e2("e2", 8, 30, 'e', 2700, 5, 'f');
	static Mob e3("e3", 16, 26, 'e', 7500, 9, 'f');
	static Mob e4("e4", 10, 72, 'e', 18000, 13, 'f');
	static Mob e5("e5", 40, 36, 'e', 54000, 17, 'f');
	static Mob e6("e6", 24, 72, 'e', 71000, 21, 'f');
	static Mob e7("e7", 36, 66, 'e', 115000, 25, 'f');
	static Mob e8("e8", 60, 60, 'e', 215000, 29, 'f');
	static Mob e9("e9", 48, 120, 'e', 436000, 33, 'f');
	static Mob e10("e10", 64, 122, 'e', 689000, 37, 'f');
	static Mob e11("e11", 81, 134, 'e', 1130000, 41, 'f');
	static Mob e12("e12", 120, 128, 'e', 1903000, 45, 'f');
	static Mob e13("e13", 132, 190, 'e', 3971000, 49, 'f');
	static Mob e14("e14", 136, 244, 'e', 6044000, 53, 'f');
	static Mob e15("e15", 186, 200, 'e', 7137000, 57, 'f');
	static Mob e16("e16", 190, 284, 'e', 12534000, 61, 'f');
	static Mob e17("e17", 192, 388, 'e', 16531000, 65, 'f');
	static Mob e18("e18", 242, 330, 'e', 22567000, 69, 'f');
	static Mob e19("e19", 282, 320, 'e', 27107000, 73, 'f');
	static Mob e20("e20", 264, 382, 'e', 32025000, 77, 'f');
	static Mob e21("e21", 272, 446, 'e', 42252000, 81, 'f');
	static Mob e22("e22", 324, 450, 'e', 55671000, 85, 'f');
	static Mob e23("e23", 340, 516, 'e', 73483000, 89, 'f');
	static Mob e24("e24", 458, 458, 'e', 96071000, 93, 'f');
	static Mob e25("e25", 418, 592, 'e', 123100000, 97, 'f');
	static Mob e26("e26", 468, 622, 'e', 157060000, 101, 'f');
	static Mob e27("e27", 602, 580, 'e', 206320000, 105, 'f');
	static Mob e28("e28", 540, 770, 'e', 268120000, 109, 'f');
	static Mob e29("e29", 614, 830, 'e', 363810000, 113, 'f');
	static Mob e30("e30", 614, 1022, 'e', 497080000, 117, 'f');
	static Mob f1("f1", 10, 16, 'f', 1000, 2, 'w');
	static Mob f2("f2", 16, 18, 'f', 3900, 6, 'w');
	static Mob f3("f3", 8, 54, 'f', 8000, 10, 'w');
	static Mob f4("f4", 16, 52, 'f', 23000, 14, 'w');
	static Mob f5("f5", 24, 42, 'f', 31000, 18, 'w');
	static Mob f6("f6", 20, 104, 'f', 94000, 22, 'w');
	static Mob f7("f7", 44, 54, 'f', 115000, 26, 'w');
	static Mob f8("f8", 50, 94, 'f', 321000, 30, 'w');
	static Mob f9("f9", 58, 102, 'f', 454000, 34, 'w');
	static Mob f10("f10", 82, 104, 'f', 787000, 38, 'w');
	static Mob f11("f11", 70, 164, 'f', 1229000, 42, 'w');
	static Mob f12("f12", 92, 156, 'f', 1718000, 46, 'w');
	static Mob f13("f13", 130, 166, 'f', 3169000, 50, 'w');
	static Mob f14("f14", 168, 168, 'f', 4741000, 54, 'w');
	static Mob f15("f15", 136, 234, 'f', 5676000, 58, 'w');
	static Mob f16("f16", 192, 288, 'f', 13001000, 62, 'w');
	static Mob f17("f17", 292, 236, 'f', 18090000, 66, 'w');
	static Mob f18("f18", 200, 392, 'f', 21951000, 70, 'w');
	static Mob f19("f19", 244, 352, 'f', 25170000, 74, 'w');
	static Mob f20("f20", 266, 388, 'f', 331550000, 78, 'w');
	static Mob f21("f21", 338, 362, 'f', 42798000, 82, 'w');
	static Mob f22("f22", 318, 458, 'f', 55582000, 86, 'w');
	static Mob f23("f23", 410, 424, 'f', 72480000, 90, 'w');
	static Mob f24("f24", 392, 534, 'f', 95772000, 94, 'w');
	static Mob f25("f25", 328, 764, 'f', 125440000, 98, 'w');
	static Mob f26("f26", 462, 638, 'f', 160030000, 102, 'w');
	static Mob f27("f27", 498, 690, 'f', 210430000, 106, 'w');
	static Mob f28("f28", 552, 746, 'f', 264250000, 110, 'w');
	static Mob f29("f29", 676, 746, 'f', 358120000, 114, 'w');
	static Mob f30("f30", 690, 930, 'f', 514040000, 118, 'w');
	static Mob w1("w1", 6, 30, 'w', 1400, 3, 'a');
	static Mob w2("w2", 12, 24, 'w', 3900, 7, 'a');
	static Mob w3("w3", 24, 18, 'w', 8000, 11, 'a');
	static Mob w4("w4", 20, 36, 'w', 18000, 15, 'a');
	static Mob w5("w5", 18, 78, 'w', 52000, 19, 'a');
	static Mob w6("w6", 44, 44, 'w', 84000, 23, 'a');
	static Mob w7("w7", 32, 92, 'w', 159000, 27, 'a');
	static Mob w8("w8", 36, 108, 'w', 241000, 31, 'a');
	static Mob w9("w9", 70, 80, 'w', 418000, 35, 'a');
	static Mob w10("w10", 70, 110, 'w', 675000, 39, 'a');
	static Mob w11("w11", 79, 152, 'w', 1315000, 43, 'a');
	static Mob w12("w12", 78, 188, 'w', 1775000, 47, 'a');
	static Mob w13("w13", 128, 140, 'w', 2398000, 51, 'a');
	static Mob w14("w14", 122, 212, 'w', 4159000, 55, 'a');
	static Mob w15("w15", 142, 276, 'w', 7758000, 59, 'a');
	static Mob w16("w16", 198, 286, 'w', 13475000, 63, 'a');
	static Mob w17("w17", 206, 318, 'w', 17573000, 67, 'a');
	static Mob w18("w18", 230, 330, 'w', 20909000, 71, 'a');
	static Mob w19("w19", 238, 360, 'w', 25079000, 75, 'a');
	static Mob w20("w20", 232, 454, 'w', 34182000, 79, 'a');
	static Mob w21("w21", 290, 416, 'w', 41901000, 83, 'a');
	static Mob w22("w22", 340, 440, 'w', 55877000, 87, 'a');
	static Mob w23("w23", 354, 490, 'w', 72242000, 91, 'a');
	static Mob w24("w24", 388, 540, 'w', 95903000, 95, 'a');
	static Mob w25("w25", 506, 500, 'w', 127260000, 99, 'a');
	static Mob w26("w26", 416, 700, 'w', 157140000, 103, 'a');
	static Mob w27("w27", 500, 682, 'w', 199340000, 107, 'a');
	static Mob w28("w28", 536, 762, 'w', 261020000, 111, 'a');
	static Mob w29("w29", 512, 1008, 'w', 370760000, 115, 'a');
	static Mob w30("w30", 802, 802, 'w', 515850000, 119, 'a');
	static Mob Nulla(0, 0, 0, 0, "null", "null", 'x', -1, 0, 0, 0, 0, 0, 'x', 'x', "questnone");//creats a hero with a level, rarity, attack, defense, name, skillname, element, id, prom1 value, prom2 value, prom3 value, prom 4 value, prom 5 value, skill value, target, and element. Later, quests will be added for optimizing solver
	static extra lot(1, 0, 20, 45, "lot", "extra", 'a', -2, 28, 25, 15, 3, 3, 'x', 'e', "quest18");//Alya_N
	static buffahe Tiny(1, 1, 30, 70, "tiny", "buffahe", 'e', -3, 40, 28, 17, .0404, (1 / 24.0), 'x', 'f',"quest54");
	static dmg Nebra(1, 2, 40, 110, "nebra", "dmg", 'f', -4, 140, 100, 20, 20, 20, 'x', 'w', "quest82");
	static def Valor(1, 0, 10, 20, "valor", "def", 'a', -5, 7, 3, 9, 1, 1, 'a', 'e', "quest4");
	static def Rokka(1, 0, 8, 30, "rokka", "def", 'e', -6, 40, 7, 5, 1, 1, 'e', 'f',"quest3");
	static def Pyromancer(1, 0, 12, 24, "pyromancer", "def", 'f', -7, 16, 2, 8, 1, 1, 'f', 'w',"quest6");
	static def Bewat(1, 0, 6, 50, "bewat", "def", 'w', -8, 31, 10, 8, 1, 1, 'w', 'a',"quest1");
	static dmg Hunter(1, 0, 14, 22, "hunter", "dmg", 'a', -9, 14, 12, 4, 2, 1, 'a', 'e',"quest7");
	static def Shaman(1, 1, 20, 40, "shaman", "def", 'e', -10, 36, 16, 25, 2, 2, 'e', 'f',"quest40");
	static aoe Alpha(1, 2, 22, 82, "alpha", "aoe", 'f', -11, 115, 37, 25 * 3, 4, 1, 'x', 'w',"quest74");
	static dmg Carl(1, 0, 12, 28, "carl", "dmg", 'w', -12, 18, 5, 5, 2, 2, 'w', 'a',"quest5");
	static def Nimue(1, 1, 22, 38, "nimue", "def", 'a', -13, 49, 14, 12, 2, 2, 'a', 'e',"quest39");
	static def Athos(1, 2, 26, 70, "athos", "def", 'e', -14, 70, 32, 96, 6, 2, 'x', 'f',"quest77");
	static dmg Jet(1, 0, 16, 24, "jet", "dmg", 'f', -15, 11, 9, 6, 2, 2, 'f', 'w', "quest12");
	static def Geron(1, 1, 24, 36, "geron", "def", 'w', -16, 27, 11, 18, 2, 2, 'w', 'a',"quest38");
	static dmg Rei(1, 2, 40, 46, "rei", "dmg", 'a', -17, 79, 67, 52, 8, 2, 'x', 'e',"quest97");
	static dmg Ailen(1, 0, 22, 19, "ailen", "dmg", 'e', -18, 21, 17, 7, 2, 2, 'e', 'f',"quest14");
	static def Faefyr(1, 1, 18, 50, "faefyr", "def", 'f', -19, 53, 17, 19, 2, 2, 'f', 'w', "quest34");
	static heal Auri(1, 2, 32, 60, "auri", "heal", 'w', -20, 70, 41, 23, 2, 2, 'x', 'a', "quest85");
	static dmg Nicte(1, 1, 32, 22, "nicte", "dmg", 'a', -21, 21, 43, 24, 4, 4, 'a', 'e',"quest36");
	static rico James(1, 2, 12, 50, "james", "rico", 'e', -22, 89, 39, 29, 0.1, 0.75, 5, 'f',"quest69");
	static dmg K41ry(1, 0, 16, 28, "k41ry", "dmg", 'a', -23, 19, 14, 19, 3, 3, 'a', 'e', "quest9");
	static dmg T4urus(1, 1, 20, 46, "t4urus", "dmg", 'e', -24, 28, 20, 30, 1, 1, 'x', 'f', "quest37");
	static aoe Tr0n1x(1, 2, 20, 100, "tr0n1x", "aoe", 'f', -25, 107, 19, 35, 3, 3, 'x', 'w',"quest73");
	static dmg Aquortis(1, 0, 8, 58, "aquortis", "dmg", 'w', -26, 28, 18, 18, 3, 3, 'w', 'a',"quest2");
	static heal Aeris(1, 1, 32, 30, "aeris", "heal", 'a', -27, 10, 36, 28, 1, 1, 'x', 'e',"quest35");
	static buff Geum(1, 2, 2, 75, "geum", "buff", 'e', -28, 213, 8, 22, 0.2, 2, 'x', 'f',"quest67");
	static dmg Forest_Druid(1, 1, 16, 46, "forestduid", "dmg", 'e', -29, 38, 6, 7, 4, 4, 'e', 'f',"quest32");
	static dmg Ignitor(1, 1, 24, 32, "ignitor", "dmg", 'f', -30, 38, 6, 7, 4, 4, 'f', 'w',"quest47");
	static dmg Undine(1, 1, 14, 58, "undine", "dmg", 'w', -31, 25, 7, 15, 4, 4, 'w', 'a',"quest31");
	static dmg Rudean(1, 0, 12, 38, "rudean", "dmg", 'f', -32, 19, 7, 5, 3, 3, 'f', 'w',"quest8");
	static buff Aural(1, 1, 50, 8, "aural", "buff", 'w', -33, 33, 31, 28, 0.12, 1.2, 'x', 'a',"quest44");
	static mon Geror(1, 2, 46, 46, "geror", "mon", 'a', -34, 95, 125, 36, 0.12, 1.2, 'x', 'e',"quest94");
	static extra Veildur(1, 2, 44, 66, "veildur", "extra", 'e', -35, 74, 11, 51, 3, 3, 'x', 'f',"quest102");
	static extra BrynHildr(1, 2, 48, 72, "brynhildr", "extra", 'a', -36, 84, 23, 59, 4, 4, 'x', 'e',"quest105");
	static extra Groth(1, 2, 52, 78, "Ggoth", "extra", 'f', -37, 114, 70, 62, 5, 5, 'x', 'w',"quest109");
	static dmg Ourea(1, 0, 16, 30, "ourea", "dmg", 'e', -38, 17, 3, 8, 3, 3, 'e', 'f', "quest11");
	static extra Erebus(1, 1, 20, 48, "erebus", "extra", 'f', -39, 55, 10, 20, 2, 2, 'f', 'w',"quest42");
	static purity Pontus(1, 2, 36, 62, "pontus", "purity", 'w', -40, 121, 43, 20, 0.2, 2, 'w', 'a',"quest101");
	static def Chroma(1, 1, 20, 52, "chroma", "def", 'a', -41, 23, 15, 14, 4, 4, 'a', 'e',"quest33");
	static def Petry(1, 1, 44, 26, "petry", "def", 'e', -42, 18, 16, 28, 4, 4, 'e', 'f',"quest49");
	static def Zaytus(1, 1, 22, 58, "zaytus", "def", 'f', -43, 57, 5, 16, 4, 4, 'f', 'w',"quest43");
	static turna Spyke(1, 2, 45, 75, "spyke", "turna", 'a', -44, 112, 22, 40, 10, 10, 'x', 'e',"quest100");
	static rainbow Aoyuki(1, 2, 55, 70, "aoyuki", "rainbow", 'w', -45, 75, 121, 66, 100, 100, 'x', 'a',"quest99");
	static ban Gaiabyte(1, 2, 150, 75, "gaiabyte", "ban", 'e', -46, 113, 31, 52, 2, 2, 'x', 'f',"quest114");
	static dmg Oymos(1, 0, 14, 36, "oymos", "dmg", 'a', -47, 24, 15, 21, 4, 4, 'a', 'e',"quest10");
	static extra Xarth(1, 1, 32, 32, "xarth", "extra", 'e', -48, 11, 18, 19, 2, 2, 'e', 'f',"quest41");
	static purity Atzar(1, 2, 32, 76, "atzar", "purity", 'f', -49, 85, 28, 48, 0.2, 2, 'f', 'w',"quest86");
	static boom Zeth(1, 2, 42, 70, "zeth", "boom", 'w', -50, 127, 16, 24, 0.05, 0.1, 'x', 'a',"quest104");
	static boom Koth(1, 2, 46, 70, "koth", "boom", 'e', -51, 99, 39, 70, .05, .15, 'x', 'f',"quest107");
	static boom Gurth(1, 2, 50, 82, "gurth", "boom", 'a', -52, 108, 43, 68, .05, .2, 'X', 'e',"quest110");
	static buffdef Werewolf(1, 0, 25, 35, "werewolf", "buffdef", 'e', -53, 23, 28, 19, 0.01112, 0.1112, 'x', 'f',"quest22");
	static buffatk JackO_Knight(1, 1, 25, 35, "jackoknight", "buffatk", 'a', -54, 50, 13, 38, 0.01112, 0.1112, 'x', 'e',"quest55");
	static buffboth Dullahan(1, 2, 45, 75, "dullahan", "buffboth", 'f', -55, 114, 11, 48, 0.0404, 0.1112, 'x', 'w',"quest111");
	static def Lady_Odelith(1, 1, 36, 36, "ladyodelith", "extra", 'w', -56, 19, 17, 29, 4, 4, 'w', 'a',"quest45");
	static buffdef Shygu(1, 2, 54, 34, "shygu", "buffdef", 'a', -57, 23, 68, 71, 0.01112, 0.1112, 'a', 'e',"quest84");
	static buffdef Thert(1, 2, 28, 72, "thert", "buffdef", 'e', -58, 61, 44, 35, 0.01112, 0.1112, 'e', 'f',"quest78");
	static buffdef Lord_Kirk(1, 2, 64, 32, "lordkirk", "buffdef", 'f', -59, 77, 99, 83, 0.01112, 0.1112, 'f', 'w',"quest92");
	static buffdef Neptunius(1, 2, 70, 30, "neptunius", "buffdef", 'w', -60, 92, 73, 83, 0.01112, 0.1112, 'w', 'a',"quest98");
	static rico Sigrun(1, 2, 12, 65, "sigrun", "rico", 'f', -61, 132, 29, 45, 0.15, 0.5, 5, 'w',"quest68");
	static rico Koldis(1, 2, 14, 70, "koldis", "rico", 'w', -62, 173, 18, 26, 0.15, 0.5, 5, 'a',"quest72");
	static rico Alvitr(1, 2, 16, 75, "alvitr", "rico", 'e', -63, 152, 50, 52, 0.15, 0.5, 5, 'f',"quest70");
	static dmg Hama(1, 0, 18, 30, "hama", "dmg", 'w', -64, 21, 10, 7, 4, 4, 'w', 'a',"quest15");
	static extra Hallinskidi(1, 1, 34, 34, "hallinskidi", "extra", 'a', -65, 17, 54, 20, 2, 2, 'a', 'e',"quest50");
	static purity Rigr(1, 2, 42, 60, "rigr", "purity", 'e', -66, 68, 21, 93, 0.2, 2, 'e', 'f',"quest103");
	static buffaoe aAlpha(1, 3, 46, 174, "aalpha", "buffaoe", 'f', -67, 251, 40, 92, 0.0304, 0.304, 'x', 'w',"quest138");
	static buffdef aAthos(1, 3, 60, 162, "aathos", "buffdef", 'e', -68, 281, 57, 36, 0.0304, 0.304, 'x', 'f',"quest140");
	static buffatk aRei(1, 3, 104, 120, "arei", "buffatk", 'a', -69, 127, 46, 176, 0.1414, 0.304, 'x', 'e',"quest150");
	static buffheal aAuri(1, 3, 78, 148, "aauri", "buffheal", 'w', -70, 81, 221, 59, 0.0152, 0.152, 'x', 'a',"quest139");
	static rico aTr0n1x(1, 3, 38, 190, "atr0n1x", "rico", 'f', -71, 383, 56, 25, 0.05, 0.75, 5, 'w',"quest137");
	static buff aGeum(1, 3, 8, 222, "ageum", "buff", 'e', -72, 348, 35, 16, 0.2, 2, 'a', 'f',"quest136");
	static mon aGeror(1, 3, 116, 116, "ageror", "mon", 'a', -73, 173, 22, 153, 0.13, 1.3, 'x', 'e',"quest149");
	static aoe Lord_Of_Chaos(1, 4, 112, INT_MAX, "LoC", "aoe", 'f', -74, 0, 0, 0, 0, 50, 'x', 'w',"quest11");
	static buffheal Christmas_Elf(1, 0, 24, 38, "christmaself", "buffheal", 'w', -75, 28, 34, 22, 0.01112, 0.1112, 'x', 'a',"quest20");
	static buffaoe Reindeer(1, 1, 36, 54, "reindeer", "buffaoe", 'a', -76, 53, 18, 33, 0.01112, 0.1112, 'x', 'e',"quest56");
	static buffahe Santa_Claus(1, 2, 48, 72, "santaclaus", "buffahe", 'f', -77, 107, 96, 78, 0.0404, 0.1112, 'x', 'w',"quest108");
	static rico Sexy_Santa(1, 1, 44, 44, "sexysanta", "rico", 'e', -78, 27, 41, 40, 0.05, 0.66, 5, 'f',"quest54");
	static dmg Toth(1, 0, 24, 24, "toth", "dmg", 'f', -79, 18, 32, 16, 4, 4, 'f', 'w',"quest16");
	static extra Ganah(1, 1, 30, 40, "ganah", "extra", 'w', -80, 29, 26, 43, 2, 2, 'w', 'a',"quest48");
	static purity Dagda(1, 2, 46, 58, "dagda", "purity", 'a', -81, 79, 78, 123, 0.2, 2, 'a', 'e',"quest112");
	static debuff Bubbles(1, 3, 100, 300, "bubbles", "debuff", 'w', -82, 291, 120, 58, 0.0005, 0.0005, 'x', 'a',"quest148");
	static purity aPontus(1, 3, 86, 150, "apontus", "purity", 'w', -83, 124, 211, 190, 0.3, 3, 'w', 'a',"quest144");
	static purity aAtzar(1, 3, 81, 162, "aatzar", "purity", 'f', -84, 333, 27, 86, 0.3, 3, 'f', 'w',"quest156");
	static rico Arshen(1, 2, 36, 74, "arshen", "rico", 'a', -85, 83, 44, 19, 0.05, 1, 1, 'e',"quest81");
	static rico Rua(1, 2, 40, 78, "rua", "rico", 'f', -86, 88, 44, 37, 0.05, 1, 1, 'w',"quest93");
	static rico Dorth(1, 2, 44, 82, "dorth", "rico", 'w', -87, 90, 38, 40, 0.05, 1, 1, 'a',"quest91");
	static purity aRigr(1, 3, 99, 141, "arigr", "purity", 'e', -88, 138, 121, 40, 0.3, 3, 'e', 'f',"quest155");
	static debuff Moak(1, 4, 190, INT_MAX, "moak", "debuff", 'e', -89, 0, 0, 0, 0, 0.5, 'x', 'f',"quest11");
	static buffatk Hosokawa(1, 2, 50, 42, "hosokawa", "buffatk", 'a', -90, 108, 115, 74, 0.01112, 0.1819, 'a', 'e',"quest96");
	static buffatk Takeda(1, 2, 66, 32, "takeda", "buffatk", 'e', -91, 83, 82, 32, 0.01112, 0.1112, 'e', 'f',"quest89");
	static buffatk Hirate(1, 2, 56, 38, "hirate", "buffatk", 'f', -92, 53, 133, 44, 0.01112, 0.1112, 'f', 'w',"quest83");
	static buffatk Hattori(1, 2, 48, 44, "hattori", "buffatk", 'w', -93, 65, 74, 64, 0.01112, 0.1112, 'w', 'a',"quest88");
	static purity aDagda(1, 3, 107, 135, "adagda", "purity", 'a', -94, 208, 78, 322, 0.3, 3, 'a', 'e',"quest156");
	static dmg Bylar(1, 0, 20, 30, "bylar", "dmg", 'e', -95, 18, 16, 15, 4, 4, 'e', 'f',"quest17");
	static turna Boor(1, 1, 36, 36, "boor", "turna", 'f', -96, 19, 49, 20, 3, 3, 'x', 'w',"quest46");
	static extra Bavah(1, 2, 52, 52, "bavah", "extra", 'w', -97, 84, 92, 43, 5, 2, 'x', 'a',"quest95");
	static ratio Leprechaun(1, 2, 25, 75, "leprechaun", "ratio", 'e', -98, 59, 13, 13, 1.0, 0.0, 'x', 'f',"quest75");
	static evo Sparks(1, 0, 30, 30, "sparks", "evo", 'f', -99, 29, 29, 15, 0.2, 2, 'x', 'w',"quest24");
	static evo Leaf(1, 1, 42, 48, "leaf", "evo", 'e', -100, 35, 57, 26, 0.2, 2, 'x', 'f',"quest60");
	static evo Flynn(1, 2, 48, 70, "flynn", "evo", 'a', -101, 46, 93, 69, 0.2, 2, 'x', 'e',"quest122");
	static buffboth aBavah(1, 3, 122, 122, "abavah", "buffboth", 'w', -102, 217, 152, 145, 0.0152, 0.152, 'x', 'a',"quest145");
	static paoe Dr_Hawking(1, 2, 60, 66, "drhawking", "paoe", 'a', -103, 94, 136, 70, 0.3, 1, 'x', 'e',"quest116");
	static counter Master_Lee(1, 3, 90, 150, "masterlee", "counter", 'a', -104, 314, 290, 225, 0.05, 0.5, 'x', 'e',"quest158");
	static counter Kumu_San(1, 2, 38, 70, "kumusan", "counter", 'f', -105, 134, 132, 135, 0.02, 0.2, 'x', 'w',"quest115");
	static counter Liu_Cheng(1, 2, 42, 78, "liucheng", "counter", 'w', -106, 113, 147, 80, 0.025, 0.25, 'x', 'a',"quest118");
	static counter Hidoka(1, 2, 44, 86, "hidoka", "counter", 'e', -107, 144, 172, 45, 0.03, 0.3, 'x', 'f',"quest119");
	static turna Kryton(1, 4, 10, INT_MAX, "kryton", "turna", 'w', -108, 0, 0, 0, 0, 10, 'x', 'e',"quest11");
	static ratk Dicemaster(1, 0, 26, 25, "dicemaster", "ratk", 'w', -109, 19, 36, 12, 20, 20, 'x', 'a',"quest19");
	static rtrg Luxurius_Maximus(1, 1, 60, 28, "lux", "rtrg", 'f', -110, 44, 47, 29, 1, 0, 'x', 'w',"quest52");
	static rcrit Pokerface(1, 2, 70, 70, "pokerface", "rcrit", 'e', -111, 119, 211, 111, 0.3, 3, 'x', 'f',"quest117");
	static rico Taint(1, 0, 25, 25, "taint", "rico", 'a', -112, 13, 4, 21, 0.05, 0.5, 5, 'e',"quest13");
	static turna Putrid(1, 1, 50, 48, "putrid", "turna", 'e', -113, 51, 93, 50, 1, -3, 'x', 'f',"quest57");
	static moob Defile(1, 2, 48, 52, "defile", "moob", 'f', -114, 60, 138, 72, 50, 50, 'x', 'w',"quest90");
	static tank Neil(1, 2, 15, 150, "neil", "tank", 'w', -115, 244, 20, 23, 0.05, 0.3, 'x', 'a',"quest66");
	static elem Mahatma(1, 2, 26, 78, "mahatma", "elem", 'a', -116, 56, 19, 25, 0.075, 0.75, 'w', 'e',"quest76");
	static elem Jade(1, 2, 30, 76, "jade", "elem", 'e', -117, 56, 19, 25, 0.075, 0.75, 'a', 'f',"quest79");
	static elem Edana(1, 2, 36, 72, "edana", "elem", 'f', -118, 91, 46, 66, 0.075, 0.75, 'e', 'w',"quest87");
	static elem Dybbuk(1, 2, 30, 80, "dybbuk", "elem", 'w', -119, 65, 43, 37, 0.075, 0.075, 'f', 'a',"quest80");
	static buffdef aShygu(1, 3, 135, 85, "ashygu", "buffdef", 'a', -120, 148, 113, 217, 0.01819, 0.1819, 'a', 'e',"quest147");
	static buffdef aThert(1, 3, 70, 180, "athert", "buffdef", 'e', -121, 346, 47, 46, 0.1819, 0.01819, 'e', 'f',"quest141");
	static buffdef aLord_Kirk(1, 3, 160, 80, "alordkirk", "buffdef", 'f', -122, 215, 255, 85, 0.01819, 0.1819, 'f', 'w',"quest153");
	static buffdef aNeptunius(1, 3, 175, 75, "aneptunius", "buffdef", 'w', -123, 335, 201, 241, 0.01819, 0.1819, 'w', 'a',"quest154");
	static buffatk aHosokawa(1, 3, 124, 106, "ahosokawa", "buffatk", 'a', -124, 229, 423, 207, 0.01819, 0.1819, 'a', 'e',"quest151");
	static buffatk aTakeda(1, 3, 164, 182, "atakeda", "buffatk", 'e', -125, 252, 425, 66, 0.01819, 0.1819, 'e', 'f',"quest152");
	static buffatk aHirate(1, 3, 144, 96, "ahirate", "buffatk", 'f', -126, 139, 23, 27, 0.01819, 0.1819, 'f', 'w',"quest143");
	static buffatk aHattori(1, 3, 126, 114, "ahattori", "buffatk", 'w', -127, 218, 116, 117, 0.01819, 0.1819, 'w', 'a',"quest146");
	static dampen Doyenne(1, 4, 174, INT_MAX, "doyenne", "dampen", 'w', -128, 0, 0, 0, 0, 0, 'x', 'a',"quest11");
	static explosion Billy(1, 0, 40, 30, "billy", "explosion", 'e', -129, 43, 30, 24, 25, 100, 'x', 'f',"quest23");
	static leech Sanqueen(1, 1, 22, 88, "sanqueen", "leech", 'w', -130, 71, 8, 16, 0.08, 0.8, 'x', 'a',"quest51");
	static evolve Cliodhna(1, 2, 60, 150, "cliodhna", "evolve", 'a', -131, 193, 240, 78, 0.1, 1, 'x', 'e',"quest120");
	static anarchy Guy(1, 3, 64, 340, "guy", "anarchy", 'f', -132, 160, 51, 115, 0.1, 1, 'x', 'w',"quest160");
	static amoob aDefile(1, 3, 114, 126, "adefile", "amoob", 'f', -133, 126, 102, 114, 2, 7, 'x', 'w',"quest142");
	static otk Raider_Rose(1, 3, 62, 186, "raiderrose", "otk", 'e', -134, 353, 32, 476, 0.05, 0.6, 'x', 'f',"quest159");
	static otk Buccaneer_Beatrice(1, 2, 30, 96, "buccaneerbeatrice", "otk", 'w', -135, 66, 32, 66, 0.05, 0.3, 'x', 'a',"quest106");
	static otk Corsair_Charles(1, 2, 32, 100, "corsaircharles", "otk", 'a', -136, 87, 21, 64, 0.05, 0.35, 'x', 'e',"quest113");
	static otk Marauder_Magnus(1, 2, 34, 105, "maraudermagnus", "otk", 'f', -137, 175, 67, 71, 0.05, 0.4, 'x', 'w',"quest121");
	static armor Frosty(1, 1, 52, 46, "frosty", "armor", 'w', -138, 51, 69, 16, 0.03, 0.03, 'x', 'a',"quest59");
	static reflect Fir(1, 0, 18, 50, "fir", "reflect", 'e', -139, 33, 5, 11, 0.0004, 0.004, 'x', 'f',"quest21");
	static amplify melf(1, 1, 34, 78, "melf", "amplify", 'a', -140, 42, 37, 39, 0.003, 0.03, 'x', 'e',"quest58");
	static guardian Kedari(1, 2, 18, 170, "kedari", "guardian", 'f', -141, 133, 19, 25, 0.2, 2, 'x', 'w',"quest71");
	static rico Raze(1, 0, 26, 18, "raze", "rico", 'w', -142, 8, 3, 14, 0.05, 0.7, 1, 'a',"quest6");
	static boom Ruin(1, 1, 48, 44, "ruin", "boom", 'a', -143, 23, 61, 23, 0.05, 0.1, 'x', 'e',"quest57");
	static posbonus Seethe(1, 2, 54, 48, "seethe", "posbonus", 'e', -144, 23, 61, 23, 15, 15, 'x', 'f',"quest87");
	static aposbonus aSeethe(1, 3, 131, 171, "aseethe", "aposbonus", 'e', -145, 90, 117, 124, 0.11, 0.45, 'x', 'f',"quest147");
	static friends Blossom(1, 2, 54, 54, "blossom", "friends", 'e', -146, 99, 99, 144, 0.01, 0.10, 'x', 'f',"quest92");
	static friends Flint(1, 2, 56, 56, "flint", "friends", 'f', -147, 100, 100, 150, 0.01, 0.11, 'x', 'w',"quest99");
	static friends Orin(1, 2, 58, 58, "orin", "friends", 'a', -148, 101, 101, 156, 0.01, 0.12, 'x', 'e',"quest105");
	static friends Aurora(1, 3, 130, 130, "aurora", "friends", 'w', -149, 221, 221, 344, 0.01, 0.15, 'x', 'a',"quest143");
	static rico Cupid(1, 2, 20, 220, "cupid", "rico", 'a', -150, 150, 50, 110, 1.0, 3.0, 1, 'e',"quest119");
	static voids Transient(1, 0, 22, 22, "transient", "void", 'v', -151, 11, 11, 20, 0.1, 0.5, 'x', 'x',"quest25");
	static voids Maunder(1, 1, 34, 34, "maunder", "void", 'v', -152, 22, 22, 32, 0.1, 0.5, 'x', 'x',"quest58");
	static voids The_Wanderer(1, 2, 50, 50, "thewanderer", "void", 'v', -153, 80, 80, 120, 0.1, 0.5, 'x', 'x',"quest127");
	static bday B_Day(1, 2, 40, 100, "bday", "bday", 'a', -154, 61, 51, 23, 0.05, 0.1, 'x', 'e',"quest92");
	static infiltered Cloud(1, 0, 22, 44, "cloud", "infiltered", 'a', -155, 36, 32, 11, 0.05, 0.95, 'x', 'e',"quest19");
	static infiltered Ember(1, 1, 32, 64, "ember", "infiltered", 'f', -156, 89, 34, 22, 0.05, 0.95, 'x', 'w',"quest53");
	static infiltered Riptide(1, 2, 42, 84, "riptide", "infiltered", 'w', -157, 89, 34, 22, 0.05, 0.95, 'x', 'a',"quest88");
	static infiltered Spike(1, 3, 90, 180, "spike", "infiltered", 'e', -158, 234, 103, 136, 0.05, 0.95, 'x', 'f',"quest144");
	static elem aMahatma(1, 4, 60, 180, "amahatma", "elem", 'a', -159, 241, 50, 45, .3, 3.2, 'w', 'e',"quest139");
	static elem aJade(1, 4, 68, 172, "ajade", "elem", 'e', -160, 288, 41, 33, .3, 3.2, 'a', 'f',"quest147");
	static elem aEdana(1, 4, 80, 160, "aedana", "elem", 'f', -161, 191, 180, 74, .3, 3.2, 'e', 'w',"quest146");
	static elem aDybbuk(1, 4, 66, 176, "adybbuk", "elem", 'w', -162, 272, 55, 29, .3, 3.2, 'f', 'a',"quest148");
	int  doBattle(Line line1, Line line2);//compares the lines
	void calcTurn0(Line& linea, Line& lineb, int64_t seed);//does certain skills, like paoe and ratio, as they are only done once at start of battle
	void doTurn(Line& LineA, Line& LineB, int turns);//does attacks and certain skills
	bool neil(Line line);//checks if neil is in the line for certain effects
	bool bubbles(Line line);//checks if bubbles/moak is in the line to apply that skill function
	bool Gaia(Line line);//checks if gaia is in the line for his function
	void killUnits(Line& line, Line& line2);//removes dead units and applies those skilleffects that are applied in the subturn
	bool isAlive(Line line);//checks if line size > 0
	void calcTurn(Line& LineA, Line& LineB, int64_t seed, int turns);//sets bonuses prior to calculating damage done
	bool anyDead(vector<Mob> line, vector<Mob> line2);//checks if any mobs in the line have hp <=0
	void getResult(list<Mob> heat, Line selfl, int upperlimit, int lowerlimit, Line enemyl);//returns wether or not a winner was found
	void getPromotional(list<Mob> heat, Line selfl, int upperlimit, int lowerlimit, Line enemyl, int id);
	typedef unsigned char BYTE;
	static string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	string base64_encode(BYTE const* buf, unsigned int bufLen);
}
#endif //MOB_H
