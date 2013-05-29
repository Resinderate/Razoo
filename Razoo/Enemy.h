/*
	Ronan Murphy   12/05/13
	A class that represents an enemy in the game.
*/

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy
{
private:
	std::string m_name;
	std::string m_description;
	int m_confidence;
	int m_humor;
	int m_speed;

public:
	/*
		Name:	Enemy
		Desc:	Constructor for enemy
		Args:	p_name : name of enemy
				p_desc : description of enemy
				p_confidence : stat for enemy
				p_humor : stat for enemy
				p_speed : stat for enemy
	*/
	Enemy(std::string p_name, std::string p_description, int p_confidence, int p_humor, int p_speed)
	{
		m_name = p_name;
		m_description = p_description;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
	}

	/*
		Name:	Enemy
		Desc:	Default Constructor
		Args:	None
	*/
	Enemy()
	{
		m_name = "";
		m_description = "";
		m_confidence = 0;
		m_humor = 0;
		m_speed = 0;
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

	std::string GetDescription()
	{
		return m_description;
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
