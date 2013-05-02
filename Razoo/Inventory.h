#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "DLinkedList.h"

class Inventory
{
private:
	DLinkedList<Item> m_inventory;
	int m_weight;
	int m_maxWeight;
public:


};
#endif