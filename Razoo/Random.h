/*
	Ronan Murphy   12/05/13
	A Util file for generating random numbers. 
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>      
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Random
{
public:
	
	/*
		Name:	RandomInt
		Desc:	Gets a random int in the range given.
		Args:	p_lo : the lower range of the number to be generated.
				p_hi : the higher range of the number to be generated.
		Return:	
	*/
	static int RandomInt(int p_lo, int p_hi)
	{
		srand (time(NULL));
		return rand() % (p_hi-p_lo) + p_lo;
	}
};
#endif