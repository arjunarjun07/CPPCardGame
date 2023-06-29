#include "Deck_operations.h"
#include <string>

int return_char_hash(char ch)
{
	int hash = 0;
	switch (ch)
	{
	case 'C':
		hash = 1000;
		break;
	case 'D':
		hash = 2000;
		break;
	case 'H':
		hash = 3000;
		break;
	case 'S':
		hash = 4000;
		break;
	}
	return hash;
}

bool Deck_operations_class::sort_by_symbols(const Card_Class::card &lhs, const Card_Class::card &rhs)
{
	int L = return_char_hash(lhs.symbol) + lhs.val;
	int R = return_char_hash(rhs.symbol) + rhs.val;
	bool b = (L < R) ? true : false;
	return(b);
}

Deck_operations_class::~Deck_operations_class()
{
}

int Deck_operations_class::random_num_gen(int min, int max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	int rand_num = distr(eng);
	return rand_num;
}

Deck_operations_class::Deck_operations_class()
{
}

Deck_operations_class::Deck_operations_class(vector<Card_Class::card> deck_param)
{
	deck = deck_param;
}

vector<Card_Class::card> Deck_operations_class::shuffle()
{
	for (int i = 0; i<52; i++)
	{
		int rand_pos = random_num_gen();
		Card_Class::card temp = deck[i];
		deck[i] = deck[rand_pos];
		deck[rand_pos] = temp;
	}
	return deck;
}

vector<Card_Class::card> Deck_operations_class::Sort()
{
	sort(deck.begin(), deck.end(), sort_by_symbols);
	return deck;
}

void Deck_operations_class::print_deck()
{
	Sort();
	for (int i = 0; i<deck.size(); i++)
	{
		string symbolStr="";
		string card = "";

		if (deck[i].val == 14)
			card = "Ace";
		else if (deck[i].val == 13)
			card = "King";
		else if (deck[i].val == 12)
			card = "Queen";
		else if (deck[i].val == 11)
			card = "Joker";
		else
			card = to_string(deck[i].val);

		if (deck[i].symbol == 'C')
			symbolStr = "Clover";
		if (deck[i].symbol == 'D')
			symbolStr = "Diamond";
		if (deck[i].symbol == 'H')
			symbolStr = "Hearts";
		if (deck[i].symbol == 'S')
			symbolStr = "Spade";

		cout<<"\n"<<card<<"-"<<symbolStr;
	}
	cout << "\n";
}