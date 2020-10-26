/********************************************
DUNGEON CRAWLER
Class: CS 3150-01 C++ Programming
Edited by: Matthew Hall
Last Edit: 10/17/20

Rubric Validation:

Code Quality (including user interface) - Commented and indented code. User interface accepts only valid inputs and is neat. 
											Also I added some ascii art and used fucntion calls to try and keep my code condensed.
										
Logical use of multiple files - Separated my main pieces of my program in to respective files. Hero is contained in hero.h and .cpp,
								map and character map are contained in mapp.h and .cpp, main.cpp is the driver and user interface.
									
Overall Functionality (Could I break it) - Written to handle invalid input when entering a direction (main.cpp 157-161) and when selecting a difficulty(main.cpp 74-96).

Logical use of enum type - enum type was used in the getTile function defined in map.cpp (line 136) to interpret the dungeon map hidden from the user.

Proper use of extern variable - I used the dungeon map as my extern variable. it is defined in map.cpp (line 76) then used as an extern in main.cpp (line 45)

Proper use of static variable - A for loop runs until the player dies or the reaches the end. I created a static variable in that loop called 
								stepsTaken to keep track of moves. (main.cpp line 138)

Logical use of a struct - I used a struct in my hero.h file to represent a hero object. (has hitPoints, xCord, yCord, and name)

Logical use of random number generator - When generating the map (in map.cpp line 40-73) I seed srand with the time and then create a random map.

********************************************/

#ifndef HERO_H
#define HERO_H
#include<string>

using namespace std;

struct Hero
{
		string name;
		int hitPoints;
		int xCord;
		int yCord;
	 
		Hero(string n, int hp, int x, int y);
		Hero();
		
		void printStats(); 
		void setYCord(int);
		void setXCord(int);
		bool isAlive();
};



#endif