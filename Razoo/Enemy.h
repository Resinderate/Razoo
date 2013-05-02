/*
	Ronan Murphy
	A class that represents an enemy in the game.
*/

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

using namespace std;

class Enemy
{
private:
	string m_name;
	int m_confidence;
	int m_humor;
	int m_speed;

public:
	Enemy(string p_name, int p_confidence, int p_humor, int p_speed)
	{
		m_name = p_name;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
	}

	string GetName()
	{
		return m_name;
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

	//Don't think I need setters, atm.

};
#endif
