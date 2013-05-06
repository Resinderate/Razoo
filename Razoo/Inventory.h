#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "DLinkedList.h"

class Inventory
{
private:
	DLinkedList<Item*> m_inventory;
	int m_weight;
	int m_maxWeight;
public:

	int GetWeight()
	{
		return m_weight;
	}

	int GetMaxWeight()
	{
		return m_maxWeight;
	}

	int AddItem(Item* p_item)
	{
		if(p_item->GetWeight + m_weight <= m_maxWeight)
		{
			//add item pointer.
		}
		else
		{
			//Too heavy, error msg.
		}
	}

};
#endif