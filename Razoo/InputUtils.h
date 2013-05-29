/*
	Ronan Murphy   12/05/13
	A Util file related to the getting of valid input from the user. 
*/

#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <iostream>
#include <regex>

using namespace std;
class InputUtils
{
public:
	//***************************************
	//		Input Utils
	//***************************************

	//----------------------------------------------------
	//Name:				GetStringRegex
	//Description:		Gets a string input, after prompting the given message, and comparing it to a given regex.
	//Args:				p_promt, the message to be displayed before requesting input
	//					p_regex, the regex the input must match to be valid input.
	//Return:			string, a valid string.
	//----------------------------------------------------
	// Order(c)
	static string GetStringRegex(string p_prompt, string p_regex)
	{
		std::regex reg(p_regex);
		string input;
		cout << p_prompt << endl;
		cin >> input;
		while(1)
		{
		
			if(cin.good())
			{
				if(regex_match(input, reg))
				{
					break;
				}
				else
				{
					cout << "Invalid Input, Please Re-Enter.." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> input;
				}
			}
			else
			{
				cout << "Invalid Input, Please Re-Enter.." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> input;
			}
		}
		return input;
	}

	/*
		Name:	GetString
		Desc:	Gets a string from the user, after prompting a given message
		Args:	p_prompt : message to display to the user.
		Return:	input : users inputter string.
	*/
	static string GetString(string p_prompt)
	{
		string input;
		cout << p_prompt;
		char in[256];
		cin.getline(in, 256);
		input.assign(in);
		while(1)
		{
			if(cin.good())
			{
				break;
			}
			else //Can't think of something that would trigger this.
			{
				cout << "\nInvalid Input, Please Re-Enter..\n>";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> input;
			}
		}
		return input;
	}

	//----------------------------------------------------
	//Name:				GetIntInput
	//Description:		Gets an int input, after prompting the given message,and validating that it is an int
	//Args:				p_promt, the message to be displayed before requesting input
	//Return:			int, a valid int.
	//----------------------------------------------------
	// Order(c)
	static int GetIntInput(string p_prompt)
	{
		int input;
		cout << p_prompt << endl;
		cin >> input;
		while(cin.fail())
		{
			cout << "Invalid Input, Please Re-Enter.." << endl;
			cin.clear(cin.good());
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> input;
		}
		return input;
	}

	//----------------------------------------------------
	//Name:				GetIntInput
	//Description:		Gets an int input, after prompting the given message,and validating that it is an int and in the specified range.
	//Args:				p_promt, the message to be displayed before requesting input
	//					p_lo, the lower valid range of the int
	//					p_hi, the higher valid range of the int.
	//Return:			int, a valid int.
	//----------------------------------------------------
	// Order(c)
	static int GetIntInput(string p_prompt, int p_lo, int p_hi)
	{
		int input;
		cout << p_prompt << endl;
		cin >> input;
		while(1)
		{
		
			if(cin.good())
			{
				if((input >= p_lo && input <= p_hi))
				{
					break;
				}
				else
				{
					cout << "Invalid Input, Please Re-Enter.." << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> input;
				}
			}
			else
			{
				cout << "Invalid Input, Please Re-Enter.." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> input;
			}
		}
		return input;
	}

	

};
#endif