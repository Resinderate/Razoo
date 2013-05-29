/*
	Ronan Murphy   12/05/13
	A class to represent a room in the game.

	& a container class to keep track of the rooms as a Level.
*/

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "Inventory.h"
#include "Enemy.h"
#include "Random.h"

/*
	Level & Room as a Datastructure
	Sort of set up like a LinkedList, with rooms being the nodes, and the Level being the container.
	Player has access to one room at a time, and can move to any other rooms connected to it.
	It's extremely fast and you dont have to go searching for the appropriate named room, you just have a pointer to it.
	You will never be looking for any rooms that are not directly beside you.
	Never need to Iterate through the rooms.
	Moving to a new room is Order(c)

	Level holds the "head" and "tail".
	Head is mostly used for locating where new players should start,
	Tail is used to check whether the player's current room is the last one, as a win condition.
*/


using namespace std;


class Room
{
private:
	string m_name;
	string m_description;
	Item* m_inventory;
	Room* m_north;
	Room* m_south;
	Room* m_east;
	Room* m_west;
	Enemy* m_enemy;

public:
	/*
		Name:	Room
		Desc:	Constructor for Room
		Args:	p_name : name of the room
				p_desc : desc of the room
				p_north : pointer to the room north of this room
				p_south : pointer to the room south of this room
				p_east : pointer to the room to the east of this room
				p_west : pointer to the room to the east of this room	
	*/
	Room(string p_name, string p_desc, Room* p_north, Room* p_south, Room* p_east, Room* p_west)
	{
		m_name = p_name;
		m_description = p_desc;
		m_north = p_north;
		m_south = p_south;
		m_east = p_east;
		m_west = p_west;
		m_enemy = 0;
		m_inventory = 0;
	}

	/*
		Name:	Room
		Desc:	Default Constructor
		Args:	None
	*/
	Room()
	{
		m_name = "";
		m_description = "";
		m_north = 0;
		m_south = 0;
		m_east = 0;
		m_west = 0;
		m_enemy = 0;
		m_inventory = 0;
	}

	/*
		Name:	Getters & Setters
		Desc:	Methods for manipulating member variables.
		Args:	p_newvalue : where applicable
		Return:	m_var : where applicable
	*/
	string GetName()
	{
		return m_name;
	}

	string GetDesc()
	{
		return m_description;
	}

	Item* GetInventory()
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

	void SetInventory(Item* p_item)
	{
		m_inventory = p_item;
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

	/*
		Name:	GiveRandomEnemy
		Desc:	Fills the room with a random enemy from the array provided. 30% chance that none will be added.
		Args:	p_enemeis : the array of existing enemies to choose from.
		Return:	None
	*/
	//Order(c)
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

	/*
		Name:	GiveRandomItem
		Desc:	Fills the room with a random item from the array provided. 20% chance that none will be added.
		Args:	
		Return:	
	*/
	//Order(c)
	void GiveRandomItem(Array<Item>& p_items)
	{
		
		if(Random::RandomInt(1, 100) > 20)   //80% of getting an item
		{
			int count = p_items.size();
			int index = Random::RandomInt(0, count);
			m_inventory= &p_items[index];
		}
		else
		{
			m_inventory = 0;
		}
	}

};

class Level
{
private:
	Room* m_start;	//The first room where the player will start.
	Room* m_end; //The final room which the player must reach.

public:
	/*
		Name:	Level
		Desc:	Level Constructor
		Args:	p_start : the starting room for the level.
				p_end : the ending room for the level.
		Return:	
	*/
	Level(Room* p_start, Room* p_end)
	{
		m_start = p_start;
		m_end = p_end;
	}

	~Level()
	{
	}

	/*
		Name:	Getters
		Desc:	Methods for retreiving member variables.
		Args:	None
		Return:	m_var : where applicable
	*/
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