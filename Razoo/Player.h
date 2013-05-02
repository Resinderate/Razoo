#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Room.h"
#include "Inventory.h"


using namespace std;

class Player
{
private:
	string m_name;
	int m_health;
	int m_confidence;
	int m_humor;
	int m_speed;
	Room* m_currentRoom;
	Inventory m_inventory;
public:
	Player(string p_name, int p_health, int p_confidence, int p_humor, int p_speed, Room* p_currentRoom, Inventory p_inventory)
	{
		m_name = p_name;
		m_health = p_health;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
		m_currentRoom = p_currentRoom;
		m_inventory  = p_inventory;
	}

	string GetName()
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

};

#endif