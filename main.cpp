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
#include<string>

#include"map.h"
#include"hero.h"

using namespace std;


int main(){
	//variables used to set up player HitPoints,the level of difficulty, and the direction.
	int customHP;
	int level = 0;
	string direction;
	
	//Map created in map.cpp file but use of extern variable here.
	extern int** map;
	
	//prints the actual dungeon (0- empty, 1-potion, 2-miniTrap, 3-trap, 4-entrance, 5-exit)
	//printMap(map, sizeM);
	
	//clears the terminal
	if(system("cls"))
	{
		system("clear");
	}
	cout << "Welcome To" << endl;
	
	
cout <<" ____                                                       ____                                ___        " << endl;           
cout <<"/\\  _`\\                                                    /\\  _`\\                             /\\_ \\       " << endl;           
cout <<"\\ \\ \\/\\ \\  __  __    ___      __      __    ___     ___    \\ \\ \\/\\_\\  _ __    __     __  __  __\\//\\ \\      __   _ __  " << endl;
cout <<" \\ \\ \\ \\ \\/\\ \\/\\ \\ /' _ `\\  /'_ `\\  /'__`\\ / __`\\ /' _ `\\   \\ \\ \\/_/_/\\`'__\\/'__`\\  /\\ \\/\\ \\/\\ \\ \\ \\ \\   /'__`\\/\\`'__\\ " << endl;
cout <<"  \\ \\ \\_\\ \\ \\ \\_\\ \\/\\ \\/\\ \\/\\ \\ \\ \\/\\  __//\\ \\ \\ \\/\\ \\/\\ \\   \\ \\ \\ \\ \\ \\ \\//\\ \\ \\.\\_\\ \\ \\_/ \\_/ \\ \\_\\ \\_/\\  __/\\ \\ \\/ " << endl;
cout <<"   \\ \\____/\\ \\____/\\ \\_\\ \\_\\ \\____ \\ \\____\\ \\____/\\ \\_\\ \\_\\   \\ \\____/\\ \\_\\\\ \\__/.\\_\\\\ \\___ ___/' /\\____\\ \\____\\\\ \\_\\ " << endl;
cout <<"    \\/___/  \\/___/  \\/_/\\/_/\\/___ \\ \\/____/\\/___/  \\/_/\\/_/    \\/___/  \\/_/ \\/__/\\/_/ \\/__//__/   \\/____/\\/____/ \\/_/ " << endl;
cout <<"                              /\\____/                                                                                 " << endl;
cout <<"                              \\_/__/                                                                                  " << endl;

	
	cout << "Hint: Make console taller" << endl;
	//insert easy medium hard (higher or lower hitPoints
	cout << "Select Difficulty" << endl;
	cout << "1-Easy....(60HP)\n2-Medium..(45HP)\n3-Hard....(30HP)" << endl;
	
	while(true)
	{
		cin >> level;
		//while input is not just an int.
		while(cin.fail()) 
		{
			cout << "Invalid choice, Must be 1, 2, or 3." << endl;
			//clears error from false input
			cin.clear();
			//skips the first 256 characters in the cin and goes to a new line.
			cin.ignore(256,'\n');
			cin >> level;
		}
		//if its an int but not 1-3
		if(level != 1 && level != 2 && level != 3)
		{
			cout << "Invalid choice, Must be 1, 2, or 3." << endl;
			continue;
		}else
		{
			break;
		}
	}
	
	//based on the level set hitpoints accordingly
	switch(level)
	{
		case 1:
			customHP = 60;
			break;
		case 2:
			customHP = 45;
			break;
		case 3:
			customHP = 30;
			break;
	}
	
	//creates player and sets stats
	static Hero h = Hero("Adventurer", customHP, 0,0);
	
	//clears the terminal
	if(system("cls"))
	{
		system("clear");
	}
	
	cout << "You are the 'P'" << endl;
	cout << "The Exit is Marked with an E!"<< endl;
	cout << "Use the wasd keys to move followed by enter" << endl;
	
	//creates playerMap using actual map and the size given (12 in map.h)
	char** playerMap = makePlayerMap(map, sizeM);
	//places player on the map
	playerMap[h.xCord][h.yCord] = 'P';
	
	//prints player map and stats
	printPlayerMap(playerMap, sizeM);
	h.printStats();
	
	//while the player is not at the exit
	while(h.xCord != sizeM && h.yCord != sizeM)
	{
	//sets steps taken use of a static variable.
		static int stepsTaken = 0;
		if(h.xCord == sizeM-1 && h.yCord == sizeM-1){
			cout << endl;
			printWinner();
			cout << "	You Escaped!!" << endl;
			cout << "	Steps Taken: " << stepsTaken << endl;
			cout << "	Score: " << (h.hitPoints*20)-stepsTaken;
			break;
		}
		
		cin >> direction;
		
		//clears the terminal
		if(system("cls"))
		{
			system("clear");
		}
		
		//checks for valid input
		if(direction != "w" && direction != "a" && direction != "s" && direction != "d")
		{
			printInvalidInput();
			cout << "Invalid Input" << endl;
		}
		else
		{
		//move Right code
			if(direction == "d" && h.yCord == sizeM-1)
			{
				printInvalidInput();
				cout << "Cannot go Right" << endl;
			}
			else if (direction == "d")
			{
				stepsTaken += 1;
				playerMap[h.xCord][h.yCord] = ' ';
				h.setYCord(h.yCord+=1);
				getTile(&h, map, playerMap);
				playerMap[h.xCord][h.yCord] = 'P';
				if(!h.isAlive())
				{
					printDead();
					break;
				}
			}
		//move down code
			if(direction == "s" && h.xCord == sizeM-1)
			{
				printInvalidInput();
				cout << "Cannot go Down" << endl;
			}
			else if(direction == "s")
			{
				stepsTaken += 1;
				playerMap[h.xCord][h.yCord] = ' ';
				h.setXCord(h.xCord+=1);
				getTile(&h, map, playerMap);
				playerMap[h.xCord][h.yCord] = 'P';	
				if(!h.isAlive())
				{
					printDead();
					break;
				}
			}
		//move up code
			if(direction == "w" && h.xCord == 0)
			{
				printInvalidInput();
				cout << "Cannot go Up" << endl;
			}
			else if(direction == "w")
			{
				stepsTaken += 1;
				playerMap[h.xCord][h.yCord] = ' ';
				h.setXCord(h.xCord-=1);
				getTile(&h, map, playerMap);
				playerMap[h.xCord][h.yCord] = 'P';
				if(!h.isAlive())
				{
					printDead();
					break;
				}
			}
		//move left code
			if(direction == "a" && h.yCord == 0)
			{
				printInvalidInput();
				cout << "Cannot go Left" << endl;
			}
			else if(direction == "a")
			{
				stepsTaken += 1;
				playerMap[h.xCord][h.yCord] = ' ';
				h.setYCord(h.yCord-=1);
				getTile(&h, map, playerMap);
				playerMap[h.xCord][h.yCord] = 'P';
				if(!h.isAlive())
				{
					printDead();
					break;
				}
			}
		}
		printPlayerMap(playerMap, sizeM);
		h.printStats();
		//cout<< boolalpha << h.isAlive() << endl << endl;
	}
}

