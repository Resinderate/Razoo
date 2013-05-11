#ifndef GENERALUTILS_H
#define GENERALUTILS_H

#include "Player.h"
#include <iostream>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class Room;

using namespace std;

class GeneralUtils
{
public:
	static void PrintInfo(Player& player)
	{

		system("cls");
		int width = 78;


		int size = player.GetCurrentRoom()->GetName().length();
		int border = ((width - size) /2) -2;

		for(int i = 0; i < border; i++)
			cout << ":";
		string name = player.GetCurrentRoom()->GetName();
		cout << "  " << name << "  ";
		for(int i = 0; i < border; i++)
			cout << ":";
		cout << endl;

		border = 4;
		for(int i = 0; i < border; i++)
			cout << ":";
		cout << "\t\t";
		string health = "Health: " + std::to_string(player.GetHealth());
		cout << health;
		cout << "\t\t\t";
		string confidence = "Confidence: " + std::to_string(player.GetConfidence());
		cout << confidence;
		cout << endl;

		for(int i = 0; i < border; i++)
			cout << ":";
		cout << "\t\t";
		string humor = "Humor: " + std::to_string(player.GetHumor());
		cout << humor;
		cout << "\t\t\t";
		string speed = "Speed: " + std::to_string(player.GetSpeed());
		cout << speed;
		cout << endl;

		for(int i = 0; i < border; i++)
			cout << ":";
		cout << "\t\t";
		string numItems = "# of Items: " + std::to_string(player.GetInventory().Size());
		cout << numItems;
		cout << "\t\t\t";
		string totalWeight = "Weight/MaxWeight: " + std::to_string(player.GetInventory().GetWeight()) + "/" + std::to_string(player.GetInventory().GetMaxWeight());
		cout << totalWeight;
		cout << endl;

		for(int i = 0; i < width; i++)
		{
			cout << ":";
		}
		cout << endl;

		for(int i = 0; i < border; i++)
			cout << ":";
		cout << "\t" << player.GetCurrentRoom()->GetDesc() << endl;

		for(int i = 0; i < border; i++)
			cout << ":";
		cout << endl;

		//if current room directions are not null.

		for(int i = 0; i < border; i++)
			cout << ":";
		cout << "\tLocations from this place:" << endl;		//There will be at least one.

		if(player.GetCurrentRoom()->GetNorth() != 0)
		{
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "\t\t- To the north you can see: " << player.GetCurrentRoom()->GetNorth()->GetName() << endl;
		}

		if(player.GetCurrentRoom()->GetSouth() != 0)
		{
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "\t\t- To the south you can see: " << player.GetCurrentRoom()->GetSouth()->GetName() << endl;
		}

		if(player.GetCurrentRoom()->GetEast() != 0)
		{
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "\t\t- To the east you can see: " << player.GetCurrentRoom()->GetEast()->GetName() << endl;
		}

		if(player.GetCurrentRoom()->GetWest() != 0)
		{
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "\t\t- To the west you can see: " << player.GetCurrentRoom()->GetWest()->GetName() << endl;
		}

		//repeated for the 3 others.


		Array<string> items(player.GetCurrentRoom()->GetInventory().Size());
		items = player.GetCurrentRoom()->GetInventory().GetItemNames();
		if(items.size() > 0)
		{

			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "Items in this location:" << endl;

			for(int i = 0; i < items.size(); i++)
			{
				cout << "\t\t- A " << items[i] << endl;
			}

		}


		for(int i = 0; i < width; i++)
		{
			cout << ":";
		}
		cout << endl;

	}

	static Enemy* GiveRandomEnemy(Array<Enemy>& p_enemies)
	{
		Enemy* result = 0;

		//First see if there will actually be an enemy.
		if(GeneralUtils::RandomInt(1, 100) > 30)   //70% chance of getting an enemy
		{
			int count = p_enemies.size();
			int index = GeneralUtils::RandomInt(0, count);
			result = &(p_enemies[index]);
		}
		else
		{
			return result;
		}
	}

	static Item* GiveRandomItem(Array<Item>& p_items)
	{
		Item* result;
		if(GeneralUtils::RandomInt(1, 100) > 20)   //80% of getting an item
		{
			int count = p_items.size();
			int index = GeneralUtils::RandomInt(0, count);
			result = &(p_items[index]);
			return result;
		}
		else
		{
			return 0;
		}
	}

	/*



	*/
	static unsigned long int Hash(string p_index)
	{
		//need some proper string hash.
		return p_index.length();
	}

	//Return random int in the range
	static int RandomInt(int lo, int hi)
	{
		srand (time(NULL));
		return rand() % (hi-lo) + lo;
	}

};
#endif