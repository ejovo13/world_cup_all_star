#include "all_star.hpp"
using namespace all_star::mini_games;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Offense minigame"); // open game window
    window.setFramerateLimit(60);                                                        // set limit to have same experience between different PCs
    sf::Texture ball_texture = create_ball_texture("ball.png");                              // for ball texture
    sf::Texture background_texture = create_background_texture("background.png");            // for background texture
    sf::Sprite game_background = load_background(background_texture);                        // load background texture in an object to display later
    //window.setView(sf::View(sf::FloatRect(0,0,background_texture.getSize().x,background_texture.getSize().y)));   
    std::string font_file = "arial.ttf";
    sf::Font font;
    font.loadFromFile(font_file);
    Game minigame(ball_texture, font);                                                             // game initialization
    bool playing = true;
    while (window.isOpen()) // game loop
    {
        if (playing == true)
        {
            if (minigame.checklose())
            {
                sf::Event event;
                while (window.pollEvent(event)) // check if user does something
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
                minigame.display(window, game_background);
            }
            else
            {
                playing = false;
            }
        }
        else{
            sf::Event event;
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            window.draw(game_background);
            minigame.game_over(window, game_background, mousePosition);
                while (window.pollEvent(event)) // check if user does something
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        playing = minigame.game_over_click(window, event, game_background);
                        if(playing){new (&minigame) Game(ball_texture, font);} //reset game
                    }
                }
        }
    }
    return 0;
}
