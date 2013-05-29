/*
	Ronan Murphy   12/05/13
	A file container class for a DLinkedList, that acts as an inventory for the player in game. 
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "DLinkedList.h"
#include "Array.h"
#include <algorithm>
#include <iostream>
#include <fstream>


/*
	Inventory as Datastructure
	Container with a DLinkedList.
	The player has an inventory which isn't limited by size, but by a weight, a seperate variable.
	Size could be anything so a LinkedList is ideal. No Resizing.
	The Printing of all of the contents is usually done in batches ie. everything at once, which is o(n), being similar performance compared to other Dstructures.
	The only drawbacks are are removing named items , and examining named items, which involves iterating through the contents until the correct node is found.
*/

class Inventory
{
private:
	DLinkedList<Item> m_inventory;
	int m_weight;
	int m_maxWeight;
public:
	/*
		Name:	Inventory
		Desc:	Constructor for Inventory
		Args:	p_maxWeight : maximum weight the inventory will allow from Items
	*/
	Inventory(int p_maxWeight)
	{
		m_maxWeight = p_maxWeight;
		m_weight = 0;
	}

	/*
		Name:	Inventory
		Desc:	Default Constructor
		Args:	None
		Return:	None
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
		Name:	Getters & Setters
		Desc:	Methods for manipulating member variables.
		Args:	p_newvalue : where applicable
		Return:	m_var : where applicable
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
		Name:	PrintNames
		Desc:	print the present items in the inventory, with no formatting.
		Args:	None
		Return:	None
	*/
	//Order(n)
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
		Name:	PrintNamesFormated
		Desc:	Print the present items in the inventory, with formatting suited to the game loop.
		Args:	None
		Return:	None
	*/
	//Order(n)
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
		Name:	PrintNamesFile
		Desc:	Prints the present items in the inventory, with no formatting and into the given ofstream
		Args:	p_out : ofstream to print to.
		Return:	None
	*/
	//Order(n)
	void PrintNamesFile(std::ofstream& p_out)
	{
		int count = m_inventory.GetCount();
		Array<std::string> content(count);

		if(count > 0)
		{
			DListIterator<Item> itr = m_inventory.GetIterator();
			itr.Start();

			for(int i = 0; i < count; i++)
			{
				p_out << itr.Item().GetName() << std::endl;
				itr.Forth();
			}
		}
	}

	/*
		Name:	AddItem
		Desc:	Add the given item to the inventory if it doesnt go over the weight limit.
		Args:	p_item : item to add to the inventory
		Return:	bool : true if added, false if not.
	*/
	//Order(c)
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
		Name:	SearchByName
		Desc:	Searches for the given item name int he inventory
		Args:	p_name : name of the item you are searching for.
		Return:	Item* : pointer to item found. Is null if nothing found.
	*/
	//Order(n)
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
		Name:	RemoveByName
		Desc:	Removes the given item named if it is found in the inventory
		Args:	p_name : name of the item you want to remove
		Return:	bool : true if removed, flase if not found.
	*/
	//Order(n)
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
		Name:	TotalStats
		Desc:	Totals up the stats of all the items present in the inventory, and assigns them to the given variables.
		Args:	p_confidence
				p_humor
				p_speed
		Return:	None
	*/
	//Order(n)
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