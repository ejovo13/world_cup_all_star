#include "all_star.hpp"
using namespace world_cup::mini_games;

sf::Texture create_background_texture(std::string file);
sf::Texture create_ball_texture(std::string file);
sf::Sprite load_background(sf::Texture &background);

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Offense minigame"); // open game window
    window.setFramerateLimit(60);                                                            // set limit to have same experience between different PCs
    sf::Texture ball_texture = create_ball_texture("ball.png");                              // for ball texture
    sf::Texture background_texture = create_background_texture("background.jpg");            // for background texture
    sf::Sprite game_background = load_background(background_texture);                        // load background texture in an object to display later
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
            minigame.game_over(window);
            sf::Event event;
                while (window.pollEvent(event)) // check if user does something
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {
                        playing = minigame.game_over_click(window, event);
                        if(playing){new (&minigame) Game(ball_texture, font);} //reset game
                    }
                }
        }
    }
    return 0;
}

sf::Texture create_background_texture(std::string file)
{
    sf::Texture background_texture;
    background_texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    background_texture.loadFromFile(file);
    return background_texture;
}

sf::Texture create_ball_texture(std::string file)
{
    sf::Texture ball_texture; // for ball graphics
    ball_texture.loadFromFile(file);
    return ball_texture;
}

sf::Sprite load_background(sf::Texture &background)
{
    sf::Sprite game_background(background);
    game_background.setOrigin(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    game_background.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    return game_background;
}