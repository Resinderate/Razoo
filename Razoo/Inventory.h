#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "DLinkedList.h"
#include "Array.h"
#include <algorithm>

class Inventory
{
private:
	DLinkedList<Item*> m_inventory;
	int m_weight;
	int m_maxWeight;
public:
	Inventory(int p_maxWeight)
	{
		m_maxWeight = p_maxWeight;
		m_weight = 0;
	}

	Inventory()
	{
		m_maxWeight = 100;
		m_weight = 0;
	}

	~Inventory()
	{
		
	}

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

	Array<std::string>& GetItemNames()
	{
		int count = m_inventory.GetCount();
		Array<std::string> content(count);

		if(count != 0)
		{
			Array<std::string> content(count);
			DListIterator<Item*> itr = m_inventory.GetIterator();
			itr.Start();
			for(int i = 0; i < count; i++)
			{
				content.insert(itr.Item()->GetName(), i);
				itr.Forth();
			}
			return content;
		}
		else
			return content; //size will be 0
	}

	
	bool AddItem(Item* p_item)
	{
		if(p_item->GetWeight() + m_weight <= m_maxWeight)
		{
			m_inventory.Append(p_item);
		}
		else
		{
			return false;
		}
		return true;
	}

	Item* SearchByName(std::string p_name)
	{
		DListIterator<Item*> itr = m_inventory.GetIterator();
		itr.Start();
		std::transform(p_name.begin(), p_name.end(), p_name.begin(), ::tolower);
		for(int i = 0; i < m_inventory.GetCount(); i++)
		{
			std::string search = itr.Item()->GetName();
			std::transform(search.begin(), search.end(), search.begin(), ::tolower);
			if(search == p_name)
				return itr.Item();
			else
				itr.Forth();
		}
		//Not found.
		return 0;
	}
	

};
#endif