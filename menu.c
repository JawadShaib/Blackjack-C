
#include "menu.h"

void display_game_intro(void)
{
    printf("\n-----------------------------------------------------------\n");
    printf("\n------------- Blackjack Game Tournament -------------------\n");
    printf("\n-----------------------------------------------------------\n");
}

void display_game_outro(void)
{
    printf("\n-----------------------------------------------------------\n");
    printf("\n------------- Blackjack Game Tournament End -------------------\n");
    printf("\n-----------------------------------------------------------\n");
}

void display_cash_pot_values(int *cash, int *pot)
{
    printf("\nYour current cash--> %d\n", *cash);
    printf("\nYour current Pot--> %d\n", *pot);
}

void game_initialization(CardList *deck, CardList *dealer_hand, CardList *player_hand, int *cash, int *pot)
{
    srand(time(NULL));
    init_cardlist(deck);
    init_cardlist(dealer_hand);
    init_cardlist(player_hand);
    fill_deck(deck);
    *cash = 1000;
    *pot = 0;
}

game_status betting_phase(int *cash, int *pot)
{

    if ((*pot == 0) && (*cash < MINIMUM_CASH_VALUE))
    {
        printf("\n No More Bets \n");
        display_cash_pot_values(cash, pot);
        return EXIT_GAME;
    }
    else if (*pot > 0 )
    {
        // Tie game proceed to another game without betting 
        display_cash_pot_values(cash, pot);
        return PROCEED_GAME;
    }
    

    int bet_amount;
    char buffer[50];

    while (true)
    {
        printf("\nPlease Enter bet amount: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &bet_amount) != 1)
        {
            printf("\nInvalid input, Please enter a integer\n");
            continue;
        }
        if (bet_amount <= 0)
        {
            printf("\nInvalid input, Please enter a positive bet value\n");
        }

        else if (bet_amount > *cash)
        {
            printf("\nyou don't have enough cash to place this bet\n");
        }

        else if (bet_amount % 10 != 0)
        {
            printf("\nBet amount should be multiples of 10!\n");
        }

        else
        {
            *cash = *cash - bet_amount;
            *pot = bet_amount;
            display_cash_pot_values(cash, pot);
            return PROCEED_GAME;
        }
    }
}
void adjust_bet(int *cash, int *pot, game_status player_game_status)
{

    switch (player_game_status)
    {
    case BLACKJACK:
        *cash += (*pot) + (int)((1.5) * (*pot));
        *pot = 0;
        break;

    case DEALER_BUST:
    case PLAYER_WINS:
        *cash += 2 * (*pot);
        *pot = 0;
        break;
    case DEALER_WINS:
    case PLAYER_BUST:
        *pot = 0;

    default:
        break;
    }

    display_cash_pot_values(cash, pot);
}

void initial_deal(CardList *deck, CardList *dealer_hand, CardList *player_hand)
{
    while ((dealer_hand->len != 2 && player_hand->len != 2))
    {
        // draw two cards for each player and dealer
        draw_card(deck, dealer_hand);
        draw_card(deck, player_hand);
    }
    // print player first two cards
    show_initial_card_cardlist(dealer_hand, true);
    // print dealer first card the second card is unrevealed
    show_initial_card_cardlist(player_hand, false);
}

game_status blackjack_check(CardList *player_hand, CardList *dealer_hand, int *cash, int *pot)
{
    int player_hand_value = calculate_hand_value(player_hand);
    int dealer_hand_value = calculate_hand_value(dealer_hand);
    if (player_hand_value == MAX_HAND_VALUE)
    {
        // check if dealer has also black jack
        if (dealer_hand_value == MAX_HAND_VALUE)
        {

            printf("\n Dealer also have BlackJack its a TIE game \n");
            show_cardlist(dealer_hand);
            return TIE;
        }

        else
        {
            printf("\n !! BlackJack !! \n");
            show_cardlist(player_hand);
            adjust_bet(cash, pot, BLACKJACK);
            return BLACKJACK;
        }
    }
    // check if dealer have blackjack
    else if (dealer_hand_value == MAX_HAND_VALUE)
    {
        printf("\n Dealer have BlackJack you lose \n");
        show_cardlist(dealer_hand);
        adjust_bet(cash, pot, DEALER_WINS);
        return DEALER_WINS;
    }

    // blackjack not found for player & delaer proceeding to game
    return PROCEED_GAME;
}

game_status player_hit(CardList *deck, CardList *player_hand, int *cash, int *pot)
{
    draw_card(deck, player_hand);
    show_cardlist(player_hand);
    int player_hand_value = calculate_hand_value(player_hand);

    if (player_hand_value > MAX_HAND_VALUE)
    {
        printf("\nBUST --> Player Hand Value %d\n ", player_hand_value);
        adjust_bet(cash, pot, PLAYER_BUST);
        return PLAYER_BUST;
    }
    return PROCEED_GAME;
}
game_status hit_or_stand_phase(CardList *deck, CardList *player_hand, int *cash, int *pot)
{

    printf("\n---Player Hit OR Stand---\n");
    int stage_status = PROCEED_GAME;
    char input[10];
    while (stage_status == PROCEED_GAME)
    {
        printf("\n1.Hit\n");
        printf("\n2.Stand\n");
        printf("-->(h/s)  ");
        // scanf(" %c", &option);
        fgets(input, sizeof(input), stdin);
        if (input[strlen(input) - 1] == '\n')
        {
            // remove newline if it exists.
            input[strlen(input) - 1] = '\0';
        }
        if (strlen(input) != 1)
        {
            printf("\nInvalid input! Please enter exactly one character ('h' or 's').\n");
            continue;
        }
        switch (input[0])
        {
        case 'h':
            /* Hit */
            stage_status = player_hit(deck, player_hand, cash, pot);

            break;

        case 's':
            /* Stand */

            stage_status = PLAYER_STAND;
            break;

        default:
            printf("\nWrong Option! Please enter exactly one character ('h' or 's') \n");
            break;
        }
    }

    return stage_status;
}

void dealer_draw(CardList *deck, CardList *dealer_hand, CardList *player_hand, int *cash, int *pot)
{
    printf("\n---Dealer Draw---\n");
    show_cardlist(dealer_hand);
    int dealer_hand_value = calculate_hand_value(dealer_hand);
    int player_hand_value = calculate_hand_value(player_hand);
    while (dealer_hand_value < DEALER_STOP_VALUE)
    {
        draw_card(deck, dealer_hand);
        Sleep(2500);
        show_cardlist(dealer_hand);
        dealer_hand_value = calculate_hand_value(dealer_hand);
    }
    // dealer hand value check when hand value reach 17 or more
    if (dealer_hand_value > MAX_HAND_VALUE)
    {
        printf("\nDealer Bust\n");
        adjust_bet(cash, pot, DEALER_BUST);
    }

    else if (dealer_hand_value > player_hand_value)
    {
        printf("\nDealer Wins\n");
        adjust_bet(cash, pot, DEALER_WINS);
    }
    else if (dealer_hand_value < player_hand_value)
    {
        printf("\nPlayer Wins\n");
        adjust_bet(cash, pot, PLAYER_WINS);
    }
    else
    {
        printf("\nIt's a TIE!\n");
    }
}

game_status reset_cards(CardList *deck, CardList *dealer_hand, CardList *player_hand, int *cash, int *pot)
{
    char input[10];
    transfer_cards_to_deck(deck, player_hand);
    transfer_cards_to_deck(deck, dealer_hand);
    if ((*pot == 0) && (*cash < MINIMUM_CASH_VALUE))
    {
        printf("\nNo More Betts\n");
        return EXIT_GAME;
    }
    while (true)
    {
        printf("\nWhould you like to play another round?(y/n)\n");
        fgets(input, sizeof(input), stdin);
        if (input[strlen(input) - 1] == '\n')
        {
            // remove newline if it exists.
            input[strlen(input) - 1] = '\0';
        }
        if (strlen(input) != 1)
        {
            printf("\nInvalid input! Please enter exactly one character ('y' or 'n').\n");
            continue;
        }

        switch (input[0])
        {
        case 'y':
            return PROCEED_GAME;

        case 'n':
            return EXIT_GAME;

        default:
            printf("\nInvalid input! Please enter ('y' or 'n').\n");
            break;
        }
    }
}

game_status play_game(CardList *deck, CardList *player_hand, CardList *dealer_hand, int *cash, int *pot)
{
    int status;
    status = betting_phase(cash, pot);
    if (status != EXIT_GAME)
    {
        initial_deal(deck, dealer_hand, player_hand);
        status = blackjack_check(player_hand, dealer_hand, cash, pot);
        if (status == PROCEED_GAME)
        {
            status = hit_or_stand_phase(deck, player_hand, cash, pot);
            if (status == PLAYER_STAND)
            {
                dealer_draw(deck, dealer_hand, player_hand, cash, pot);
            }
        }
        status = reset_cards(deck, dealer_hand, player_hand, cash, pot);
    }
    return status;
}