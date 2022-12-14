#include "all_star.hpp"

using namespace all_star::mini_games;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Offense minigame");
    Game minigame;
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        if (minigame.checklose())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    minigame.update_balls(event);
                }
            }
            minigame.update_game();
            minigame.displaythegame(window);
        }
        else
        {
            window.close();
        }
    }
    return 0;
}