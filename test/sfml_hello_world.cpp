#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    /**========================================================================
     *!                           Basic font
     *========================================================================**/
    sf::Font font;
    if (!font.loadFromFile("story_element.ttf")) {
        throw std::invalid_argument("Bad font");
    }

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");


    // Initial settings
    // window.setTitle("SFML window");
    // window.setSize(sf::Vector2u(800, 600));
    window.setPosition(sf::Vector2i(50, 50));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);


    sf::Text text;
    text.setPosition(320, 300);
    text.setFont(font);
    text.setString("All Star World Cup");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);


    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(text);


        window.display();
    }

    return EXIT_SUCCESS;
}