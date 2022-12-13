/**========================================================================
 * ?                          game_mgr.cpp
 * @brief   : A Game manager is responsible for the handling of SFML's windows,
 * switching between menus, keeping track of scores, etc etc.
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-13
 *========================================================================**/

// So what the hell do we actually have to implement?

// The very first thing that we need to work on is a simple interface that allows us to switch between different contexts

// What contexts shall exist in this game?

// What menus do we need?
// - main menu
// - team selection menu
// - information menu
// - after we select a team we should immediately begin the mini games...

// We are going to need a lot of classes to get this thing done.
// We will have button types that are clickable and will switch the context of the menu
#include "game_mgr/game_mgr.hpp"

namespace all_star::game_mgr {


auto GameManager::start() const -> void {

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

}


// Abstract base class with two derivatives, circle button and square button
class AbstractButton {

public:

protected:

private:


};



};

