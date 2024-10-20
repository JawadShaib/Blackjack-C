#ifndef MENU_H
#define MENU_H

#include "card.h"
#include "game_status.h"
#include <windows.h>

#define DEALER_STOP_VALUE 17
#define MINIMUM_CASH_VALUE 10
#define MAX_HAND_VALUE 21
/**
 * @brief Display blackjack game intro screen
 *
 */
void display_game_intro(void);

/**
 * @brief Display blackjack game outro screen
 *
 */
void display_game_outro(void);

/**
 * @brief Display player's cash & pot values
 *
 * @param cash Player cash value
 * @param pot cash are added to pot and adjusted according to game status
 */
void display_cash_pot_values(int *cash, int *pot);

/**
 * @brief Initialize blackjack game
 *
 * @param deck A inked list of card nodes represents deck of cards to draw
 * @param dealer_hand  A linked list of card nodes represents dealer's hand
 * @param player_hand A linked list of card nodes represents player's hand
 * @param cash Player cash value
 * @param pot cash are added to pot and adjusted according to game status
 */
void game_initialization(CardList *deck, CardList *dealer_hand, CardList *player_hand, int *cash, int *pot);

/**
 * @brief Player place a bet in multiples of 10
 *
 * @param cash Player cash value
 * @param pot cash are added to pot and adjusted according to game status
 * @return game_status Returns PROCEED_GAME on success bet  otherwise EXIT_GAME
 */
game_status betting_phase(int *cash, int *pot);

/**
 * @brief cash inside the pot are adjusted according to game status (added to cash when player wins else set to zero)
 *
 * @param cash Player's cash value
 * @param pot Cash are added/removed to/from pot and adjusted according to game status
 * @param player_game_status weather to proceed game or exit game according to cash amount left
 */
void adjust_bet(int *cash, int *pot, game_status player_game_status);

/**
 * @brief Player & dealer draw two cards from deck of cards
 *
 * @param deck  A inked list of card nodes represents deck of cards to draw
 * @param dealer_hand A linked list of card nodes represents dealer's hand
 * @param player_hand A linked list of card nodes represents player's hand
 */
void initial_deal(CardList *deck, CardList *dealer_hand, CardList *player_hand);

/**
 * @brief Player's hand is checked to see if its value is (21) Blackjack
 *
 * @param player_hand A linked list of card nodes represents player's hand
 * @param dealer_hand A linked list of card nodes represents dealer's hand
 * @param cash Player's cash value
 * @param pot Cash are added/removed to/from pot and adjusted according to game status
 * @return game_status
 */
game_status blackjack_check(CardList *player_hand, CardList *dealer_hand, int *cash, int *pot);

/**
 * @brief Player Draw cards from deck , each hit card value are caculated
 *
 * @param deck A inked list of card nodes represents deck of cards to draw
 * @param player_hand A linked list of card nodes represents player's hand
 * @param pot Cash are added/removed to/from pot and adjusted according to game status
 * @param cash Player's cash value
 * @return game_status
 */
game_status player_hit(CardList *deck, CardList *player_hand, int *cash, int *pot);

/**
 * @brief The player is asked whether they want to "Hit" (draw another card) or "Stand" (keep their current hand)
 *
 * @param deck A linked list of card nodes represents deck of cards to draw
 * @param player_hand A linked list of card nodes represents player's hand
 * @param cash  Player's cash value
 * @param pot Cash are added/removed to/from pot and adjusted according to game status
 * @return game_status
 */
game_status hit_or_stand_phase(CardList *deck, CardList *player_hand, int *cash, int *pot);

/**
 * @brief Dealer reveals their hidden card and draws additional cards until their hand value reaches 17 or more , card value are compared to player's hand
 *
 * @param deck A linked list of card nodes represents deck of cards to draw
 * @param dealer_hand A linked list of card nodes represents dealer's hand
 * @param player_hand A linked list of card nodes represents player's hand
 * @param cash Player's cash value
 * @param pot Cash are added/removed to/from pot and adjusted according to game status
 */
void dealer_draw(CardList *deck, CardList *dealer_hand, CardList *player_hand, int *cash, int *pot);

/**
 * @brief After a game round, all cards from the player’s and dealer’s hands are returned to the deck.
 *
 * @param deck A linked list of card nodes represents deck of cards to draw
 * @param dealer_hand A linked list of card nodes represents dealer's hand
 * @param player_hand A linked list of card nodes represents player's hand
 * @param cash Player's cash value
 * @param pot Cash are added/removed to/from pot and adjusted according to game status
 * @return game_status
 */
game_status reset_cards(CardList *deck, CardList *dealer_hand, CardList *player_hand, int *cash, int *pot);

/**
 * @brief All blackjack game phases are executed according to game status for each player & dealer
 *
 * @param deck A linked list of card nodes represents deck of cards to draw
 * @param player_hand A linked list of card nodes represents dealer's hand
 * @param dealer_hand A linked list of card nodes represents dealer's hand
 * @param cash Player's cash value
 * @param pot Current pot value
 * @return game_status
 */
game_status play_game(CardList *deck, CardList *player_hand, CardList *dealer_hand, int *cash, int *pot);

#endif