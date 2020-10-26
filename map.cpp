/********************************************
DUNGEON CRAWLER
Class: CS 3150-01 C++ Programming
Edited by: Matthew Hall
Last Edit: 10/22/20

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


#include<iostream>
#include<ctime>
#include <iomanip>
#include"map.h"
#include"hero.h"

using namespace std;

//use of random number generator
int randomNumber()
{
	return rand()%7 +1;
}

int** makeMap(int x)
{
	//seed Random number
	srand(time(NULL));
	
	//Create 2D array for map
	int** map = {};
	map = new int*[x];
	
	//fill up map with values
	for(int i = 0; i < x; i++)
	{
		map[i] = new int[x];
		for(int j = 0; j < x; j++)
		{
			int rando = randomNumber();
			if(rando > 3)
			{
				map[i][j] = 0;
			}else
			{
				map[i][j] = rando;
			}
		}
	}
	map[0][0] = 4; //sets entrance to 4
	map[x-1][x-1] = 5;// sets exit to 5
	return map;
}

//make a new map of size sizeM (12)
int** map = makeMap(sizeM);

void printMap(int** map, int size)
{
	//print out map
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

char** makePlayerMap(int** map, int size)
{	
	//Create 2D array for map
	char** playerMap;
	playerMap = new char*[size];
	//fill up map with values
	for(int i = 0; i < size; i++)
	{
		playerMap[i] = new char[size];
		for(int j = 0; j < size; j++)
		{
			if(map[i][j] == ending)
			{
				//put an E where the exit is
				playerMap[i][j] = 'E';
			}
			else
			{
				//mark all other tiles with an X
				playerMap[i][j] = 'X';
			}
		}
	}
	return playerMap;
}

void printPlayerMap(char** playerMap, int size)
{
	//print out players map
	cout << "     ";
	cout << setfill('_') << setw(size*2) << "_"<<endl;
	cout << endl;
	for(int i = 0; i < size; i++)
	{
		cout<< "   | ";
		for(int j = 0; j < size; j++)
		{
			cout << playerMap[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << "     ";
	cout << setfill('_') << setw(size*2) << "_"<<endl;
}

void getTile(struct Hero* h, int** map, char** playerMap)
{
	if(playerMap[h->xCord][h->yCord] == ' ')
	{
		printEmpty();
	}
	else
	{
		//cout << "new spot" << endl;
		int tile = map[h->xCord][h->yCord];
		if(tile == empty)
		{
			printEmpty();
		}
		else if (tile == potion)
		{
			printPotion();
			h->hitPoints += 5;
		}
		else if (tile == miniTrap)
		{
			printMiniTrap();
			h->hitPoints -=5;
		}
		else if (tile == trap)
		{
			printTrap();
			h->hitPoints -=10;
		}
	}
}

void printDead()
{
	cout <<"	      .-. " << endl;
	cout <<"	     (o.o) " << endl;
	cout <<"	      |=| " << endl;
	cout <<"	     __|__ " << endl;
	cout <<"	   //.=|=.\\\\ " << endl;
	cout <<"	  // .=|=. \\\\ " << endl;
	cout <<"	  \\\\ .=|=. // " << endl;
	cout <<"	   \\\\(_=_)// " << endl;
	cout <<"	    (:| |:) " << endl;
	cout <<"	     || || " << endl;
	cout <<"	     () () " << endl;
	cout <<"	     || || " << endl;
	cout <<"	     || || " << endl;
	cout <<"	    ==' '== " << endl;
	cout <<"	    You Dead" << endl;
}

void printEmpty()
{
	cout << "|,',',',|---|',|'|???????|'|,'|---|,',',',|" << endl;
	cout << "|.'.'.'.|:::|'.|'|???????|'|.'|:::|.'.'.'.|" << endl;
	cout << "|.'.'.'.|---|','   /%%%\\   ','|---|.'.'.'.|" << endl;
	cout << "|.'.'.'.|===:'    /%%%%%\\    ':===|.'.'.'.|" << endl;
	cout << "|.'.'.'.|%%%%%%%%%%%%%%%%%%%%%%%%%|.'.'.'.|" << endl;
	cout << "|.'.'.','       /%%%%%%%%%\\       ','.'.'.|" << endl;
	cout << "|.'.'.'        /%%%%%%%%%%%\\        ','.'.|" << endl;
	cout << "Tile empty" << endl;
}

void printPotion()
{
	cout << endl;
	cout << endl;
	cout <<"	     |~|       " << endl;
	cout <<"	     |_|       " << endl;
	cout <<"	   .'   `.     " << endl;
	cout <<"	   `.___.'     " << endl;
	cout << endl;
	cout << "You found a Potion! (+5 HitPoints)" << endl;
}

void printMiniTrap()
{
	cout << endl;
	cout <<"	        ,--.!, " << endl;
	cout <<"	     __/   -*- " << endl;
	cout <<"	   ,d08b.  '|` " << endl;
	cout <<"	   0088MM      " << endl;
	cout <<"	   `9MMP'      " << endl;
	cout << endl;
	cout << "You've stumbled upon a mini trap! (-5 HitPoints)" << endl;	
}

void printTrap()
{
	cout <<"	               , . ' " << endl;
	cout <<"	     |0|- -. '`.-` - ' " << endl;
	cout <<"	   .-`+'-.   `.' -,.'. " << endl;
	cout <<"	   | .-. |     ` .  ` " << endl;
	cout <<"	   |(0.0)| 			" << endl;
	cout <<"	   |>|=|<| 			" << endl;
	cout <<"	   `-._.-' 			" << endl;
	cout << "You've stumbled upon a trap! (-10 HitPoints)" << endl;
}

void printInvalidInput()
{
	cout << "	  ___  " << endl;
	cout << "	 |__ \\ " << endl;
	cout << "	    ) |" << endl;
	cout << "	   / / " << endl;
	cout << "	  |_|  " << endl;
	cout << "	  (_)  " << endl;
	cout << endl;	
}

void printWinner()
{
	cout << "	   _______ " << endl;
	cout << "	  |       | " << endl;
	cout << "	 (|  You  |) " << endl;
	cout << "	  |  Win  | " << endl;
	cout << "	   \\     / " << endl;
	cout << "	    `---' " << endl;
	cout << "	    _|_|_ " << endl;
}