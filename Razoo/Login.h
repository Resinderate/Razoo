/*
	Ronan Murphy   12/05/13
	A class used for the login of players. Focused on the encapsulation of functions like encrypt(). 
*/

#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "Player.h"
#include "InputUtils.h"
#include <algorithm>
#include <fstream>
#include "HashTable.h"
#include "Initializer.h"
#include "GeneralUtils.h"


class Login
{
private:
	/*
		Name:	CreateNewPlayer
		Desc:	Way of getting a usable "Save File" by creating a new one, in the form of a new user.
		Args:	None
		Return:	string : name of the save file to be used.
	*/
	std::string CreateNewPlayer()
	{
		//Make new, enter name and password.
		std::string username = InputUtils::GetStringRegex("Enter a username: ", "[a-zA-z0-9]{1,30}");
		ifstream checkName(username + ".txt");
		while(checkName)
		{
			username = InputUtils::GetStringRegex("That username is taken, enter another: ", "[a-zA-z0-9]{1,30}");
			checkName.open(username + ".txt");
		}
		std::string password = InputUtils::GetStringRegex("Enter a password: ", "[a-zA-z0-9]{1,30}");

		system("cls");
		system("cls");
		cout << "You are located in the southern-most part of the zoo, in the restaurant. All of the animals have broken free and are running amock in the zoo. This includes many dangerous animals so you must make your way to the carpark on the north side of the zoo, so you can escape." << endl;
		cout << "Press Enter to continue!" << endl;
		cin.ignore();
		cin.ignore();
		system("cls");

		//Distribute points
		int points = 40;
		int confidence = 0;
		int humor = 0;
		int speed = 0;
		cout << "You have 3 attributes. Confidence, Humor and Speed. All 3 will help you to deal with different animals in the zoo. You have 40 points to distribute between these 3 values." << endl;
		confidence = InputUtils::GetIntInput("How many points would you like to put into Confidence?", 0, points);
		points -= confidence;
		cout << "You have " << points << " points left!" << endl;
		humor = InputUtils::GetIntInput("How many points would you like to put into Humor?", 0, points);
		points -= humor;
		speed = points; //rest of points put into speed.
		cout << "Great! The remaining " << points << " points will be placed into Speed for you. " << endl;
		cout << "Press Enter to continue!" << endl;
		cin.ignore();
		cin.ignore();
		//Have the 3 values now.
		
		ifstream playerDefaultsFile("defaultplayer.txt");
		char trash[256];
		char value[256];
		playerDefaultsFile.getline(trash, 256);
		playerDefaultsFile.getline(trash, 256);
		playerDefaultsFile.getline(value, 256);
		int health = atoi(value);
		playerDefaultsFile.getline(trash, 256);
		playerDefaultsFile.getline(value, 256);
		std::string startRoom(value);
		playerDefaultsFile.close();

		//make file using sample. Using username as the filename
		ofstream outfile(username + ".txt");
		outfile << "********** " << username << " player file **********" << endl;
		outfile << "Username::" << endl;
		outfile << username << endl;
		outfile << "Health::" << endl;
		outfile << health << endl;
		outfile << "Confidence::" << endl;
		outfile << confidence << endl;
		outfile << "Humor::" << endl;
		outfile << humor << endl;
		outfile << "Speed::" << endl;
		outfile << speed << endl;
		outfile << "CurrentRoom::" << endl;
		outfile << startRoom << endl;
		outfile << "Inventory::::" << endl;
		outfile << "No. of Items::" << endl;
		outfile << 0 << endl;					//No items in inventory a the start of the game.
		outfile.close();


		//Store name and password. encrypted.
		ofstream usersfile("usersfile.txt", ios::app);
		usersfile << encrypt(username) << endl;
		usersfile << encrypt(password) << endl;
		usersfile << "*********" << endl;
		usersfile.close();

		return username + ".txt";
	}

	/*
		Name:	LogInPlayer
		Desc:	Way of getting a usable "Save File" by accessing an existing one based on user given credetials
		Args:	None
		Return:	string : name of the save file to be used.
	*/
	std::string LogInPlayer()
	{
		//Read in Users file.
		HashTable<std::string, std::string> logins(50, GeneralUtils::Hash); //Some sort of size.

		ifstream usersfile("usersfile.txt");
		char trash[256];
		char value[256];
		std::string cipheruser = "";
		std::string cipherpass = "";
		usersfile.getline(trash, 256); //header

		while (true) {
			usersfile.getline(value, 256);
			cipheruser.assign(value);
			usersfile.getline(value, 256);
			cipherpass.assign(value);
			usersfile.getline(trash, 256);
			if( usersfile.eof())
				break;
			logins.Insert(decrypt(cipheruser), decrypt(cipherpass));
		}

		
		//Enter name and pw
		//2 stage check.
		//Order(c)
		std::string username = InputUtils::GetStringRegex("Please enter your username:", "[a-zA-Z0-9]{1,30}");
		HashEntry<std::string, std::string>* result = logins.Find(username);

		while(result == 0)
		{
			cout << "Cannot find a user by that name," << endl;
			std::string username = InputUtils::GetStringRegex("please try another username:", "[a-zA-Z0-9]{1,30}");
			HashEntry<std::string, std::string>* result = logins.Find(username);
		}

		std::string password = InputUtils::GetStringRegex("Please enter your password:", "[a-zA-Z0-9]{1,30}");

		while(result->m_data != password)
		{
			cout << "That password does not match the username " << username << "," << endl;
			std::string password = InputUtils::GetStringRegex("please another password:", "[a-zA-Z0-9]{1,30}");
		}

		return username + ".txt";
	}

	/*
		Name:	encrypt
		Desc:	encrpyts given text into ciphertext using a simple substitution cipher
		Args:	p_plaintext : text to encrypt
		Return:	string : ciphertext
	*/
	std::string encrypt(std::string p_plaintext)
	{
		int offset = 6;
		std::string output = "";
        
		std::transform(p_plaintext.begin(), p_plaintext.end(), p_plaintext.begin(), ::tolower);

        for(int i = 0; i < p_plaintext.length(); i++)
        {
            int currentChar = p_plaintext.at(i);
            currentChar += offset;
            
			output.append(1, (char)currentChar);
        }

        return output;
	}

	/*
		Name:	decrypt
		Desc:	decrypts given cipher text based on the previous encrypt function.
		Args:	p_ciphertext : text to decipher
		Return:	string : plaintext
	*/
	std::string decrypt(std::string p_ciphertext)
	{
		int offset = 6;
		std::string output = "";
        
		std::transform(p_ciphertext.begin(), p_ciphertext.end(), p_ciphertext.begin(), ::tolower);

        for(int i = 0; i < p_ciphertext.length(); i++)
        {
            int currentChar = p_ciphertext.at(i);
            currentChar -= offset;
            
			output.append(1, (char)currentChar);
        }

        return output;
	}

	

public:

	std::string LoginToGame()
	{
		//Log in to existing  OR  make new account.
		int choice = InputUtils::GetIntInput("Would you like to:\n\t1. Log in to existing account.\n\t2. Make a new account.", 1, 2);
		std::string filename;
	
		if(choice == 1)
			filename = LogInPlayer();
		else
			filename = CreateNewPlayer();

		return filename;
	}

	/*
		Name:	RemoveUser
		Desc:	Removes the given users save file and their login details for the usersfile.
		Args:	p_player : the player to remove
		Return:	None
	*/
	//Order(n) n being the amount of users.
	void RemoveUser(Player& p_player)
	{
		string del = p_player.GetName() + ".txt";
		remove(del.c_str());

		HashTable<std::string, std::string> logins(50, GeneralUtils::Hash); //Some sort of size.
		std::string names[50];

		ifstream usersfile("usersfile.txt");
		char trash[256];
		char value[256];
		std::string cipheruser = "";
		std::string cipherpass = "";
		usersfile.getline(trash, 256); //header

		int i = 0;
		while (true) {
			usersfile.getline(value, 256);
			cipheruser.assign(value);
			usersfile.getline(value, 256);
			cipherpass.assign(value);
			usersfile.getline(trash, 256);
			if( usersfile.eof())
				break;
			logins.Insert(decrypt(cipheruser), decrypt(cipherpass));
			names[i] = decrypt(cipheruser);
			i++;
		}
		usersfile.close();

		logins.Remove(p_player.GetName());

		ofstream outfile("usersfile.txt");

		outfile << "******* USERS FILE ***********" << std::endl;
		int count = i + 1;
		cout << "count : " << count << endl;
		for(int j = 0; j < count; j++)
		{
			if(logins.Find(names[j]) != 0)
			{
				std::string name = names[j];
				outfile << encrypt(name) << endl;
				cout << "after print name" << endl;
			
				std::string pass = logins.Find(names[j])->m_data;
				cout << "after assigning entry->data as name." << endl;
				outfile << encrypt(pass) << endl;
				cout << "after print pass" << endl;
				outfile << "*********" << endl;
			}
		}
	}
};
#endif