#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <algorithm>

class Parser
{
private:
	Player m_player;
	Enemy* m_enemies;
	Item* m_items;

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

	}

	void Examine(std::string p_input)
	{

	}

	void Fight(std::string p_input)
	{

	}

	void Help(std::string p_input)
	{

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