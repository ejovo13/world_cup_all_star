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

// sf::Font TextButton::s_font_{};
// TextButton::s_font_.loadFromFile("arial.ttf");

// bool TextButton::s_font_loaded_ = false;



auto GameManager::start() -> void {

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw std::invalid_argument("Bad font");
    }



    // Initial settings
    // window.setTitle("SFML window");
    // window.setSize(sf::Vector2u(800, 600));
    window_.setPosition(sf::Vector2i(50, 50));
    window_.setVerticalSyncEnabled(true);
    window_.setFramerateLimit(60);

    // Return the position of the mouse as a string that we can display 
    // with a sf::Text object
    auto mouse_pos_str = [&] () -> std::string {

        std::string x = std::to_string(mouse_x(window_));
        std::string y = std::to_string(mouse_y(window_));
        std::string lp = "(";
        std::string rp = ")";
        std::string com = ", ";

        return lp + x + com + y + rp;
    };

    // sf::Text all_star;
    sf::Text frame_count;
    sf::Text mouse_pos;

    // all_star.setString("All Star World Cup");
    // all_star.setPosition(320, 300);
    // all_star.setFont(font);
    // all_star.setCharacterSize(24);
    // all_star.setFillColor(sf::Color::Red);

    int frame_count_i = 0;
    std::cerr << "Starting game\n";

    while (window_.isOpen())
    {
        screen_.poll_events();
        screen_.update();
        screen_.display();
    }

}

} // namespace all_start::game_mgr