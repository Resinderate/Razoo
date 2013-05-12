#ifndef GENERALUTILS_H
#define GENERALUTILS_H

#include "Player.h"
#include <iostream>


using namespace std;

class GeneralUtils
{
public:
	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
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
		for(int i = 0; i < border; i++)
				cout << ":";
		cout << endl;

		//repeated for the 3 others.


		//Array<string> items = player.GetCurrentRoom()->GetInventory().GetItemNames();
		
		if(player.GetCurrentRoom()->GetInventory() != 0)
		{
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << endl;
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "\tItems in this location:" << endl;
			if(player.GetCurrentRoom()->GetInventory() == 0)
				cout << "Its actually null" << endl;
			player.GetCurrentRoom()->GetInventory()->PrintFormatted();
			
		}

		if(player.GetCurrentRoom()->GetEnemy() != 0)
		{
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << endl;
			for(int i = 0; i < border; i++)
				cout << ":";
			cout << "\t- A  " << player.GetCurrentRoom()->GetEnemy()->GetName() << " is blocking your way!" << endl;
		}


		for(int i = 0; i < width; i++)
		{
			cout << ":";
		}
		cout << endl;

	}

	

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static unsigned long int Hash(string p_index)
	{
		//need some proper string hash.
		return p_index.length();
	}

	

};
#endif