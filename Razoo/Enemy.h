/*
	Ronan Murphy
	A class that represents an enemy in the game.
*/

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy
{
private:
	std::string m_name;
	int m_confidence;
	int m_humor;
	int m_speed;

public:
	Enemy(std::string p_name, int p_confidence, int p_humor, int p_speed)
	{
		m_name = p_name;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
	}

	std::string GetName()
	{
		return m_name;
	}

	int GetConfidence()
	{
		return Enemy::m_confidence;
	}

	int GetHumor()
	{
		return m_humor;
	}

	int GetSpeed()
	{
		return m_speed;
	}

};
#endif
