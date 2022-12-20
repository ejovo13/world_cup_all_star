#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "game_mgr/buttons.hpp"

namespace all_star::game_mgr {

inline auto mouse_x(const sf::RenderWindow& window) -> int { return sf::Mouse::getPosition(window).x; }
inline auto mouse_y(const sf::RenderWindow& window) -> int { return sf::Mouse::getPosition(window).y; }

inline auto mouse_x(const sf::Event event) -> int {
    return event.mouseButton.x;
}

inline auto mouse_y(const sf::Event event) -> int {
    return event.mouseButton.y;
}

enum ScreenSelection {
    kMain = 0,
    kHelp = 1,
    kSecond = 2,
    kThird = 3,
};

class Screen {

public:

    Screen(sf::Color bg_color, sf::RenderWindow& window, sf::Font &font, std::string description = "Default menu") 
        : font_{font}
        , window_{window}
        , bg_color_{bg_color}
        , description_{description}
    {}

    Screen(const Screen &screen) = default;

    // Used to switch contexts
    Screen& operator=(const Screen &screen);

    void add_bg(const sf::Texture &t); 

    // These three functions are used in the main game loop
    void display(); 
    void poll_events(); 
    void update(); 

    void add_button(RectangleButton &button); 
    void add_text_button(TextButton &button); 

    // Close all of the elements in this screen
    virtual void close() {

        buttons_.clear();
        text_buttons_.clear();
    }

    sf::Color get_bg_color() const { return bg_color_; }

    std::vector<RectangleButton> buttons_;
    std::vector<TextButton> text_buttons_;
    std::function<void(void)> loop_; // main looping function that can be set

private:

    sf::Font &font_;
    sf::RenderWindow& window_;
    bool draw_bg_ = false;
    sf::Sprite bg_;
    sf::Color bg_color_;
    std::string description_;

};

} // namespace all_star::game_mgr