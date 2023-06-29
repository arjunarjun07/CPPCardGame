#pragma once
#include "Card.h"

class Player_Class
{
private:
	int playerID;
	vector<Card_Class::card> player_deck;

public:
	Player_Class();
	Player_Class(vector<Card_Class::card> partof_deck);

	int get_playerID();
	bool push_a_card_in_deck(Card_Class::card c);
	bool push_a_part_of_deck(vector<Card_Class::card> part_of_deck);
	bool check_card_present_in_player_deck(char symbol);
	Card_Class::card get_a_card_from_deck( char symbol );
	void print_player_deck();
	int get_players_deck_size();
	pair<int,int> fetch_minmax_posistion_from_playerdeck(char symbol);
	
	~Player_Class();

};
