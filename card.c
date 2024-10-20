
#include "card.h"

void init_cardlist(CardList *cardlist)
{
    cardlist->head = NULL;
    cardlist->len = 0;
}

Card *card_new(int rank, int suit)
{
    Card *new_card = (Card *)malloc(sizeof(Card));
    new_card->data = (rank << 4) | suit; // Combine rank and suit into data
    new_card->next = NULL;
    return new_card;
}

void card_push(CardList *cardlist, Card *card)
{
    card->next = cardlist->head;
    cardlist->head = card;
    cardlist->len++;
}

void fill_deck(CardList *deck)
{
    for (int rank = 1; rank <= 13; rank++)
    { // 1 for Ace, 2-10, 11 for Jack, 12 for Queen, 13 for King
        for (int suit = 1; suit <= 8; suit <<= 1)
        { // 1: Hearts, 2: Clubs, 4: Diamonds, 8: Spades
            card_push(deck, card_new(rank, suit));
        }
    }
}

void clear_cardlist(CardList *cardlist)
{
    Card *current = cardlist->head;
    while (current != NULL)
    {
        Card *next = current->next;
        free(current);
        current = next;
    }
    cardlist->head = NULL;
    cardlist->len = 0;
}

int get_rank_value(Card *card)
{
    return (card->data >> 4) & 0xF;
}

const char *get_rank_name(int rank)
{
    static const char *ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    return ranks[rank - 1];
}

const char *get_rank(Card *card)
{
    int rank = get_rank_value(card);
    return get_rank_name(rank);
}

int get_suit_value(Card *card)
{
    return (card->data) & 0Xf;
}

const char *get_suit_name(int suit)
{
    switch (suit)
    {
    case 1:
        return "\u2665"; // Unicode for Hearts \u2665 (♥)
    case 2:
        return "\u2663"; // Unicode for Clubs (♣)
    case 4:
        return "\u2666"; // Unicode for Diamonds (♦)
    case 8:
        return "\u2660"; // Unicode for Spades (♠)
    default:
        return "Unknown";
    }
}

const char *get_suit(Card *card)
{
    int rank = get_suit_value(card);
    return get_suit_name(rank);
}

void show_initial_card_cardlist(CardList *cardlist, bool is_dealer)

{
    if (cardlist == NULL || cardlist->head == NULL)
    {
        printf("\n Cannot display an empty card list \n");
        return;
    }
    Card *current = cardlist->head;
    if (is_dealer)
    {
        printf("\nDealer: %s Of %s --> ??????\n", get_rank(current), get_suit(current));
    }
    else
    {
        printf("\nPlayer: %s of %s --> %s of %s\n", get_rank(current), get_suit(current), get_rank(current->next), get_suit(current->next));
    }
}

void show_cardlist(CardList *cardlist)
{
    Card *current = cardlist->head;
    while (current != NULL)
    {

        const char *rank = get_rank(current);
        const char *suit = get_suit(current);
        printf("%s Of %s", rank, suit);
        current = current->next;
        if (current != NULL)
        {
            printf(" --> ");
        }
    }

    printf("\n");
}

Card *remove_card_at_index(CardList *cardlist, size_t index)
{
    if (cardlist == NULL || cardlist->head == NULL)
    {
        printf("Cannot remove a card from an empty list");
        return NULL;
    }
    Card *temp = cardlist->head;
    if (index == 0)
    {
        /* removing the first cardnode */
        cardlist->head = temp->next;
        /*detachd the cardnode from the cardlist*/
        temp->next = NULL;
        cardlist->len--;
        return temp;
    }

    for (size_t i = 0; temp != NULL && i < index - 1; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
    {
        printf("Index is out of bounds.\n");
        return NULL;
    }

    Card *detached = temp->next;
    temp->next = detached->next;
    detached->next = NULL;
    cardlist->len--;
    return detached;
}

void draw_card(CardList *deck, CardList *cardlist)
{
    int index = rand() % deck->len;
    Card *removed_card = remove_card_at_index(deck, index);
    if (removed_card != NULL)
    {
        card_push(cardlist, removed_card);
    }
    else
    {
        printf("cannot draw card ! ");
    }
}

int calculate_hand_value(CardList *hand)
{
    int sum = 0, rank, ace_counter = 0;
    if (hand == NULL || hand->head == NULL)
    {
        return sum;
    }

    Card *current = hand->head;
    while (current != NULL)
    {
        rank = get_rank_value(current);
        if (rank == 1)
        {
            /* ACE card */
            ace_counter++;
            rank = 1;
        }
        else if (rank >= 11 && rank <= 13)
        {
            /* JACK || QUEEN || KING card */
            rank = 10;
        }
        sum += rank;
        current = current->next;
    }

    while (ace_counter > 0 && sum <= 11)
    {
        sum += 10;
        ace_counter--;
    }

    return sum;
}

void transfer_cards_to_deck(CardList *deck, CardList *hand)
{

    while (hand->head != NULL)
    {

        Card *current = hand->head;
        hand->head = current->next;
        current->next = NULL;
        card_push(deck, current);
    }
    hand->len = 0;
}
