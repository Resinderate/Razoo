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
#include "Array.h"
#include "GeneralUtils.h"
#include <fstream>
#include <stdlib.h>


class Initializer
{
public:
	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void InitializeItems(Array<Item>& p_itemarray, std::string& p_filename)
	{
		std::ifstream myfile(p_filename);

		//do stuff
		char trash[256];
		char value[256];

		int count;

		myfile.getline(trash, 256);
		myfile.getline(trash, 256);
		myfile.getline(value, 256); //Get # of items.
		count = atoi(value);

		std::string name;
		std::string desc;
		int weight;
		int confidence;
		int humor;
		int speed;

		for(int i = 0; i < count; i++)
		{
			myfile.getline(trash, 256);	//Linebreak
			myfile.getline(trash, 256);	//Name tag
			myfile.getline(value, 256);	//Name
			name.assign(value);

			myfile.getline(trash, 256); //Desc teg
			myfile.getline(value, 256); //Desc
			desc.assign(value);

			myfile.getline(trash, 256);	//Weight tag
			myfile.getline(value, 256);	//weight
			weight = atoi(value);

			myfile.getline(trash, 256);	//Confidence tag
			myfile.getline(value, 256);	//Confidence
			confidence = atoi(value);

			myfile.getline(trash, 256);	//Humor tag
			myfile.getline(value, 256);	//Humor
			humor = atoi(value);

			myfile.getline(trash, 256);	//Speed tag
			myfile.getline(value, 256);	//Speed
			speed = atoi(value);

			Item temp(name, desc, weight, confidence, humor, speed);
			p_itemarray[i] = temp;
		}
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void InitializeEnemies(Array<Enemy>& p_enemyarray, std::string& p_filename)
	{
		std::ifstream myfile(p_filename);


		//do stuff
		char trash[256];
		char value[256];

		int count;

		myfile.getline(trash, 256);
		myfile.getline(trash, 256);
		myfile.getline(value, 256); //Get # of items.
		count = atoi(value);

		std::string name;
		std::string desc;
		int confidence;
		int humor;
		int speed;

		for(int i = 0; i < count; i++)
		{
			myfile.getline(trash, 256);	//Linebreak
			myfile.getline(trash, 256);	//Name tag
			myfile.getline(value, 256);	//Name
			name.assign(value);

			myfile.getline(trash, 256); //Desc teg
			myfile.getline(value, 256); //Desc
			desc.assign(value);

			myfile.getline(trash, 256);	//Confidence tag
			myfile.getline(value, 256);	//Confidence
			confidence = atoi(value);

			myfile.getline(trash, 256);	//Humor tag
			myfile.getline(value, 256);	//Humor
			humor = atoi(value);

			myfile.getline(trash, 256);	//Speed tag
			myfile.getline(value, 256);	//Speed
			speed = atoi(value);

			Enemy temp(name, desc, confidence, humor, speed);
			p_enemyarray[i] = temp;
		}
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static Level& InitializeRooms(HashTable<std::string, Room>& p_roomtable, std::string& p_filename)
	{
		std::ifstream myfile(p_filename);
		//do stuff
		char trash[256];
		char value[256];

		//These are terrible names.
		//Some number bigger than I expect there to be rooms.
		std::string rooms[20];
		std::string roomsandexits[20][4];

		int count;

		//Getting the header out of the way & finding out how many rooms there are.
		myfile.getline(trash, 256);
		myfile.getline(trash, 256);
		myfile.getline(value, 256); //Get # of rooms.
		count = atoi(value); //Convert to int.

		std::string name;
		std::string desc;
		std::string north;
		std::string south;
		std::string east;
		std::string west;

		Room* temp = 0;

		for(int i = 0; i < count; i++)
		{
			myfile.getline(trash, 256);	//Line break.
			myfile.getline(trash, 256);	//Name tag
			myfile.getline(value, 256); //Take in the name.
			name.assign(value);			//convet to std::string.

			myfile.getline(trash, 256); //Desc tag
			myfile.getline(value, 256);	//Take in the desc
			desc.assign(value);

			myfile.getline(trash, 256);	//Exits tag
			myfile.getline(value, 256);	//north
			north.assign(value);
			myfile.getline(value, 256);	//south
			south.assign(value);
			myfile.getline(value, 256);	//east
			east.assign(value);
			myfile.getline(value, 256);	//west
			west.assign(value);

			roomsandexits[i][0] = north;
			roomsandexits[i][1] = south;
			roomsandexits[i][2] = east;
			roomsandexits[i][3] = west;

			Room room(name, desc, temp, temp, temp, temp); //Pointers to other rooms are initially null
			rooms[i] = name;
			p_roomtable.Insert(room.GetName(), room);

		}

		//Now I have:
		//HashTable of Roomes, with their Name as Key, Room as Value.
		//An array of rooms names
		//An array of an array of strings. The exits north, south, east and west. In the same indexs as their rooms.
		//Lots of arrays, of 4 strings, the north south east ans west.

		//Now have to go through and set the pointers manually.

		for(int i = 0; i < count; i++)
		{
			//Each Room, 4 pointers. NSEW
			if(roomsandexits[i][0] != "*")
				p_roomtable.Find(rooms[i])->m_data.SetNorth(&p_roomtable.Find(roomsandexits[i][0])->m_data);
			if(roomsandexits[i][1] != "*")
				p_roomtable.Find(rooms[i])->m_data.SetSouth(&p_roomtable.Find(roomsandexits[i][1])->m_data);
			if(roomsandexits[i][2] != "*")
				p_roomtable.Find(rooms[i])->m_data.SetEast(&p_roomtable.Find(roomsandexits[i][2])->m_data);
			if(roomsandexits[i][3] != "*")
				p_roomtable.Find(rooms[i])->m_data.SetWest(&p_roomtable.Find(roomsandexits[i][3])->m_data);
		}

		//End of level is last one defined in the file.
		Level level(&p_roomtable.Find(rooms[0])->m_data, &p_roomtable.Find(rooms[count-1])->m_data);
		return level;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void InitializePlayer(Player& p_player, HashTable<string, Room>& p_rooms, Array<Item>& p_items, std::string& p_filename)
	{
		ifstream playerfile(p_filename);

		char trash[256];
		char value[256];

		int inventorycount = 0;

		std::string name;
		int health;
		int confidence;
		int humor;
		int speed;
		std::string room;
		Room* currentRoom;
		Inventory inventory(100); //Max weight  Hard coded.

		//reading in values from file
		playerfile.getline(trash, 256);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		name.assign(value);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		health = atoi(value);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		confidence = atoi(value);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		humor = atoi(value);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		speed = atoi(value);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		room.assign(value);
		currentRoom = &(p_rooms.Find(room)->m_data);
		playerfile.getline(trash, 256);
		playerfile.getline(trash, 256);
		playerfile.getline(value, 256);
		inventorycount = atoi(value);
		
		Player p1(name, health, confidence, humor, speed, currentRoom, inventory);
		p_player = p1;

		for(int i = 0; i < inventorycount; i++)
		{
			playerfile.getline(value, 256);
			std::string item(value);
			int count = p_items.size();
			for(int j = 0; j < count; j++)
			{
				if(p_items[j].GetName() == item)
				{
					p_player.GetInventory().AddItem(p_items[j]);
				}
			}
		}
		p_player.UpdateStats();
		
	}
	
	
};
#endif