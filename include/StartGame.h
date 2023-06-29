#pragma once
#include"Player.h"

class StartGame
{
private:
	int NumofPlayers;
	int Player_iterator_to_begin_game;
	int Cards_counter;

	Player_Class *Players;

	vector<Card_Class::card> temporary_deck;
	vector<Player_Class> Player_Queue;


public:

	Card_Class *cardPack;

	StartGame(int n=2);

	int Serve_cards();
	
	int Validate_round( char symbol );

	int remove_player_from_Queue(Card_Class::card tempCard);

	void Game_main_Loop();

	~StartGame();
};