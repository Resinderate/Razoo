/*
	Ronan Murphy   12/05/13
	A class representing a player in the game. 
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <fstream>

#include "Room.h"
#include "Inventory.h"
#include "Array.h"


class Player
{
private:
	std::string m_name;
	int m_health;
	int m_confidence;
	int m_humor;
	int m_speed;
	Room* m_currentRoom;
	Inventory m_inventory;
public:
	/*
		Name:	Player
		Desc:	Constructor for the player
		Args:	p_name : name of the player
				p_health : health of the player
				p_confidence : stat
				p_humor : stat
				p_speed : stat
				p_currentRoom : currentRoom of the player.
				p_inventory : inventory obj for the player.
	*/
	Player(std::string p_name, int p_health, int p_confidence, int p_humor, int p_speed, Room* p_currentRoom, Inventory p_inventory)
	{
		m_name = p_name;
		m_health = p_health;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
		m_currentRoom = p_currentRoom;	//Name of current room for saving.
		m_inventory  = p_inventory;		//List of item names, for saving
	}

	/*
		Name:	Player
		Desc:	Default Constructor
		Args:	None
	*/
	Player()
	{
		m_name = "";
		m_health = 0;
		m_confidence = 0;
		m_humor = 0;
		m_speed = 0;
		m_currentRoom = 0;
		m_inventory  = 0;
	}

	
	~Player()
	{

	}

	/*
		Name:	Getters & Setters
		Desc:	Methods for manipulating member variables.
		Args:	p_newvalue : where applicable
		Return:	m_var : where applicable
	*/
	std::string GetName()
	{
		return m_name;
	}

	int GetHealth()
	{
		return m_health;
	}

	int GetConfidence()
	{
		return m_confidence;
	}

	int GetHumor()
	{
		return m_humor;
	}

	int GetSpeed()
	{
		return m_speed;
	}

	Room* GetCurrentRoom()
	{
		return m_currentRoom;
	}

	Inventory& GetInventory()
	{
		return m_inventory;
	}

	void SetName(std::string p_name)
	{
		m_name =p_name;
	}

	void SetHealth(int p_health)
	{
		m_health = p_health;
	}

	void SetConfidence(int p_confidence)
	{
		m_confidence = p_confidence;
	}

	void SetHumor(int p_humor)
	{
		m_humor = p_humor;
	}

	void SetSpeed(int p_speed)
	{
		m_speed = p_speed;
	}

	void SetCurrentRoom(Room* p_currentRoom)
	{
		m_currentRoom = p_currentRoom;
	}

	void SetInventory(Inventory p_inventory)
	{
		m_inventory = p_inventory;
	}

	/*
		Name:	MoveNorth
		Desc:	Moves the player north from it's current room.
		Args:	None
		Return:	None
	*/
	void MoveNorth()
	{
		m_currentRoom = m_currentRoom->GetNorth();
	}

	/*
		Name:	MoveSouth
		Desc:	Moves the player south from it's current room.
		Args:	None
		Return:	None
	*/
	void MoveSouth()
	{
		m_currentRoom = m_currentRoom->GetSouth();
	}

	/*
		Name:	MoveEast
		Desc:	Moves the player east from it's current room.
		Args:	None
		Return:	None
	*/
	void MoveEast()
	{
		m_currentRoom = m_currentRoom->GetEast();
	}

	/*
		Name:	MoveWest
		Desc:	Moves the player west from it's current room.
		Args:	None
		Return:	None
	*/
	void MoveWest()
	{
		m_currentRoom = m_currentRoom->GetWest();
	}

	/*
		Name:	PickupItem
		Desc:	Add the given item to the players inventory if possible
		Args:	p_item : the item to add to the playes inventory
		Return:	bool : true if added, false otherwise.
	*/
	bool PickupItem(Item& p_item)
	{
		if(m_inventory.AddItem(p_item))
		{
			UpdateStats();
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
		Name:	SaveGame
		Desc:	Saves the players current progress in the game to their save file.
		Args:	None
		Return:	None
	*/
	void SaveGame() //Unefficient saving of file.
	{
		ReduceStats();
		ofstream savefile(m_name + ".txt");
		savefile << "********** " << m_name << " player file **********" << endl;
		savefile << "Username::" << endl;
		savefile << m_name << endl;
		savefile << "Health::" << endl;
		savefile << m_health << endl;
		savefile << "Confidence::" << endl;
		savefile << m_confidence << endl;
		savefile << "Humor::" << endl;
		savefile << m_humor << endl;
		savefile << "Speed::" << endl;
		savefile << m_speed << endl;
		savefile << "CurrentRoom::" << endl;
		if(m_currentRoom != 0)
		{
			savefile << m_currentRoom->GetName() << endl;
			savefile << "Inventory::::" << endl;
			savefile << "No. of Items::" << endl;
			savefile << m_inventory.Size() << endl;
			m_inventory.PrintNamesFile(savefile);
		}
		savefile.close();
	}

	/*
		Name:	UpdateStats
		Desc:	Increase the stats of the player based on the items they have
		Args:	None
		Return:	None
	*/
	void UpdateStats()
	{
		int count = m_inventory.Size();

		for(int i = 0; i <count; i++)
		{
			m_inventory.TotalStats(m_confidence, m_humor, m_speed);
		}
	}

	/*
		Name:	ReduceStats
		Desc:	Reduced the players stats based on the items they are holding. Used before saving so that inventory can be stored properly without boosting players stats
		Args:	None
		Return:	None
	*/
	void ReduceStats()
	{
		int minusConfidence = 0;
		int minusHumor = 0;
		int minusSpeed = 0;

		int count = m_inventory.Size();

		for(int i = 0; i <count; i++)
		{
			m_inventory.TotalStats(minusConfidence, minusHumor, minusSpeed);
		}

		m_confidence -= minusConfidence;
		m_humor -= minusHumor;
		m_speed -= minusSpeed;
	}
};

#endif