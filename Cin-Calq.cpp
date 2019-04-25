#include "pch.h"
#include "Mob.h"
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <fstream>
#include <sstream> 
using namespace std;
using namespace jmcclain1299;
string choice;
int idh;
void populate(Line& lenemy, Line& lself, int& ulimit, int& llimit, list<Mob>& heats, map<string, vector<Mob>>& q, map<string, Mob>& Heroes);//fills the pools
int main()
{
	map<string, Mob> Heromap;
	int upperlimits, lowerlimits;//limits for determining what mobs to put into the pool
	Line enemyline, selfa;//lines to battle with
	char run = 'y';
	double l;
	string type, nextmob;
	vector<Mob> enemyi;
	list<Mob> heatl;//list of mobs/heroes that get populated into the heat
	map<string, vector<Mob>> quests;
	populate(enemyline, selfa, upperlimits, lowerlimits, heatl, quests, Heromap);//Fills enemy line, and fills the heat, which is the list of mobs to choose from, with the upper and lower limits on followers
	enemyi = enemyline.getLine();
	if (choice == "Promotion")
	{
		getPromotional(heatl, selfa, upperlimits, lowerlimits, enemyline, idh);
	}
	else if ((enemyi.size() == 1) && (enemyi[0].getDefense() == INT_MAX))
	{
		getWorldBoss(heatl, selfa, upperlimits, lowerlimits, enemyline);
	}
	else getResult(heatl, selfa, upperlimits, lowerlimits, enemyline);//Tries combinations of units and heroes to beat the input enemy line in setup.txt. If a solution is found, it prints it.
	cout << "Would you like to run this program again? Enter [y/n]\n";
	cin >> run;
	while (run != 'n' && run != 'N')
	{
		cout << "DQ, Quest, or Promotion? Enter the option you'd like with the capitilization shown.\n";
		cin >> type;
		if (type == "DQ") {
			cout << "Please enter the mobs/heroes you'd like to run against, and type done when finished \n";
			cin >> nextmob;
			while (nextmob != "done")
			{
				Mob mob = Heromap.find(nextmob)->second;
				if (mob.getSkillName() != "mob")
				{
					cin >> l;
					int m = l;
					if (fmod(l, 1) == 0)
					{
						mob.setLevel(m);
					}
					else mob.setLevel(l);
				}
				enemyi.push_back(mob);
				cin >> nextmob;
			}
			enemyline = enemyi;
			enemyi.clear();
			getResult(heatl, selfa, upperlimits, lowerlimits, enemyline);
			cout << "Would you like to run this program again? Enter [y/n]\n";
			cin >> run;
		}
		else if (type == "Quest")
		{
			cout << "Which quest would you like to run? Enter your answer as quest1 for quest 1, or quest101 for quest 101\n";
			quest:
			cin >> nextmob;
			enemyline = quests.find(nextmob)->second;
			getResult(heatl, selfa, upperlimits, lowerlimits, enemyline);
			cout << "Would you like to run this program again? Enter [y/n] \n";
			cin >> run;
		}
		else if (type == "Promotion")
		{
			cout << "Which hero are you trying to promote? Enter the hero name in all lower case with no spaces or special charcters \n";
			promotional:
			cin >> nextmob;
			Mob nextmoba = Heromap.find(nextmob)->second;
			enemyline = quests.find(nextmoba.quest)->second;
			int id = nextmoba.getId();
			getPromotional(heatl, selfa, upperlimits, lowerlimits, enemyline, id);
		}
	}
	//Some users only want a solution for 4 or 5 units, and options were added for this scenario. Due to time constraints, added user features and interfaces were not added at this time.
	//Future updates include: Choosing quests for hero promotions, a battle replay output, and speed optimizations(not having nulla in the pool if lep isn't in the pool.)
	//Line Driver, enemyDriver;
	//Dorth.setLevel(99.4), Rua.setLevel(99.4), Geror.setLevel(99.4), Cliodhna.setLevel(99.4), Pokerface.setLevel(99.4), Defile.setLevel(99.4);
	//Shaman.setLevel(1000), Nicte.setLevel(1000), Ignitor.setLevel(1000), Neil.setLevel(1000);
	//vector<Mob> driver = { Dorth, Rua, Geror, Cliodhna, Pokerface, Defile }, enemydriver = { f30, Shaman, Nicte, Ignitor, Neil };
	//Driver = driver, enemyDriver = enemydriver;
	//doBattle(Driver, enemyDriver);
	return 0;

}
void populate(Line& lenemy, Line& lself, int& ulimit, int& llimit, list<Mob>& heats, map<string, vector<Mob>>& q, map<string, Mob>& Heroes)
{
	ifstream setup;
	setup.open("setup.txt");
	if (!setup)
	{
		cout << "File didn't open";
	}
	vector<Mob>mobs = { a1, a2, a3, a4, a5, a6, a7, a8, a9, a10,
	a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24,
	a25, a26, a27, a28, a29, a30, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10,
	e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24,
	e25, e26, e27, e28, e29, e30, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10,
	f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24,
	f25, f26, f27, f28, f29, f30, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10,
	w11, w12, w13, w14, w15, w16, w17, w18, w19, w20, w21, w22, w23, w24,
	w25, w26, w27, w28, w29, w30 };
	vector<Mob>heroes = { lot, Tiny, Nebra, Valor, Rokka, Pyromancer, Bewat, Hunter, Shaman,
   Alpha, Carl, Nimue, Athos, Jet, Geron, Rei, Ailen, Faefyr, Auri, Nicte, James, K41ry, T4urus,
   Tr0n1x, Aquortis, Aeris, Geum, Forest_Druid, Ignitor, Undine, Rudean, Aural, Geror, Veildur, BrynHildr,
   Groth, Ourea, Erebus, Pontus, Chroma, Petry, Zaytus, Spyke, Aoyuki, Gaiabyte, Oymos, Xarth, Atzar,
   Zeth, Koth, Gurth, Werewolf, JackO_Knight, Dullahan, Lady_Odelith, Shygu, Thert, Lord_Kirk,
   Neptunius, Sigrun, Koldis, Alvitr, Hama, Hallinskidi, Rigr, aAlpha, aAthos, aRei, aAuri,
   aTr0n1x, aGeum, aGeror, Lord_Of_Chaos, Christmas_Elf, Reindeer, Santa_Claus, Sexy_Santa, Toth,
   Ganah, Dagda, Bubbles, aPontus, aAtzar, Arshen, Rua, Dorth, aRigr, Moak, Hosokawa, Takeda, Hirate,
   Hattori, aDagda, Bylar, Boor, Bavah, Leprechaun, Sparks, Leaf, Flynn, aBavah, Dr_Hawking, Master_Lee,
   Kumu_San, Liu_Cheng, Hidoka, Kryton, Dicemaster, Luxurius_Maximus, Pokerface, Taint, Putrid, Defile,
   Neil, Mahatma, Jade, Edana, Dybbuk, aShygu, aThert, aLord_Kirk, aNeptunius, aHosokawa, aTakeda,
   aHirate, aHattori, Doyenne, Billy, Sanqueen, Cliodhna, Guy, aDefile, Raider_Rose,
   Buccaneer_Beatrice, Corsair_Charles, Marauder_Magnus, Frosty, Fir, melf, Kedari, Raze, Ruin,
   Seethe, aSeethe, Blossom, Flint, Orin, Aurora, Cupid, Transient, Maunder, The_Wanderer, B_Day,
   Cloud, Ember, Riptide, Spike, aMahatma, aJade, aEdana, aDybbuk };
	Mob x = heroes[55];
	x.setLevel(1000), Nicte.setLevel(1000), Petry.setLevel(1000), Undine.setLevel(1000), Chroma.setLevel(1000), Zaytus.setLevel(1000), Forest_Druid.setLevel(1000), Neptunius.setLevel(1000), Shygu.setLevel(1000), Lord_Kirk.setLevel(1000), Thert.setLevel(1000), Hosokawa.setLevel(1000), Takeda.setLevel(1000), Hattori.setLevel(1000), Mahatma.setLevel(1000), Edana.setLevel(1000), Dybbuk.setLevel(1000), Jade.setLevel(1000), Hirate.setLevel(1000);
	vector<Mob> quest01 = { e5 }, quest02 = { f1, a1, f1, a1, f1 }, quest03 = { f5, a5 }, quest04 = { f2, a2, e2, w2, f3, a3 },
		quest05 = { w3, e3, w3, e3, w3, e3 }, quest06 = { w4, e1, a4, f4, w1, e4 }, quest07 = { f5, a5, f4, a3, f2, a1 }, quest08 = { e4, w4, w5, e5, w4, e4 },
		quest09 = { w5, f5, e5, a5, w4, f4 }, quest10 = { w5, e5, a5, f5, e5, w5 }, quest11 = { f5, f6, e5, e6, a5, a6 }, quest12 = { e5, w5, f5, e6, f6, w6 },
		quest13 = { a8, a7, a6, a5, a4, a3 }, quest14 = { f7, f6, f5, e7, e6, e6 }, quest15 = { w5, e6, w6, e8, w8 }, quest16 = { a9, f8, a8 },
		quest17 = { w5, e6, w7, e8, w8 }, quest18 = { f7, f6, a6, f5, a7, a8 }, quest19 = { e7, w9, f9, e9 }, quest20 = { f2, a4, f5, a7, f8, a10 },
		quest21 = { w10, a10, w10 }, quest22 = { w9, e10, f10 }, quest23 = { e9, a9, w8, f8, e8 }, quest24 = { f6, a7, f7, a8, f8, a9 },
		quest25 = { w8, w7, w8, w8, w7, w8 }, quest26 = { a9, w7, w8, e7, e8, f10 }, quest27 = { e9, f9, w9, f7, w7, w7 }, quest28 = { a10, a8, a9, a10, a9 },
		quest29 = { a10, w7, f7, e8, a9, a9 }, quest30 = { e10, e10, e10, f10 }, quest31 = { e9, f10, f9, f9, a10, a7 }, quest32 = { w1, a9, f10, e9, a10, w10 },
		quest33 = { e9, a9, a9, f9, a9, f10 }, quest34 = { f8, e9, w9, a9, a10, a10 }, quest35 = { w8, w8, w10, a10, a10, f10 },
		quest36 = { a8, a10, f10, a10, a10, a10 }, quest37 = { e8, a10, e10, f10, f10, e10 }, quest38 = { f10, e10, w10, a10, w10, w10 },
		quest39 = { w9, a10, w10, e10, a10, a10 }, quest40 = { w10, a10, w10, a10, w10, a10 }, quest41 = { e12, e11, a11, f11, a12 },
		quest42 = { a11, a11, e11, a11, e11, a11 }, quest43 = { a8, a11, a10, w10, a12, e12 }, quest44 = { a10, f10, a12, f10, a10, f12 },
		quest45 = { w4, e11, a12, a12, w11, a12 }, quest46 = { a11, a12, a11, f11, a11, f10 }, quest47 = { f12, w11, e12, a12, w12 },
		quest48 = { a11, a11, e12, a11, a11, a13 }, quest49 = { a13, f13, f13, f13 }, quest50 = { f12, f12, f12, f12, f12, f12 },
		quest51 = { a11, e11, a13, a11, e11, a13 }, quest52 = { f13, w13, a13, f12, f12 }, quest53 = { a9, f13, f13, f12, a12, a12 },
		quest54 = { a13, a13, a12, a12, f11, f12 }, quest55 = { a11, f10, a11, e14, f13, a11 }, quest56 = { f13, a13, f13, e13, w12 },
		quest57 = { e10, a13, w12, f13, f13, f13 }, quest58 = { f7, w11, w13, e14, f13, a14 }, quest59 = { a8, f15, a14, f14, w14 },
		quest60 = { f12, w13, a14, f13, a13, e10 }, quest61 = { f13, e13, a13, w12, f12, a12 }, quest62 = { w13, e12, w12, a14, a12, f13 },
		quest63 = { e15, f14, w14, a15 }, quest64 = { e12, a14, e14, w13, e12, f13 }, quest65 = { e13, f12, w11, w12, a14, e14 },
		quest66 = { a14, e13, a11, a14, f13, e13 }, quest67 = { f13, w13, e14, f13, f14, a14 }, quest68 = { a15, e15, f15, w15 },
		quest69 = { f13, a14, e14, f13, a14, f13 }, quest70 = { a11, a14, w13, e14, a14, f14 }, quest71 = { e13, a14, f14, w13, f14, e14 },
		quest72 = { w10, a14, a14, a14, a14, w14 }, quest73 = { w13, w13, f14, a15, a15, e13 }, quest74 = { a14, e14, e14, e14, e14, e14 },
		quest75 = { w15, w15, e15, w15, f15 }, quest76 = { f14, e15, a15, w14, a14, e15 }, quest77 = { w14, a15, w14, e15, a15, w14 },
		quest78 = { w15, w15, w15, w15, f15, f15 }, quest79 = { a15, a15, a15, a15, a15, w14 }, quest80 = { f15, w15, w15, w15, w15, w15 },
		quest81 = { f14, e16, e16, e16, e16 }, quest82 = { w14, a15, f15, a16, f16, f15 }, quest83 = { w15, f15, w15, w15, a16, w16 },
		quest84 = { a16, w15, a16, e16, a17 }, quest85 = { f15, w15, w15, w15, e17, e16 }, quest86 = { a13, a16, a16, a16, a16, f16 },
		quest87 = { e16, f16, f16, f17, a17 }, quest88 = { w15, f16, a16, a16, f16, e17 }, quest89 = { f16, f17, a17, a15, a16, a16 },
		quest90 = { f16, f16, f16, f16, f16, a18 }, quest91 = { e16, e16, a17, f17, a17, w15 }, quest92 = { f17, a18, a18, w17, a17, e16 },
		quest93 = { e18, f16, f16, f16, w16, f18 }, quest94 = { a21, a20, f20, a21 }, quest95 = { e18, e17, a18, e17, e17, e20 },
		quest96 = { a19, a19, w18, w18, f15, e16 }, quest97 = { w18, f19, f19, e18, e18, a19 }, quest98 = { f18, w19, w19, e19, e19, f18 },
		quest99 = { f19, a19, e19, f20, a20, f19 }, quest100 = { a20, w18, w18, a19, w20, f20 }, quest101 = { a22, e21, f20, w20, f22 },
		quest102 = { f23, w21, f20, a20, a21 }, quest103 = { f22, w21, w21, f21, e21 }, quest104 = { a20, f20, e21, a21, a20, f20 },
		quest105 = { f20, e21, f20, w20, e21, f20 }, quest106 = { e21, w22, f23, a23, a22 }, quest107 = { f21, a20, f21, a21, w21, e21 },
		quest108 = { w22, w22, a22, f22, e21, w21 }, quest109 = { e22, f22, a22, w21, e22, w21 }, quest110 = { a22, w22, a22, w21, e22, w22 },
		quest111 = { f23, a22, e23, e23, e22, w22 }, quest112 = { w22, w23, a23, w22, f21, f21 }, quest113 = { w24, a24, e24, f24, f23, f23 },
		quest114 = { a24, a25, a24, f25, e23 }, quest115 = { e23, f23, e23, w25, a24, a23 }, quest116 = { e24, a24, e24, f23, w24, w23 },
		quest117 = { e24, e24, a24, w24, f24, w24 }, quest118 = { f24, a23, a24, f24, f24, w24 }, quest119 = { f25, f25, a26, a26, w25 },
		quest120 = { e27, w27, e27, w27 }, quest121 = { w27, f27, f27, w27 }, quest122 = { a27, e27, f27, w27 }, quest123 = { e27, e27, w27, f27 },
		quest124 = { a28, f27, w27, f27 }, quest125 = { a28, a27, w27, w28 }, quest126 = { f26, w28, w28, w28 }, quest127 = { e26, w27, w27, w28 },
		quest128 = { f27, w28, w29, w29 }, quest129 = { a27, w27, w29, w29 }, quest130 = { e27, w28, w29, w29 }, quest131 = { a26, e26, w29, e29, f27 },
		quest132 = { w29, f29, a27, a26, a28 }, quest133 = { w29, e29, a29, a28 }, quest134 = { a27, w29, a27, f28, a27 },
		quest135 = { w29, w30, a26, a27, a30 }, quest136 = { f26, a30, f27, e30, w28 }, quest137 = { a30, a27, a30, a27, e30 },
		quest138 = { a27, w30, f28, w30, a27, a27 }, quest139 = { w27, w29, a30, a27, e30, a27 }, quest140 = { f27, e30, f28, a30, e27, a27 },
		quest141 = { w29, a30, a30, Nicte }, quest142 = { a30, w29, e29, x }, quest143 = { e30, w29, w30, f25, Ignitor },
		quest144 = { f27, w28, a30, a27, Petry }, quest145 = { e26, e30, w29, e29, Ignitor }, quest146 = { f26, e30, f25, a30, w29, Undine },
		quest147 = { w29, a30, Undine, Petry }, quest148 = { a28, w30, Ignitor, Chroma },
		quest149 = { a28, a28, w28, Undine, Zaytus }, quest150 = { w28, w28, w29, Undine, x },
		quest151 = { e30, e30, w30, w30, Undine,Chroma }, quest152 = { f30, f30, e30, a30, Ignitor, Zaytus },
		quest153 = { e30, w30, Chroma, Nicte, Forest_Druid }, quest154 = { w30, a30, Undine, Zaytus, Ignitor },
		quest155 = { f30, Zaytus, Chroma, Nicte, Forest_Druid }, quest156 = { f30, f30, Undine, x, Forest_Druid, Petry },
		quest157 = { e30, e30, Ignitor, Zaytus, Nicte, Undine }, quest158 = { w30, x, Ignitor, Zaytus, Chroma, Forest_Druid },
		quest159 = { Ignitor, Forest_Druid, Petry, Chroma, x, Undine },
		quest160 = { f30, Ignitor, Undine, Neptunius }, quest161 = { e30, Forest_Druid, Nicte, Undine, Shygu }, quest162 = { e30, f30, Petry, Zaytus, Ignitor, Lord_Kirk },
		quest163 = { a30, Undine, Ignitor, Zaytus, Nicte, Shygu }, quest164 = { f30, Ignitor, Forest_Druid, x, Undine, Thert }, quest165 = { Zaytus, Ignitor, Undine, x, Chroma, Hosokawa },
		quest166 = { Forest_Druid, Undine, Takeda, Shygu }, quest167 = { x, Petry, Neptunius, Hattori }, quest168 = { Zaytus, Petry, Chroma, Mahatma, Edana },
		quest169 = { Nicte, x, Ignitor, Lord_Kirk, Dybbuk }, quest170 = { Petry, Nicte, Chroma, Forest_Druid, Thert, Jade }, quest171 = { Zaytus, Chroma, Hattori, Hirate },
		quest172 = { Undine, x, Nicte, Hosokawa, Edana }, quest173 = { Forest_Druid, Thert, Neptunius, Mahatma }, quest174 = { Zaytus, Ignitor, Lord_Kirk, Hirate, Takeda }, quest175 = { Petry, Nicte, Chroma, Shygu, Takeda, Neptunius }, quest176 = { Thert, Neptunius, Mahatma, Hosokawa },
		quest177 = { Zaytus, Lord_Kirk, Jade, Mahatma, Dybbuk }, quest178 = { Forest_Druid, Jade, Takeda, Hattori, Hirate }, quest179 = { Zaytus, Chroma, Shygu, Hattori, Mahatma, Edana },
		quest180 = { Forest_Druid, Neptunius, Thert, Mahatma, Jade, Dybbuk };

	Nicte.setLevel(1), Petry.setLevel(1), Undine.setLevel(1), Chroma.setLevel(1), Zaytus.setLevel(1), Forest_Druid.setLevel(1), Neptunius.setLevel(1), Shygu.setLevel(1), Lord_Kirk.setLevel(1), Thert.setLevel(1);
	q.insert({ "quest1", quest01 });
	q.insert({ "quest2", quest02 });
	q.insert({ "quest3", quest03 });
	q.insert({ "quest4", quest04 });
	q.insert({ "quest5", quest05 });
	q.insert({ "quest6", quest06 });
	q.insert({ "quest7", quest07 });
	q.insert({ "quest8", quest08 });
	q.insert({ "quest9", quest09 });
	q.insert({ "quest10", quest10 });
	q.insert({ "quest11", quest11 });
	q.insert({ "quest12", quest12 });
	q.insert({ "quest13", quest13 });
	q.insert({ "quest14", quest14 });
	q.insert({ "quest15", quest15 });
	q.insert({ "quest16", quest16 });
	q.insert({ "quest17", quest17 });
	q.insert({ "quest18", quest18 });
	q.insert({ "quest19", quest19 });
	q.insert({ "quest20", quest20 });
	q.insert({ "quest21", quest21 });
	q.insert({ "quest22", quest22 });
	q.insert({ "quest23", quest23 });
	q.insert({ "quest24", quest24 });
	q.insert({ "quest25", quest25 });
	q.insert({ "quest26", quest26 });
	q.insert({ "quest27", quest27 });
	q.insert({ "quest28", quest28 });
	q.insert({ "quest29", quest29 });
	q.insert({ "quest30", quest30 });
	q.insert({ "quest31", quest31 });
	q.insert({ "quest32", quest32 });
	q.insert({ "quest33", quest33 });
	q.insert({ "quest34", quest34 });
	q.insert({ "quest35", quest35 });
	q.insert({ "quest36", quest36 });
	q.insert({ "quest37", quest37 });
	q.insert({ "quest38", quest38 });
	q.insert({ "quest39", quest39 });
	q.insert({ "quest40", quest40 });
	q.insert({ "quest41", quest41 });
	q.insert({ "quest42", quest42 });
	q.insert({ "quest43", quest43 });
	q.insert({ "quest44", quest44 });
	q.insert({ "quest45", quest45 });
	q.insert({ "quest46", quest46 });
	q.insert({ "quest47", quest47 });
	q.insert({ "quest48", quest48 });
	q.insert({ "quest49", quest49 });
	q.insert({ "quest50", quest50 });
	q.insert({ "quest51", quest51 });
	q.insert({ "quest52", quest52 });
	q.insert({ "quest53", quest53 });
	q.insert({ "quest54", quest54 });
	q.insert({ "quest55", quest55 });
	q.insert({ "quest56", quest56 });
	q.insert({ "quest57", quest57 });
	q.insert({ "quest58", quest58 });
	q.insert({ "quest59", quest59 });
	q.insert({ "quest60", quest60 });
	q.insert({ "quest61", quest61 });
	q.insert({ "quest62", quest62 });
	q.insert({ "quest63", quest63 });
	q.insert({ "quest64", quest64 });
	q.insert({ "quest65", quest65 });
	q.insert({ "quest66", quest66 });
	q.insert({ "quest67", quest67 });
	q.insert({ "quest68", quest68 });
	q.insert({ "quest69", quest69 });
	q.insert({ "quest70", quest70 });
	q.insert({ "quest71", quest71 });
	q.insert({ "quest72", quest72 });
	q.insert({ "quest73", quest73 });
	q.insert({ "quest74", quest74 });
	q.insert({ "quest75", quest75 });
	q.insert({ "quest76", quest76 });
	q.insert({ "quest77", quest77 });
	q.insert({ "quest78", quest78 });
	q.insert({ "quest79", quest79 });
	q.insert({ "quest80", quest80 });
	q.insert({ "quest81", quest81 });
	q.insert({ "quest82", quest82 });
	q.insert({ "quest83", quest83 });
	q.insert({ "quest84", quest84 });
	q.insert({ "quest85", quest85 });
	q.insert({ "quest86", quest86 });
	q.insert({ "quest87", quest87 });
	q.insert({ "quest88", quest88 });
	q.insert({ "quest89", quest89 });
	q.insert({ "quest90", quest90 });
	q.insert({ "quest91", quest91 });
	q.insert({ "quest92", quest92 });
	q.insert({ "quest93", quest93 });
	q.insert({ "quest94", quest94 });
	q.insert({ "quest95", quest95 });
	q.insert({ "quest96", quest96 });
	q.insert({ "quest97", quest97 });
	q.insert({ "quest98", quest98 });
	q.insert({ "quest99", quest99 });
	q.insert({ "quest100", quest100 });
	q.insert({ "quest101", quest101 });
	q.insert({ "quest102", quest102 });
	q.insert({ "quest103", quest103 });
	q.insert({ "quest104", quest104 });
	q.insert({ "quest105", quest105 });
	q.insert({ "quest106", quest106 });
	q.insert({ "quest107", quest107 });
	q.insert({ "quest108", quest108 });
	q.insert({ "quest109", quest109 });
	q.insert({ "quest110", quest110 });
	q.insert({ "quest111", quest111 });
	q.insert({ "quest112", quest112 });
	q.insert({ "quest113", quest113 });
	q.insert({ "quest114", quest114 });
	q.insert({ "quest115", quest115 });
	q.insert({ "quest116", quest116 });
	q.insert({ "quest117", quest117 });
	q.insert({ "quest118", quest118 });
	q.insert({ "quest119", quest119 });
	q.insert({ "quest120", quest120 });
	q.insert({ "quest121", quest122 });
	q.insert({ "quest122", quest123 });
	q.insert({ "quest123", quest123 });
	q.insert({ "quest124", quest124 });
	q.insert({ "quest125", quest125 });
	q.insert({ "quest126", quest126 });
	q.insert({ "quest127", quest127 });
	q.insert({ "quest128", quest128 });
	q.insert({ "quest129", quest129 });
	q.insert({ "quest130", quest130 });
	q.insert({ "quest131", quest131 });
	q.insert({ "quest132", quest132 });
	q.insert({ "quest133", quest133 });
	q.insert({ "quest134", quest134 });
	q.insert({ "quest135", quest135 });
	q.insert({ "quest136", quest136 });
	q.insert({ "quest137", quest137 });
	q.insert({ "quest138", quest138 });
	q.insert({ "quest139", quest139 });
	q.insert({ "quest140", quest140 });
	q.insert({ "quest141", quest141 });
	q.insert({ "quest142", quest142 });
	q.insert({ "quest143", quest143 });
	q.insert({ "quest144", quest144 });
	q.insert({ "quest145", quest145 });
	q.insert({ "quest146", quest146 });
	q.insert({ "quest147", quest147 });
	q.insert({ "quest148", quest148 });
	q.insert({ "quest149", quest149 });
	q.insert({ "quest150", quest150 });
	q.insert({ "quest151", quest151 });
	q.insert({ "quest152", quest152 });
	q.insert({ "quest153", quest153 });
	q.insert({ "quest154", quest154 });
	q.insert({ "quest155", quest155 });
	q.insert({ "quest156", quest156 });
	q.insert({ "quest157", quest157 });
	q.insert({ "quest158", quest158 });
	q.insert({ "quest159", quest159 });
	q.insert({ "quest160", quest160 });
	q.insert({ "quest161", quest161 });
	q.insert({ "quest162", quest162 });
	q.insert({ "quest163", quest163 });
	q.insert({ "quest164", quest164 });
	q.insert({ "quest165", quest165 });
	q.insert({ "quest166", quest166 });
	q.insert({ "quest167", quest167 });
	q.insert({ "quest168", quest168 });
	q.insert({ "quest169", quest169 });
	q.insert({ "quest170", quest160 });
	q.insert({ "quest171", quest171 });
	q.insert({ "quest172", quest172 });
	q.insert({ "quest173", quest173 });
	q.insert({ "quest174", quest174 });
	q.insert({ "quest175", quest175 });
	q.insert({ "quest176", quest176 });
	q.insert({ "quest177", quest177 });
	q.insert({ "quest178", quest178 });
	q.insert({ "quest179", quest179 });
	q.insert({ "quest180", quest180 });
	string next;
	double d;
	int i;
	for (int x = 0; x < heroes.size(); x++)
	{
		Heroes.insert({ heroes[x].getName(), heroes[x] });
	}
	for (int x = 0; x < mobs.size(); x++)
	{
		Heroes.insert({ mobs[x].getName(), mobs[x] });
	}
	heats.push_back(Nulla);
	setup >> next;
	while (next != "done")
	{
		Mob H = Heroes.find(next)->second;
		setup >> d;
		if (fmod(d, 1) == 0)
		{
			i = d;
			H.setLevel(i);
			heats.push_back(H);
		}
		else
		{
			H.setLevel(d);
			heats.push_back(H);
		}
		setup >> next;
	}
	setup >> llimit >> ulimit;
	for (int i = 0; i < mobs.size(); i++)
	{
		if ((mobs[i].getFollowers() > (llimit)) && (mobs[i].getFollowers() < ulimit))
		{
			heats.push_back(mobs[i]);
		}
	}
	vector<Mob> enemy;
	setup >> next;
	if (next == "Quest")
	{
		setup >> next;
		enemy = q.find(next)->second;
		setup >> next;
	}
	if (next == "Promotion")
	{
		setup >> next;
		Mob a = Heroes.find(next)->second;
		enemy = q.find(a.quest)->second;
		setup >> next;
		choice = "Promotion";
		idh = a.getId();
	}
	while (next != "done")
	{
		Mob H = Heroes.find(next)->second;
		if (H.getSkillName() != "mob")
		{
			setup >> d;
			if (fmod(d, 1) == 0)
			{
				i = d;
				H.setLevel(i);
				enemy.push_back(H);
			}
			else
			{
				H.setLevel(d);
				enemy.push_back(H);
			}
			setup >> next;
		}
		else
		{
			enemy.push_back(H);
			setup >> next;
		}
	}
	lenemy = enemy;
}
