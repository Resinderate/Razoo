/*
	Ronan Murphy   12/05/13
	A class to initialize the body of the game based off the text files provided. 
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
		Name:	InitializeItems
		Desc:	Fills the array with items, read from a text file.
		Args:	p_itemarray : the given array to fill with items
				p_filename : the file to take the items from
		Return:	None
	*/

	/*
		The datasctructure used is an array.
		The array of items is used as the stock of items that can be randomly chosen for, and be placed in rooms.
		When the items are initialized they are simply made one by one and added, and as the amount of items in known in advance, it can't run into space issues.
		The main benefit of using the array is that when you pick a random number between 0 and N-1, you can access it immediatly, and you don't really care what is inside.
	*/
	//Order(n) n being the amount of items
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
		Name:	InitializeEnemies
		Desc:	Fills the given array with Enemies, read from a text file
		Args:	p_enemies : the array to fill with enemies
				p_filename : the file to take the enemies from
		Return:	None
	*/

	/*
		The datasctructure used is an array.
		The array of enemies is used as the stock of enemies that can be randomly chosen, and be placed in rooms.
		When the enemies are initialized they are simply made one by one and added, and as the amount of items in known in advance, it can't run into space issues.
		The main benefit of using the array is that when you pick a random number between 0 and N-1, you can access it immediatly, and you don't really care what is inside.
		The Enemies are used exactly the same as Items.
	*/
	//Order(n) n being the amount of enemies
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
		Name:	InitializeRooms
		Desc:	Fills a HashTable with rooms from a text file.
		Args:	p_roomtable : the HashTable to fill.
				p_filename : the file to take the rooms from.
		Return:	None
	*/

	/*
		The data structure used is a HashTable.
		It is used as the Rooms contain pointers to other rooms, and cant be fully initialized at one time.
		The Rooms are read in and placed into a HashTable<string, Room> being their name, and themselves.
		Each rooms exits and room names are also put into an arrays, of corresponding index Ie. Room r1, is in slot  roomnames[x] & roomexits[x]

		Then with the Order(c) lookup on the hashtable, I can iterate through all of the rooms at Order(n) and assign them to each other.
		If this was done with an array as a replacement to a hashtable, I think it would be more like Order(n^2)
		HashTable Implementation is close to Order(n)
	*/
	//Order(n) amount of rooms
	static Level& InitializeRooms(HashTable<std::string, Room>& p_roomtable, std::string& p_filename)
	{
		std::ifstream myfile(p_filename);
		//do stuff
		char trash[256];
		char value[256];

		
		//These are terrible names.
		//Some number bigger than I expect there to be rooms.
		//11 implemented right now
		std::string rooms[15];
		std::string roomsandexits[15][4];

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
		Name:	InitializePlayer
		Desc:	Initializes the player given a users "save file" and the containers of Rooms and Items.
		Args:	p_player : player to initialize
				p_rooms : store of existing rooms. Save file refers to room by name, and must be match up.
				p_items : store of existing items. Save file refers to items by name, and must be found.
				p_filename : file to load player from.
		Return:	None
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

	/*
		Name:	InitializeSizes
		Desc:	Initializes the size of all the structures needed for the game.
		Args:	p_roomfile : player to initialize
				p_numRooms : store of existing rooms. Save file refers to room by name, and must be match up.
				p_itemfile : store of existing items. Save file refers to items by name, and must be found.
				p_numItems : file to load player from.
				p_enemyfile
				p_numEnemies
		Return:	None
	*/

	static void InitializeSizes(std::string p_roomfile, int& p_numRooms, std::string p_itemfile, int& p_numItems, std::string p_enemyfile, int& p_numEnemies)
	{
		char trash[256];
		char value[256];

		ifstream roomfile(p_roomfile);
		roomfile.getline(trash, 256);
		roomfile.getline(trash, 256);
		roomfile.getline(value, 256);
		p_numRooms = atoi(value);
		roomfile.close();

		ifstream itemfile(p_itemfile);
		itemfile.getline(trash, 256);
		itemfile.getline(trash, 256);
		itemfile.getline(value, 256);
		p_numItems = atoi(value);
		itemfile.close();

		ifstream enemyfile(p_enemyfile);
		enemyfile.getline(trash, 256);
		enemyfile.getline(trash, 256);
		enemyfile.getline(value, 256);
		p_numEnemies = atoi(value);
		enemyfile.close();
	}
	
	
};
#endif