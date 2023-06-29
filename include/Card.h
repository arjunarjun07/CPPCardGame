#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Card_Class
{

public:
	Card_Class();
	
	struct card
	{
		int  val;
		char symbol;
		int player_id;
	};

	~Card_Class();

	char *symbol_set;
	vector<card> card_deck;

};