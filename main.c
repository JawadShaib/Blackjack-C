
#include <stdlib.h>
#include "card.h"
#include "menu.h"

int main()
{

    CardList deck, dealer_hand, player_hand;
    int cash, pot;
    int game = PROCEED_GAME;
    display_game_intro();
    game_initialization(&deck, &dealer_hand, &player_hand, &cash, &pot);
    while (game != EXIT_GAME)
        game = play_game(&deck, &dealer_hand, &player_hand, &cash, &pot);
    clear_cardlist(&deck);
    display_game_outro();
    system("pause");
    return 0;
}
