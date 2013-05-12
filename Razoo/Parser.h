#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <algorithm>

class Parser
{
public:
	
	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static bool Parse(std::string& p_input, Player& p_player, Array<Item>& p_items, Array<Enemy>& p_enemies)
	{
		std::transform(p_input.begin(), p_input.end(), p_input.begin(), ::tolower);
		//Key is the word for the string that is useful at the moment.
		std::string key = WordAt(p_input, 0);

		if(key == "go" || key == "move")
			Go(p_input, p_player, p_items, p_enemies);
		else if(key == "examine")
			Examine(p_input, p_player);
		else if(key == "fight")
			Fight(p_player);
		else if(key == "help" || key == "commands")
			Help();
		else if(key == "inventory")
			ViewInventory(p_player);
		else if(key == "pickup" ||key == "take")
			Pickup(p_input, p_player);
		else if(key == "drop" || key == "remove")
			Drop(p_input, p_player);
		else if(key == "save")
			Save(p_player);
		else if(key == "exit")
		{
			Exit(p_player);
			return true;
		}
		else
			cout << "Try 'help' for a list of commands." << endl;
		return false;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static std::string WordAt(std::string& p_input, int p_index)
	{
		std::string output;
		int startpos = 0;
		int endpos;

		for(int i = 0; i < p_index+1; i++)
		{
			endpos = p_input.find_first_of(' ', startpos);
			output = p_input.substr(startpos, endpos - startpos);
			startpos = endpos+1;
		}

		return output;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Go(std::string& p_input, Player& p_player, Array<Item>& p_items, Array<Enemy>& p_enemies)
	{
		std::string key = WordAt(p_input, 1);
		if(p_player.GetCurrentRoom()->GetEnemy() == 0) //must get rid of enemies before moving
		{
			if(key == "north" && p_player.GetCurrentRoom()->GetNorth() != 0)
			{
				p_player.MoveNorth();
				p_player.GetCurrentRoom()->GiveRandomEnemy(p_enemies);
				if(p_player.GetCurrentRoom()->GetInventory() == 0)
					p_player.GetCurrentRoom()->GiveRandomItem(p_items);
				GeneralUtils::PrintInfo(p_player);
				cout << "Went North!" << endl;
			}
			else if(key == "south" && p_player.GetCurrentRoom()->GetSouth() != 0)
			{
				p_player.MoveSouth();
				p_player.GetCurrentRoom()->GiveRandomEnemy(p_enemies);
				if(p_player.GetCurrentRoom()->GetInventory() == 0)
					p_player.GetCurrentRoom()->GiveRandomItem(p_items);
				GeneralUtils::PrintInfo(p_player);
				cout << "Went South!" << endl;
			}
			else if(key == "east" && p_player.GetCurrentRoom()->GetEast() != 0)
			{
				p_player.MoveEast();
				p_player.GetCurrentRoom()->GiveRandomEnemy(p_enemies);
				if(p_player.GetCurrentRoom()->GetInventory() == 0)
					p_player.GetCurrentRoom()->GiveRandomItem(p_items);
				GeneralUtils::PrintInfo(p_player);
				cout << "Went East!" << endl;
			}
			else if(key == "west" && p_player.GetCurrentRoom()->GetWest() != 0)
			{
				p_player.MoveWest();
				p_player.GetCurrentRoom()->GiveRandomEnemy(p_enemies);
				if(p_player.GetCurrentRoom()->GetInventory() == 0)
					p_player.GetCurrentRoom()->GiveRandomItem(p_items);
				GeneralUtils::PrintInfo(p_player);
				cout << "Went West!" << endl;
			}
			else
				cout << "Go where?" << std::endl;
		}
		else
		{
			cout << "You can't move with an enemy blocking your way!" << endl;
		}
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Examine(std::string& p_input, Player& p_player)
	{
		std::string key = WordAt(p_input, 1);

		Item* search = p_player.GetInventory().SearchByName(key); //Players Inventory
		Enemy* newSearch = 0;

		if(search == 0)
		{
			if(p_player.GetCurrentRoom()->GetInventory() != 0)
				search = p_player.GetCurrentRoom()->GetInventory(); //Room
		}
		
		if(search == 0)	//Still found nothing, fill the enemy point if you can.
			newSearch = p_player.GetCurrentRoom()->GetEnemy();


		if(search != 0)
			cout << search->GetDescription() << endl;
		else if(newSearch != 0)
			cout << newSearch->GetDescription() << endl;
		else
			cout << "Whatever you are trying to examine doesn't appear to be in your inventory, or this room!" << endl;
		
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Fight(Player& p_player)
	{
		//Can assume that if they are trying to fight something, and there can only be one enemy in the room, as long as there is actually an enemy present we can go ahead and fight it.
		if(p_player.GetCurrentRoom()->GetEnemy() != 0)
		{
			cout << "How would you like to fend off the animal?\n1. Try and intimidate it using your confidence.\n2. Try and make it laugh using your Humor.\n3. Try and outrun it with your speed." << endl;
			int choice = InputUtils::GetIntInput("Enter your choice: ", 1, 3);

			int playerSkill;
			int enemySkill;

			if(choice == 1)
			{
				playerSkill = p_player.GetConfidence();
				enemySkill = p_player.GetCurrentRoom()->GetEnemy()->GetConfidence();
			}
			else if(choice == 2)
			{
				playerSkill = p_player.GetHumor();
				enemySkill = p_player.GetCurrentRoom()->GetEnemy()->GetHumor();
			}
			else if(choice == 3)
			{
				playerSkill = p_player.GetSpeed();
				enemySkill = p_player.GetCurrentRoom()->GetEnemy()->GetSpeed();
			}

			if(playerSkill >= enemySkill)		//Win
			{
				cout << "You have defeated the enemy!" << endl;
				int skillIncrease = Random::RandomInt(1, 4);
				if(choice == 1)
					p_player.SetConfidence(p_player.GetConfidence() + skillIncrease);
				else if(choice == 2)
					p_player.SetHumor(p_player.GetHumor() + skillIncrease);
				else if(choice == 3)
					p_player.SetSpeed(p_player.GetSpeed() + skillIncrease);

				cout << "You have become more proficient with your chosen method! +" << skillIncrease << " points!" << endl;
				p_player.GetCurrentRoom()->SetEnemy(0);
			}
			else								//loss
			{
				cout << "You have failed to fend off the enemy!" << endl;
				int healthLoss = enemySkill - playerSkill;
				p_player.SetHealth(p_player.GetHealth() - healthLoss);
				cout << "You have lost some health! -" << healthLoss << " points!" << endl;
				p_player.GetCurrentRoom()->SetEnemy(0);
			}
		}
		else
			cout << "I don't see anything to fight here!" << endl;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Help()
	{
		cout << "List of commands:" << endl;
		cout << "\tmove/go <direction>\t: 4 Directions are North, South, East and West" << endl;
		cout << "\texamine <name>\t\t: You can examine enemies, or items" << endl;
		cout << "\tfight <name>\t\t: Fight the animal blocking your way" << endl;
		cout << "\tinventory\t\t: List the items currently in your inventory" << endl;
		cout << "\tpickup/take <name>\t: Pickup an item in the current room" << endl;
		cout << "\tdrop/remove <name>\t: Drop an item currently in your inventory" << endl;
		cout << "\tsave\t\t\t: Saves your game" << endl;
		cout << "\texit\t\t\t: Exits the game (Automatic save)" << endl;
		cout << endl;
		cout << "\tTry to avoid random spaces." << endl;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void ViewInventory(Player& p_player)
	{
		p_player.GetInventory().PrintNames();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Pickup(std::string& p_input, Player& p_player)
	{
		std::string key = WordAt(p_input, 1);
		Item* item = 0;
		if(p_player.GetCurrentRoom()->GetInventory() != 0) //There is something there
		{
			std::string name = p_player.GetCurrentRoom()->GetInventory()->GetName();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			std::transform(key.begin(), key.end(), key.begin(), ::tolower);
			if(name == key) //It matched command
			{
				item = p_player.GetCurrentRoom()->GetInventory();
				bool added = p_player.GetInventory().AddItem(*item);
				p_player.GetCurrentRoom()->SetInventory(0);
				cout << "Picked up " << item->GetName() << "!" << endl;
				p_player.UpdateStats();
				//Test if room.
			}
			else
				cout << "Could not find that item to pickup! Not matched" << endl;
		}
		else
			cout << "Could not find item to pickup! Nothing in room" << endl;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Drop(std::string& p_input, Player& p_player)
	{
		std::string key = WordAt(p_input, 1);
		bool found = p_player.GetInventory().RemoveByName(key);
		if(found)
		{
			cout << "Removed " << key << " from inventory!" << endl;
			p_player.UpdateStats();
		}
		else
			cout << "Could not find that item in your inventory!" << endl;
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Save(Player& p_player)
	{
		p_player.SaveGame();
	}

	/*
		Name:	
		Desc:	
		Args:	
		Return:	
	*/
	static void Exit(Player& p_player)
	{
		p_player.SaveGame();
	}

};
#endif