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

void GameLoop(Parser& parser, Player& player, Level& level);

int main()
{
	
	//Give it a prime size?

	//Need to sort number of things before hand.
	//Text File?

	HashTable<string, Room> rooms(5, GeneralUtils::Hash);
	Level level = Initializer::InitializeRooms(rooms, "roomsfile.txt");

	Array<Item> items(3);
	Initializer::InitializeItems(items, "itemsfile.txt");



	Array<Enemy> enemies(3);
	Initializer::InitializeEnemies(enemies, "enemiesfile.txt");

	Login login;
	Player p1;
	string filename = login.LoginToGame();
	Initializer::InitializePlayer(p1, rooms, items, 3, filename);

	//NOW WE HAVE A PLAYER TO WORK WITH
	Parser parser(p1, enemies, items);
	GameLoop(parser, p1, level);

	
	cin.ignore();


	//NEED A PROPER HASH FUNCTION
	//Need random enemies and items in rooms when you move.
	return 0;
}

void GameLoop(Parser& parser, Player& player, Level& level)
{

	//Checks on health and room.
	//win or lose

	GeneralUtils::PrintInfo(player);

	string input = InputUtils::GetString(">");

	/*
	while(player.GetCurrentRoom() != level.GetEnd() && player.GetHealth() > 0)
	{
		GeneralUtils::PrintInfo(player);

		string input = InputUtils::GetString(">");
	}
	*/


}


