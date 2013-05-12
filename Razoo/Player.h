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
		Name:	
		Desc:	
		Args:	
		Return:	
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
		Name:	
		Desc:	
		Args:	
		Return:	
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
		Name:	
		Desc:	
		Args:	
		Return:	
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
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void MoveNorth()
	{
		m_currentRoom = m_currentRoom->GetNorth();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void MoveSouth()
	{
		m_currentRoom = m_currentRoom->GetSouth();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void MoveEast()
	{
		m_currentRoom = m_currentRoom->GetEast();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void MoveWest()
	{
		m_currentRoom = m_currentRoom->GetWest();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	bool PickupItem(Item& p_item)
	{
		if(m_inventory.AddItem(p_item))
		{
			m_confidence += p_item.GetConfidence();
			m_humor += p_item.GetHumor();
			m_speed =+ p_item.GetSpeed();
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void SaveGame() //Bad saving of file.
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
		Name:	
		Desc:	
		Args:	
		Return:	
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
		Name:	
		Desc:	
		Args:	
		Return:	
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