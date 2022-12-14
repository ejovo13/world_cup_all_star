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

    // Return the position of the mouse as a string that we can display 
    // with a sf::Text object
    auto mouse_pos_str = [&] () -> std::string {

        std::string x = std::to_string(get_mouse_x());
        std::string y = std::to_string(get_mouse_y());
        std::string lp = "(";
        std::string rp = ")";
        std::string com = ", ";

        return lp + x + com + y + rp;
    };

    sf::Text all_star;
    sf::Text frame_count;
    sf::Text mouse_pos;

    all_star.setString("All Star World Cup");
    all_star.setPosition(320, 300);
    all_star.setFont(font);
    all_star.setCharacterSize(24);
    all_star.setFillColor(sf::Color::Red);

    frame_count.setString("0");
    frame_count.setPosition(10, 20);
    frame_count.setFont(font);
    frame_count.setCharacterSize(10);
    frame_count.setFillColor(sf::Color::White);

    mouse_pos.setString("(0, 0)");
    mouse_pos.setPosition(750, 20);
    mouse_pos.setFont(font);
    mouse_pos.setCharacterSize(10);
    mouse_pos.setFillColor(sf::Color::White);

    // Now let's try creating a square rectangle
    RectangleButton button1(sf::Color::Red, sf::Color::White, 100, 20, 250, 350); 
    RectangleButton button2(sf::Color::Red, sf::Color::White, 100, 20, 370, 350); 

    button1.set_on_click([&] { std::cerr << "Button 1 pressed!!\n"; } );
    button2.set_on_click([&] { std::cerr << "Button 2 pressed!!\n"; } );

    int frame_count_i = 0;
    std::cerr << "Starting game\n";

    while (window_.isOpen())
    {
        frame_count.setString(std::to_string(frame_count_i));
        mouse_pos.setString(mouse_pos_str());
        button1.update_color(get_mouse_x(), get_mouse_y());
        button2.update_color(get_mouse_x(), get_mouse_y());


        // Process events
        sf::Event event;
        while (window_.pollEvent(event))
        {
            /**========================================================================
             *!                           Closed window
             *========================================================================**/
            if (event.type == sf::Event::Closed)
                window_.close();

            /**========================================================================
             *!                           Mouse Clicked
             *========================================================================**/
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    
                    // Button 1:
                    if (button1.mouse_in_bounded_box(get_mouse_x(), get_mouse_y())) {
                        button1.on_click();
                    }

                    if (button2.mouse_in_bounded_box(get_mouse_x(), get_mouse_y())) {
                        button2.on_click();
                    }
                }
            }
        }

        window_.clear();

        window_.draw(all_star);
        window_.draw(frame_count);
        window_.draw(mouse_pos);
        window_.draw(button1.get_shape());
        window_.draw(button2.get_shape());

        window_.display();

        frame_count_i ++;
    }

}

}
