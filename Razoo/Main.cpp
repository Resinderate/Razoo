/*
	Ronan Murphy   12/05/13
	A driver program for the text based game Razoo
*/
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

void GameLoop(Player& p_player, Level& p_level, Array<Item>& p_items, Array<Enemy>& p_enemies, Login& p_login);


int main()
{
	int numberOfRooms = 0;
	int numberOfItems = 0;
	int numberOfEnemies = 0;

	Initializer::InitializeSizes("roomsfile.txt", numberOfRooms, "itemsfile.txt", numberOfItems, "enemiesfile.txt", numberOfEnemies);

	HashTable<string, Room> rooms(numberOfRooms, GeneralUtils::Hash);
	string roomsfilename = "roomsfile.txt";
	Level level = Initializer::InitializeRooms(rooms, roomsfilename);

	Array<Item> items(numberOfItems);
	string itemsfilename = "itemsfile.txt";
	Initializer::InitializeItems(items, itemsfilename);

	Array<Enemy> enemies(numberOfEnemies);
	string enemiesfilename = "enemiesfile.txt";
	Initializer::InitializeEnemies(enemies, enemiesfilename);

	Login login;
	Player p1;
	string filename = login.LoginToGame();


	Initializer::InitializePlayer(p1, rooms, items, filename);

	GameLoop(p1, level, items, enemies, login);

	return 0;
}

/*
Name:	GameLoop
Desc:	The main game loop for the game.
Args:	p_player : the used player
		p_level : level for the game
		p_items : existing items
		p_enemies : existing enemies
		p_login : login obj, used for removing players. 
Return:	None
*/
void GameLoop(Player& p_player, Level& p_level, Array<Item>& p_items, Array<Enemy>& p_enemies, Login& p_login)
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
		if(win) //won the game
		{
			cout << "grats you win!" << endl;
			//delete file, game over nothing left to do.
			p_login.RemoveUser(p_player);
		}
		else //dead
		{
			cout << "Oh, you died. Too bad. I deleted your save file. Better luck next time." << endl;
			//delete file.
			p_login.RemoveUser(p_player);
		}
	}


}



