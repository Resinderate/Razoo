#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item
{
private:
	string m_name;
	int m_weight;
	int m_confidence;
	int m_humor;
	int m_speed;

public:
	Item(string p_name, int p_weight, int p_confidence, int p_humor, int p_speed)
	{
		m_name = p_name;
		m_weight = p_weight;
		m_confidence = p_confidence;
		m_humor = p_humor;
		m_speed = p_speed;
	}

	string GetName()
	{
		return m_name;
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

	//Again, don't think I'll need setters here for the time being.


};

#endif