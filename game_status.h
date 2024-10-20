#ifndef GAME_STATUS
#define GAME_STATUS

/**
 * @brief Game status code used for game operation
 *
 */
typedef enum
{
    DRAW,
    PLAYER_WINS,
    PLAYER_STAND,
    PLAYER_BUST,
    DEALER_WINS,
    DEALER_BUST,
    TIE,
    BLACKJACK,
    EXIT_GAME,
    PROCEED_GAME,

} game_status;
#endif