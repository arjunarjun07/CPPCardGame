#include "StartGame.h"
#include "Deck_operations.h"
#include <stdlib.h>

StartGame::StartGame(int n)
{
	NumofPlayers = n;
	Cards_counter = 52;

	Players = new Player_Class[NumofPlayers];
	
	for (int i=0;i<n;i++)
	{
		Player_Queue.push_back(Players[i]);
	}

	cardPack = new Card_Class();
}

int StartGame::Serve_cards()
{
	cardPack->card_deck = Deck_operations_class(cardPack->card_deck).shuffle();

	int iterator = 1;
	for (int i = 0; i < 52; i++)
	{
		int modVal = (iterator % NumofPlayers);
		int pid = ((modVal) ? modVal : NumofPlayers) - 1;
		
		Card_Class::card TempCard = cardPack->card_deck[i];
		if ( TempCard.symbol == 'S' && TempCard.val == 14) 
		{
			Player_iterator_to_begin_game = pid;
		}
		
		Players[pid].push_a_card_in_deck( TempCard );
		++iterator;
	}

return Player_iterator_to_begin_game;
}

int StartGame::Validate_round( char symbol )
{
	bool is_set_contains_diff_symbol = false;

	temporary_deck = Deck_operations_class(temporary_deck).Sort(); //Sort makes the deck sorted with same symbols contigious & diff symbol at last position

	is_set_contains_diff_symbol = (temporary_deck.back().symbol != symbol) ? true : false;

	if (is_set_contains_diff_symbol)
	{
		Card_Class::card diff_symbol_card = temporary_deck.back(); //last element
		Card_Class::card greater_value_put_card_member = temporary_deck[ temporary_deck.size()-2 ]; //2nd last element

		Players[ greater_value_put_card_member.player_id ].push_a_part_of_deck(temporary_deck);
		Player_iterator_to_begin_game = diff_symbol_card.player_id;
		cout << "Round cleared by mocking,Player[ " << Player_iterator_to_begin_game + 1 << " ] should continue";
	}
	else
	{
		Card_Class::card temp = temporary_deck.back();
		Player_iterator_to_begin_game = temp.player_id;
		Cards_counter -= temporary_deck.size();
		cout << "Round cleared,Player[ " << Player_iterator_to_begin_game + 1 << " ] should continue";
	}

	return Player_iterator_to_begin_game;
}

int StartGame::remove_player_from_Queue(Card_Class::card tempCard)
{
	int next_player_to_proceed=0;
	for (int i=0;i<Player_Queue.size();i++)
	{
		if (tempCard.player_id == Player_Queue[i].get_playerID())
		{
			Player_Queue.erase(Player_Queue.begin()+i);
			next_player_to_proceed = i + 1;
			break;
		}
	}

return next_player_to_proceed;
}

void StartGame::Game_main_Loop()
{
	char symbol_to_proceed = NULL;
	bool round_begins_check = false;
	int player_iterator = Serve_cards();

	cout <<"Player[ "<<player_iterator+1<<" ] should start because he has A-Spade ";

	for (int i = player_iterator; i < Player_Queue.size(); )
	{
		if (Cards_counter == 1 || Players[i].get_players_deck_size() == 0 )
		{
			break;
		}
		else
		{
			if ( round_begins_check == false )
			{
				round_begins_check = true;
				do
				{
					Sleep(5000);
					system("CLS");

					Players[i].print_player_deck();

					cout <<"\nPlayer[ "<<i+1<<" ] Please enter a symbol from the list to proceed [C-Clover,D-Diamond,H-Heart,S-Spade]=";
					fflush(stdin);
					cin >> symbol_to_proceed;
				} while ( ! Players[i].check_card_present_in_player_deck(symbol_to_proceed) );
			}

			Card_Class::card card_of_a_round = Players[i].get_a_card_from_deck(symbol_to_proceed);

			if (card_of_a_round.symbol == '$' && card_of_a_round.val == -1)
			{
				player_iterator = remove_player_from_Queue(card_of_a_round);
				cout << "Player doesn't have any cards on the symbol [ " << symbol_to_proceed <<" ], Try other";
				continue;
			}
			else
			{
				system("CLS");
				cout << "\n---------------In Round Stack--------------\n";
				temporary_deck.push_back(card_of_a_round);
				Deck_operations_class(temporary_deck).print_deck();
				cout << "\n---------------------------------------------\n";
			}

			if (temporary_deck.size() == Player_Queue.size())
			{
				i = Validate_round(symbol_to_proceed);
				symbol_to_proceed = NULL;
				round_begins_check = false;
				temporary_deck.clear();
			}
			else
			{
				//problem-code
				i = ((++i) % NumofPlayers);
			}
		}
	}

	//last player
	int lost_pid = Player_Queue[0].get_playerID();

	cout << "Game Finished- Player " << lost_pid+1 << " is the ASS";
}

StartGame::~StartGame()
{
	delete[] Players;
	delete cardPack;
}
