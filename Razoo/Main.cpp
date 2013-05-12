#include "HashTable.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "Room.h"
#include "Initializer.h"
#include "Login.h"
#include "Parser.h"
#include "InputUtils.h"
#include "GeneralUtils.h"

#include <iostream>
#include <crtdbg.h>

using namespace std;

void GameLoop(Player& p_player, Level& p_level, Array<Item>& p_items, Array<Enemy>& p_enemy);


int main()
{
	
	//Give it a prime size?

	//Need to sort number of things before hand.
	//Text File?

	HashTable<string, Room> rooms(11, GeneralUtils::Hash);
	string roomsfilename = "roomsfile.txt";
	Level level = Initializer::InitializeRooms(rooms, roomsfilename);

	Array<Item> items(5);
	string itemsfilename = "itemsfile.txt";
	Initializer::InitializeItems(items, itemsfilename);

	Array<Enemy> enemies(7);
	string enemiesfilename = "enemiesfile.txt";
	Initializer::InitializeEnemies(enemies, enemiesfilename);
	
	Login login;
	Player p1;
	string filename = login.LoginToGame();


	Initializer::InitializePlayer(p1, rooms, items, filename);
	//NOW WE HAVE A PLAYER TO WORK WITH


	GameLoop(p1, level, items, enemies);
	

	//NEED A PROPER HASH FUNCTION
	return 0;
}

void GameLoop(Player& p_player, Level& p_level, Array<Item>& p_items, Array<Enemy>& p_enemies)
{
	
	//Checks on health and room.
	//win or lose

	bool exit = false;
	bool win = false;
	bool dead = false;


	GeneralUtils::PrintInfo(p_player);
	while(!exit && !win && !dead)
	{
		string input = InputUtils::GetString(">");

		//true if they wish to exit.
		//Dealing with input
		exit = Parser::Parse(input, p_player, p_items, p_enemies);

		if(p_player.GetCurrentRoom()->GetName() == p_level.GetEnd()->GetName())
			win = true;
		else if(p_player.GetHealth() <= 0)
			dead = true;
	}

	if(!exit)
	{
		if(win)
		{
			cout << "grats you win!" << endl;
			//delete file, game over nothing left to do.
		}
		else //dead
		{
			cout << "Oh, you died. Too bad. I deleted your save file. Better luck next time." << endl;
			//delete file.
		}
	}
	

}



