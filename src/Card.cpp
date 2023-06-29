#include "Card.h"


Card_Class::Card_Class()
{
	//H-Heart,D-Diamond,S-Spade,C-Clover
	symbol_set = new char[4]; 
	symbol_set[0] = 'C'; symbol_set[1] = 'D'; 
	symbol_set[2] = 'H'; symbol_set[3] = 'S';

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			card c;
			c.symbol = symbol_set[i];
			
			if (j == 1)
			{
				c.val = j + 13; //the value of Ace card should be highest = 14
			}
			else
			{
				c.val = j;
			}

			c.player_id = -1;
			card_deck.push_back(c);
		}
	}
}

Card_Class::~Card_Class()
{
	delete[] symbol_set;
}

