/*
	Ronan Murphy
	A class to represent a room in the game.

	& a container class to keep track of the rooms.
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "Inventory.h"
#include "Enemy.h"
#include "Random.h"




using namespace std;

class Room
{
private:
	string m_name;
	string m_description;
	Inventory m_inventory;
	Room* m_north;
	Room* m_south;
	Room* m_east;
	Room* m_west;
	Enemy* m_enemy;

public:
	Room(string p_name, string p_desc, Room* p_north, Room* p_south, Room* p_east, Room* p_west)
	{
		m_name = p_name;
		m_description = p_desc;
		m_north = p_north;
		m_south = p_south;
		m_east = p_east;
		m_west = p_west;
		m_enemy = 0;
	}

	Room()
	{

	}

	string GetName()
	{
		return m_name;
	}

	string GetDesc()
	{
		return m_description;
	}

	Inventory& GetInventory()
	{
		return m_inventory;
	}

	Room* GetNorth()
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

	Enemy* GetEnemy()
	{
		return m_enemy;
	}

	void SetNorth(Room* p_north)
	{
		m_north = p_north;
	}

	void SetSouth(Room* p_south)
	{
		m_south = p_south;
	}

	void SetEast(Room* p_east)
	{
		m_east = p_east;
	}

	void SetWest(Room* p_west)
	{
		m_west = p_west;
	}

	void SetEnemy(Enemy* p_enemy)
	{
		m_enemy = p_enemy;
	}

	
	void GiveRandomEnemy(Array<Enemy>& p_enemies)
	{
		//First see if there will actually be an enemy.
		if(Random::RandomInt(1, 100) > 30)   //70% chance of getting an enemy
		{
			int count = p_enemies.size();
			int index = Random::RandomInt(0, count);
			m_enemy = &(p_enemies[index]);
		}
		else
		{
			m_enemy = 0;
		}
	}

	void GiveRandomItem(Array<Item>& p_items)
	{
		Item* item;
		if(Random::RandomInt(1, 100) > 20)   //80% of getting an item
		{
			int count = p_items.size();
			int index = Random::RandomInt(0, count);
			item = &(p_items[index]);
			m_inventory.AddItem(item);
		}
		//else dont add anything
	}

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

	~Level()
	{
	}

	Room* GetStart()
	{
		return m_start;
	}

	Room* GetEnd()
	{
		return m_end;
	}

};
#endif