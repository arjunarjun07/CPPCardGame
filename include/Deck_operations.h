#pragma once
#include "Card.h"

class Deck_operations_class
{
private:
	vector<Card_Class::card> deck;

public:

	Deck_operations_class();

	Deck_operations_class(vector<Card_Class::card> deck_param);

	vector<Card_Class::card> shuffle();
	vector<Card_Class::card> Sort();
	static int random_num_gen(int min = 0, int max = 51); // min & max inclusive
	void print_deck();

	static bool sort_by_symbols(const Card_Class::card &lhs, const Card_Class::card &rhs);

	~Deck_operations_class();

};
