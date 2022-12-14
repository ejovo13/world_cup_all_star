#include "all_star.hpp"

using namespace world_cup::mini_games;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Offense minigame"); //open game window
    window.setFramerateLimit(60); //set limit to have same experience between different pcs
    sf::Texture ball_texture;   //for ball graphics
    ball_texture.loadFromFile("ball.png");

    Game minigame(ball_texture);//game initialization

    while (window.isOpen()) //game loop
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
            minigame.display(window);
        }
        else
        {
            window.close();
        }
    }
    return 0;
}