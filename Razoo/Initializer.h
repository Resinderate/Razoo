/*
	Ronan Murphy
	A class to initialize the body of the game based off the text files provided.
	Needs some thinking.
*/

#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "Item.h"
#include "Enemy.h"
#include "Room.h"
#include "Player.h"
#include "HashTable.h"
#include <fstream>

class Initializer
{
private:
	//Gets the value after a tab, which is the format of these files.
	string getValue()
	{

	}
public:
	static void InitializeItems(Item* p_itemarray, std::string p_filename)
	{
		std::ifstream myfile(p_filename);

		//do stuff
	}

	static void InitializeEnemies(Enemy* p_enemyarray, std::string p_filename)
	{
		std::ifstream myfile(p_filename);
		//do stuff
	}

	static void InitializeRooms(HashTable<std::string, Room> p_roomtable, std::string p_filename)
	{
		std::ifstream myfile(p_filename);
		//do stuff
	}

	static void InitializePlayer(Player& p_player, std::string p_filename)
	{
		//filename in should be determined by the login.
		//do stuff
	}
};
#endif