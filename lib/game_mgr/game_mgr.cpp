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

    auto new_text = [&] (std::string str, int xpos, int ypos, sf::Font font, int char_size, sf::Color col) {
        sf::Text obj;
        obj.setString(str);
        obj.setPosition(xpos, ypos);
        obj.setFont(font);
        obj.setCharacterSize(char_size);
        obj.setFillColor(col);
        return obj;
    };

    // auto mouse_pos_str = [&] () -> std::string {

    //     std::string x = std::to_string(get_mouse_x());
    //     std::string y = std::to_string(get_mouse_y());
    //     std::string lp = "(";
    //     std::string rp = ")";
    //     std::string com = ", ";

    //     return lp + x + com + y + rp;
    // };

    sf::Text all_star = new_text("All Star World Cup", 320, 300, font, 24, sf::Color::Red);
    sf::Text frame_count;
    sf::Text mouse_pos;

    // update_text_obj(frame_count, "0", 10, 20, font, 10, sf::Color::White);
    // update_text_obj(mouse_pos, "(0, 0)", 750, 20, font, 10, sf::Color::White);
    // update_text_obj(all_star, "All Star World Cup", 320, 300, font, 24, sf::Color::Red);

    std::cerr << "All star str: " << all_star.getString().toAnsiString() << "\n";

    // sf::Text all_star;

    // all_star.setString("WTF");
    // all_star.setPosition(320, 300);
    // all_star.setFont(font);
    // all_star.setCharacterSize(24);
    // all_star.setFillColor(sf::Color::Red);

    int frame_count_i = 0;
    std::cerr << "Starting game\n";

    while (window_.isOpen())
    {
        frame_count.setString(std::to_string(frame_count_i));
        // mouse_pos.setString(mouse_pos_str());

        // Process events
        sf::Event event;
        while (window_.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        window_.clear();

        window_.draw(all_star);
        // window_.draw(frame_count);
        // window_.draw(mouse_pos);

        window_.display();

        frame_count_i ++;
    }

}


// Abstract base class with two derivatives, circle button and square button
class AbstractButton {

public:

protected:

private:


};



};

