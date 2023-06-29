#include "Player.h"
#include "Deck_operations.h"

static int ID_countr = 0;

Player_Class::Player_Class()
{
	playerID=ID_countr++;
	player_deck.empty();
}

Player_Class::Player_Class(vector<Card_Class::card> partof_deck)
{
	playerID =ID_countr++;
	player_deck = Deck_operations_class(partof_deck).Sort();
}

int Player_Class::get_playerID()
{
	return playerID;
}

pair<int, int> Player_Class::fetch_minmax_posistion_from_playerdeck(char symbol)
{
	int min, max;
	bool minflag = false;
	bool maxflag = false;
	for (int i=0;i<player_deck.size();i++)
	{
		if (!minflag && player_deck[i].symbol == symbol)
		{
			min = i;
			minflag = true;
		}
		else if (player_deck[i].symbol == symbol)
		{
			max = i;
			maxflag = true;
		}
	}

	if (!maxflag) //only one element of the symbol in deck , so max not set in above loop
	{
		max = min;
	}

return( pair<int,int>(min,max) );
}

bool Player_Class::push_a_card_in_deck(Card_Class::card c)
{
	c.player_id = playerID;
	player_deck.push_back(c);
return true;
}

bool Player_Class::push_a_part_of_deck(vector<Card_Class::card> part_of_deck)
{
	for (int i = 0; i < part_of_deck.size(); i++)
	{
		part_of_deck[i].player_id = playerID;
	}

	player_deck.insert( player_deck.end(), part_of_deck.begin(), part_of_deck.end() );
	player_deck = Deck_operations_class(player_deck).Sort();

return true;
}

bool Player_Class::check_card_present_in_player_deck(char symbol)
{
	player_deck = Deck_operations_class(player_deck).Sort();

	for (int i=0;i<player_deck.size();i++)
	{
		if (player_deck[i].symbol == symbol)
		{
			return true;
		}
	}
	return false;
}

Card_Class::card Player_Class::get_a_card_from_deck(char symbol)
{
	Card_Class::card card_val;
	int position = -1,min,max;

	if (player_deck.size() != 0)
	{

		bool symbol_card_present = check_card_present_in_player_deck(symbol);

		if (symbol_card_present)
		{
			cout << "enter a [" << symbol << " ]card from your deck PlayerNumber=[ "<<playerID+1<<" ]\n";

			/* CARD-INPUT LOGIC
				make this inside a timer of 30sec
				after timer if no card is selected - select_card_automatically_from_deck()-this should be poor selection logic
			*/ //TODO

			pair<int, int> min_max_pair = fetch_minmax_posistion_from_playerdeck(symbol);

			min = min_max_pair.first;
			max = min_max_pair.second;
			
			vector<Card_Class::card> tempvector = vector<Card_Class::card>(player_deck.begin()+min,player_deck.begin()+max+1);
			Deck_operations_class(tempvector).print_deck();

			if (min != max)
				cout << "enter a position between the range of cards position [" << min << " , " << max << " ]";
			else
				cout << "you have only one card in respective symbol in the following position [ " << min << " ]";
			do
			{
				cout << "\nenter the position = ";
				cin >> position;
			} while (position<min || position>max);

			card_val = player_deck[position];
			player_deck.erase(player_deck.begin() + position);
		}
		else
		{
			min = 0; max = player_deck.size() - 1;
			cout << "\n";

			vector<Card_Class::card> tempvector = vector<Card_Class::card>(player_deck.begin() + min, player_deck.begin() + max+1);
			Deck_operations_class(tempvector).print_deck();

			cout << "enter any card in range [ 0 , " << max << " ] to mock the previous playerPlayerNumber=[ " << playerID +1<< " ]";

			/* CARD-INPUT LOGIC
			make this inside a timer of 30sec
			after timer if no card is selected - select_card_automatically_from_deck()-this should be poor selection logic
			*/ //TODO

			do
			{
				cout << "\nenter the position = ";
				cin >> position;
			} while (position<min || position>max);

			card_val = player_deck[position];
			player_deck.erase(player_deck.begin() + position);
		}
	}
	else
	{
		//player finished the game return an empty card , so that he can be removed from queue

		card_val.player_id = playerID;
		card_val.val = -1;
		card_val.symbol = '$';
	}
return card_val;
}

void Player_Class::print_player_deck()
{
	Deck_operations_class(player_deck).print_deck();
}

int Player_Class::get_players_deck_size()
{
	return player_deck.size();
}

Player_Class::~Player_Class()
{

}
