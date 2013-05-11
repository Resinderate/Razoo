#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Random
{
public:
	//Return random int in the range
	static int RandomInt(int lo, int hi)
	{
		srand (time(NULL));
		return rand() % (hi-lo) + lo;
	}
};
#endif