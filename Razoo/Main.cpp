#include <iostream>
#include "HashTable.h"
#include "DLinkedList.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "Room.h"

using namespace std;

unsigned long int Hash(int p_index)
{
	return p_index;
}

int main()
{
	//Call initialiser with file names.
	//One file with all the rooms

	
	HashTable<int, Room> rooms(0, Hash);
	//One file with all the items
	//One file with all the enemies.


	//Arrays for stuff that is filled dynamically.
	//HashMaps for stuff that needs to be refered to by name in the text files.

	//All the items - Array. When you go into a room, then it's random what there will be. // Maybe you can have a HashTable, so that the items are persistant. Makes saving harder.
	//All the rooms - HashTable or w/e,
	//All the Enemies - Array. Array when you go into the room it makes a random enemy, possible to have none.

	//Inventories are LinkedLists.
	//When being constructed, then

	//NEED A HASH FUNCTION
}