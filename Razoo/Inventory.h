#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "DLinkedList.h"
#include "Array.h"
#include <algorithm>
#include <iostream>
#include <fstream>

class Inventory
{
private:
	DLinkedList<Item> m_inventory;
	int m_weight;
	int m_maxWeight;
public:
	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	Inventory(int p_maxWeight)
	{
		m_maxWeight = p_maxWeight;
		m_weight = 0;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	Inventory()
	{
		m_maxWeight = 100;
		m_weight = 0;
	}

	~Inventory()
	{
		
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	int GetWeight()
	{
		return m_weight;
	}

	int GetMaxWeight()
	{
		return m_maxWeight;
	}

	int Size()
	{
		return m_inventory.GetCount();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void PrintNames()
	{
		int count = m_inventory.GetCount();

		if(count > 0)
		{
			DListIterator<Item> itr = m_inventory.GetIterator();
			itr.Start();
			for(int i = 0; i < count; i++)
			{	
				cout << itr.Item().GetName() << std::endl;
				itr.Forth();
			}
		}
		
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void PrintNamesFormated()
	{
		int count = m_inventory.GetCount();

		if(count > 0)
		{
			DListIterator<Item> itr = m_inventory.GetIterator();
			itr.Start();
			for(int i = 0; i < count; i++)
			{
				for(int j = 0; j < 4; j++)
						cout << ":";
				
				cout << "\t- A " << itr.Item().GetName() << std::endl;
				itr.Forth();
			}
		}
		
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void PrintNamesFile(std::ofstream& out)
	{
		int count = m_inventory.GetCount();
		Array<std::string> content(count);

		if(count > 0)
		{
			DListIterator<Item> itr = m_inventory.GetIterator();
			itr.Start();

			for(int i = 0; i < count; i++)
			{
				out << itr.Item().GetName() << std::endl;
				itr.Forth();
			}
		}
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	bool AddItem(Item p_item)
	{
		if(p_item.GetWeight() + m_weight <= m_maxWeight)
		{
			m_inventory.Append(p_item);
			m_weight += p_item.GetWeight();
		}
		else
		{
			return false;
		}
		return true;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	Item* SearchByName(std::string p_name)
	{
		DListIterator<Item> itr = m_inventory.GetIterator();
		itr.Start();
		std::transform(p_name.begin(), p_name.end(), p_name.begin(), ::tolower);
		while(itr.Valid())
		{
			std::string search = itr.Item().GetName();
			std::transform(search.begin(), search.end(), search.begin(), ::tolower);
			if(search == p_name)
				return &(itr.Item());
			else
				itr.Forth();
		}
		//Not found.
		Item i;
		return 0;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	bool RemoveByName(std::string p_name)
	{
		DListIterator<Item> itr = m_inventory.GetIterator();
		itr.Start();
		std::transform(p_name.begin(), p_name.end(), p_name.begin(), ::tolower);
		if(m_inventory.GetCount() != 0)
		{
			while(itr.Valid())
			{
				std::string search = itr.Item().GetName();
				std::transform(search.begin(), search.end(), search.begin(), ::tolower);
				if(search == p_name)
				{
					m_weight -= itr.Item().GetWeight();
					m_inventory.Remove(itr);
					return true;
				}
				else
					itr.Forth();
			}
		}
		return false;
	}
	
	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	void TotalStats(int& p_confidence, int& p_humor, int& p_speed)
	{
		DListIterator<Item> itr = m_inventory.GetIterator();
		itr.Start();

		for(int i = 0; i < m_inventory.GetCount(); i++)
		{
			p_confidence += itr.Item().GetConfidence();
			p_humor += itr.Item().GetHumor();
			p_speed += itr.Item().GetSpeed();
			itr.Forth();
		}
	}

};
#endif