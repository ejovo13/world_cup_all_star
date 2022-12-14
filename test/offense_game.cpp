#include "all_star.hpp"

using namespace world_cup::mini_games;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Offense minigame");
    window.setFramerateLimit(60);
    window.clear();
    sf::CircleShape _ball;
    _ball.setRadius(50);
    _ball.setPosition(200,400);
    _ball.setFillColor(sf::Color::Red);
    sf::Texture texture;
    texture.loadFromFile("ball.png");
    _ball.setTexture(&texture);
    window.draw(_ball);
    window.display();
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
            minigame.display(window);
        }
        else
        {
            window.close();
        }
    }
    return 0;
}