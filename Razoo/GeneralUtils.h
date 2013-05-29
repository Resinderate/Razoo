/*
	Ronan Murphy   12/05/13
	A file for general utils for the game that didn't quite fit anywhere else. 
*/

#ifndef GENERALUTILS_H
#define GENERALUTILS_H

#include "Player.h"
#include <iostream>
#include <string>


using namespace std;

class GeneralUtils
{
public:
	/*
	Name:	PrintInfo
	Desc:	Prints the general info needed when entering a room in the game. Lots of formatting 
	Args:	p_player : the player obj
	Return:	None
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


	//Referenced from:
	//Author: Arash Partow - 2002
	//URL: http://www.partow.net                                             
	//URL: http://www.partow.net/programming/hashfunctions/index.html

	/*
	Name:	Hash
	Desc:	Hash function that takes strings
	Args:	p_input : string to hash
	Return:	hash : index to place entry at.
	*/
	static unsigned long int Hash(string p_input)
	{
		unsigned int b    = 378551;
		unsigned int a    = 63689;
		unsigned int hash = 0;

		for(std::size_t i = 0; i < p_input.length(); i++)
		{
			hash = hash * a + p_input[i];
			a    = a * b;
		}

		return hash;
	}
};
#endif