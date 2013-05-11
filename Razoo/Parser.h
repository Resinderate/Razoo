#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <algorithm>

class Parser
{
private:
	Player m_player;
	Array<Enemy> m_enemies;
	Array<Item> m_items;

	std::string WordAt(std::string p_input, int p_index)
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

	void Go(std::string p_input)
	{
		std::string key = WordAt(p_input, 1);

		if(key == "north" && m_player.GetCurrentRoom()->GetNorth() != 0)
		{
			m_player.MoveNorth();
			m_player.GetCurrentRoom()->GiveRandomEnemy(m_enemies);
			m_player.GetCurrentRoom()->GiveRandomItem(m_items);
			cout << "Went North!" << endl;
		}
		else if(key == "south" && m_player.GetCurrentRoom()->GetSouth() != 0)
		{
			m_player.MoveSouth();
			m_player.GetCurrentRoom()->GiveRandomEnemy(m_enemies);
			m_player.GetCurrentRoom()->GiveRandomItem(m_items);
		}
		else if(key == "east" && m_player.GetCurrentRoom()->GetEast() != 0)
		{
			m_player.MoveEast();
			m_player.GetCurrentRoom()->GiveRandomEnemy(m_enemies);
			m_player.GetCurrentRoom()->GiveRandomItem(m_items);
		}
		else if(key == "west" && m_player.GetCurrentRoom()->GetWest() != 0)
		{
			m_player.MoveWest();
			m_player.GetCurrentRoom()->GiveRandomEnemy(m_enemies);
			m_player.GetCurrentRoom()->GiveRandomItem(m_items);
		}
		else
			cout << "Go where?" << std::endl;
	}

	void Examine(std::string p_input)
	{
		std::string key = WordAt(p_input, 1);

		Item* search = m_player.GetInventory().SearchByName(key);
		if(search == 0)
			search = m_player.GetCurrentRoom()->GetInventory().SearchByName(key);

		if(search != 0)
			cout <<  search->GetDescription() << endl;
		else
			cout << "The item you are trying to examine doesn't appear to be in your inventory, or this room!" << endl;
	}

	void Fight(std::string p_input)
	{
		//Can assume that if they are trying to fight something, and there can only be one enemy in the room, as long as there is actually an enemy present we can go ahead and fight it.
		if(m_player.GetCurrentRoom()->GetEnemy() != 0)
		{
			//Fight scene, maybe new method
		}
		else
			cout << "I don't see anything to fight here!" << endl;
	}

	void Help(std::string p_input)
	{
		//print help
	}

	void ViewInventory(std::string p_input)
	{


	}

	void Pickup(std::string p_input)
	{

	}

	void Drop(std::string p_input)
	{

	}

	void Save(std::string p_input)
	{

	}

	void Exit(std::string p_input)
	{

	}

public:
	Parser(Player& p_player, Array<Enemy>& p_enemies, Array<Item>& p_items)
	{
		m_player = p_player;
		m_enemies = p_enemies;
		m_items = p_items;
	}

	Parser()
	{
		//wut
	}

	~Parser()
	{

	}

	void Parse(std::string p_input)
	{
		std::transform(p_input.begin(), p_input.end(), p_input.begin(), ::tolower);
		//Key is the word for the string that is useful at the moment.
		std::string key = WordAt(p_input, 0);

		if(key == "go" || key == "move")
			Go(p_input);
		else if(key == "examine")
			Examine(p_input);
		else if(key == "fight")
			Fight(p_input);
		else if(key == "help" || key == "commands")
			Help(p_input);
		else if(key == "inventory")
			ViewInventory(p_input);
		else if(key == "pickup" ||key == "take")
			Pickup(p_input);
		else if(key == "drop" || key == "remove")
			Drop(p_input);
		else if(key == "save")
			Save(p_input);
		else if(key == "exit")
			Exit(p_input);
		
	}

};
#endif