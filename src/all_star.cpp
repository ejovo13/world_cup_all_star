/**========================================================================
 * ?                          all_star.cpp
 * @brief   : Main driver program of our game
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-13
 *========================================================================**/
#include "all_star.hpp"

using namespace all_star::game_mgr;

int main() {

    GameManager game;
    game.start();

    return EXIT_SUCCESS;

}