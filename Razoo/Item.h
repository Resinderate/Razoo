/*
	Ronan Murphy   12/05/13
	A class that represents an item in the game. 
*/

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using namespace std;

class Item
{
private:
	string m_name;
	string m_description;
	int m_weight;
	int m_confidence;
	int m_humor;
	int m_speed;

public:
	/*
		Name:	Item
		Desc:	Constructor for Item
		Args:	p_name : name of item
				p_description : desc of item
				p_weight : weight of item
				p_confidence : stat on item
				p_humor : stat on item
				p_speed : stat on item
	*/
	Item(string p_name, string p_description, int p_weight, int p_confidence, int p_humor, int p_speed)
	{
		m_name = p_name;
		m_description = p_description;
		m_weight = p_weight;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
	}

	/*
		Name:	Item
		Desc:	Default Constructor
		Args:	None
	*/
	Item()
	{
		m_name = "";
		m_description = "";
		m_weight = 0;
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
	string GetName()
	{
		return m_name;
	}

	string GetDescription()
	{
		return m_description;
	}

	int GetWeight()
	{
		return m_weight;
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

	/*
		Name:	PrintFormatted
		Desc:	Prints the item in a suitable way for the gameloop
		Args:	None
		Return:	None
	*/
	void PrintFormatted()
	{
		for(int j = 0; j < 4; j++)
			cout << ":";
				
		cout << "\t- A " << m_name << std::endl;
	}

};

#endif