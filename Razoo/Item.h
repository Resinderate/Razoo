#ifndef ITEM_H
#define ITEM_H

#include <string>

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
	Item(string p_name, string p_description, int p_weight, int p_confidence, int p_humor, int p_speed)
	{
		m_name = p_name;
		m_description = p_description;
		m_weight = p_weight;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
	}

	Item()
	{
		m_name = "";
		m_description = "";
		m_weight = 0;
		m_confidence = 0;
		m_humor = 0;
		m_speed = 0;
	}

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

};

#endif