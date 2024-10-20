
#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

/**
 * @brief A structure to represent a card in the linked list.
 * @param data Stores rank and suit in bits [7:4] for rank and [3:0] for suit
 * @param next Pointer to the next card in the the linked list
 */
typedef struct Card
{
    uint8_t data;
    struct Card *next;
} Card;

/**
 * @brief Card linked list  for each player/dealer/deck
 * @param head Pointer to the first card in the linked list
 * @param len  Card amount
 */
typedef struct CardList
{
    Card *head;
    size_t len;
} CardList;

/**
 * @brief Creates a new card node
 *
 * @param rank Card Value (1-13)
 * @param suit card suit (Hearts, Clubs, Diamonds, Spades)
 * @return Card* Pointer to a card node
 */

Card *card_new(int rank, int suit);
/**
 * @brief Initialize a linked list of cards
 *
 * @param cardlist Pointer to a head of the card list
 */
void init_cardlist(CardList *cardlist);

/**
 * @brief Fills a card list with card nodes
 *
 * @param deck Linked list of card nodes
 */
void fill_deck(CardList *deck);

/**
 * @brief Adds a new card node to the head of card list
 *
 * @param cardlist Pointer to a head of the card list
 * @param card Card node
 */
void card_push(CardList *cardlist, Card *card);

/**
 * @brief Detach a card node at the specified index from the card list.
 *
 * @param cardlist Pointer to a head of the card list
 * @param index The index of the card node to be removed.
 * @return  detached card node
 */
Card *remove_card_at_index(CardList *cardlist, size_t index);

/**
 * @brief Remove a card node from a deck's card list and to player/dealer card list
 *
 * @param deck card list of card nodes
 * @param cardlist  card list of card nodes
 */
void draw_card(CardList *deck, CardList *cardlist);

/**
 * @brief Get the rank of card [1-13]
 *
 * @param card card node
 * @return int  card value
 */
int get_rank_value(Card *card);

/**
 * @brief Get the the card name
 *
 * @param rank a decimal number represnting card value [1-13]
 * @return const char*
 */
const char *get_rank_name(int rank);

/**
 * @brief Get rank of the card vode
 *
 * @param Card Card node
 * @return const char*
 */
const char *get_rank(Card *Card);

/**
 * @brief Get the suit index value {1:Hearts, 2:Clubs, 4:Diamonds, 8:Spades}
 *
 * @param card card node
 * @return int
 */
int get_suit_value(Card *card);

/**
 * @brief Get the suit name object according to suit value index {1:Hearts, 2:Clubs, 4:Diamonds, 8:Spades}
 *
 * @param suit
 * @return const char*
 */
const char *get_suit_name(int suit);

/**
 * @brief Get suit name of the card node {1:Hearts, 2:Clubs, 4:Diamonds, 8:Spades}
 *
 * @param Card Card node
 * @return const char*
 */
const char *get_suit(Card *Card);

/**
 * @brief Display the intial card list of each player/dealer
 *
 * @param cardlist A linked list of card nodes
 * @param is_dealer Dealer displays only the first card in the card list the rest are hidden
 */
void show_initial_card_cardlist(CardList *cardlist, bool is_dealer);

/**
 * @brief Display card list
 *
 * @param cardlist A linked list of card nodes
 */
void show_cardlist(CardList *cardlist);

/**
 * @brief Calculate Hand value according according to rank value
 *
 * @param hand A linked list of card nodes
 * @return int hand value
 */
int calculate_hand_value(CardList *hand);

/**
 * @brief Pop card node from dealer/player card list and push to deck card list
 *
 * @param deck A linked list of card nodes
 * @param hand A linked list of card nodes
 */
void transfer_cards_to_deck(CardList *deck, CardList *hand);

/**
 * @brief Clears the entire card list, freeing all card nodes.
 *
 * @param cardlist A linked list of card nodes
 */
void clear_cardlist(CardList *cardlist);

#endif
