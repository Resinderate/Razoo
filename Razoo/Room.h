/*
	Ronan Murphy
	A class to represent a room in the game.

	& a container class to keep track of the rooms.
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "Inventory.h"

using namespace std;

class Room
{
private:
	string m_name;
	Inventory m_inventory;
	Room* m_north;
	Room* m_south;
	Room* m_east;
	Room* m_west;

public:
	Room(string p_name, Inventory p_inventory, Room* p_north, Room* p_south, Room* p_east, Room* p_west)
	{
		m_name = p_name;
		m_inventory = p_inventory;
		m_north = p_north;
		m_south = p_south;
		m_east = p_east;
		m_west = p_west;
	}

	string GetName()
	{
		return m_name;
	}

	Inventory& GetInventory()
	{
		return m_inventory;
	}

	Room* GetNoth()
	{
		return m_north;
	}

	Room* GetSouth()
	{
		return m_south;
	}

	Room* GetEast()
	{
		return m_east;
	}

	Room* GetWest()
	{
		return m_west;
	}

	//Don't think I need setters for the time being.

};

//Used for putting the player at the start, if a fresh game?
//Used for checking if the player has reached the end?

class Level
{
private:
	Room* m_start;
	Room* m_end; //The final room which the player must reach.

public:
	Level(Room* p_start, Room* p_end)
	{
		m_start = p_start;
		m_end = p_end;
	}
};
#endif