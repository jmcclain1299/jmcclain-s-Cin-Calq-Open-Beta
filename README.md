**This new calc was created due to many bugs that arose in the updating the previous Dice Calc (CHeroCalc.) The current calc has not promo2 implementation, and Dice Calc will not have promo2 implementation. The Dice Calc operates on the old battlesystem, which does not mesh well with the new skills and battlesystem. This new calc has many optimizations and improvisations over the existing calc. The current calc does not have anyone to make updates code side. I had the option of learning the old calc and trying to mesh it with the new battlesystem and skills, or make a new one from scratch. I went with the latter, which makes updating the code easier since I understand it's implementation. This allows for any changes to the game code to be implemented quickly. I made design changes that allows for new unit creation to be nearly copy-paste of old heroes with redefinitions for skills for any code team that wishes to take on this project once I leave (I won't be here forever.) I spoke with some of the code team during the planning phase when I decided to take on this project, and one of the biggest driving factors was mention of a few skill functions that could not be implemented as the old Calc could not handle them correctly. I took on this project due to my desire to provide the community with a more effecient, more effective, tool they could use for their solution desires. This calc currently needs support from anyone who wishes to be a betatester. If you wish to betatest, download the files, give it a go, and let me know what you'd like to see different. If you encounter any errors, send me an email at jmcclain1299@gmail.com with the replay and setup you used. Including screenshots of the program output will help me fix any issues.**

This is an open beta for a new calc that is based on the new battle system and has suppost for 2nd promotion quests. Has support for signifying quest/promotion in setup.txt. 

Mob.H is the header file for the calculator. It has the interface for the functions

Mob.cpp is the implementation file for the calculator. It has the behavoir of all the functions.

cin-calq.cpp is main()

setup.txt is the input for the calc//Will work on having input through the program later



```
//Below is an example setup
defile 99.4 //put heroes as heroname all lower case 
geror 99.4 //no spaces/special characters 
dorth 99.4//followed by "space" level, level.promotion 
rua 99.4 //if there is a promotions
cliodhna 99.4
pokerface 99.4
done //use "done" when through entering heroes
0//lower follower limit
0//upper follower limit, the closer they are and the fewer heroes,
f30//the faster the output. start putting enemy units here.\\ You can start by saying Quest quest1 or quest2 or whatvers
shaman 1000//use hero level/hero level.promotion for heroes\\or Promotion heroname, all lowercase, to solve that heroes promo quest
nicte 1000//use f1-30, e1-30, a1-30, w1-30 for mobs\\I think it has a check for worldboss, not sure if it's working.
ignitor 1000                                        \\It does check if the line size is 1 for a wb solution, but theoretically
neil 1000                                           \\A wb can be in a dungeon/dq.  Use done when done in any event.
done // use done when done
//there are no checks for valid lineups of oddball sizes
//Send jmcclain1299 a private message for any requests for implementations
//Send jmcclain1299@gmail.com bug reports including a replay and your setup.txt so I know what to fix
//If a hero name is mispelled, the program will crash. this will be fixed later.
```
