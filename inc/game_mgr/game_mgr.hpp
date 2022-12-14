#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

namespace all_star::game_mgr {


// Should this be an enum of menus or should these be different classes????
enum class Menu { 
    kMain = 0,
    kTeamSelection = 1,
    kHelp = 2
};

// Abstract base class with two derivatives, circle button and square button
class AbstractButton {

public:

    // Button that doesnt change color when we hover over it with a mouse
    AbstractButton(sf::Color col) : color_a_{col}, color_b_{col} {}
    // Button that changes to color B when when the mouse is in the bounded box 
    AbstractButton(sf::Color col_a, sf::Color col_b) : color_a_{col_a}, color_b_{col_b} {}

    // Return the default color when not being interacted with
    auto color_a() const -> sf::Color { return color_a_; }
    auto color_b() const -> sf::Color { return color_b_; } 
    // return true when the mouse is in the button's bounded box
    virtual auto mouse_in_bounded_box(float mouse_x, float mouse_y) const -> bool = 0;  
    virtual auto update_color(float mouse_x, float mouse_y) -> const sf::Shape& = 0;

protected:

    sf::Color color_a_;
    sf::Color color_b_;

private:

};

class RectangleButton : public AbstractButton {

public:

    // x and y are the top left corner of the rectangle
    RectangleButton(sf::Color col_a, sf::Color col_b, float width, float height, float x, float y)
        : AbstractButton(col_a, col_b)
        , rect_{sf::Vector2f(width, height)} 
    {
        rect_.setPosition(x, y);
    }

    bool mouse_in_bounded_box(float mouse_x, float mouse_y) const override {

        float x = x_(), y = y_(), w = w_(), h = h_();

        return mouse_x >= x && 
               mouse_x <= x + w &&
               mouse_y >= y &&
               mouse_y <= y + h;
    }
 
    const sf::Shape& update_color(float mouse_x, float mouse_y) override {
        if (mouse_in_bounded_box(mouse_x, mouse_y)) {
            rect_.setFillColor(color_b_);
            return rect_;
        } else {
            rect_.setFillColor(color_a_);
            return rect_;
        }
    }

    const sf::Shape& get_shape() const {
        return rect_;
    }

private:

    sf::RectangleShape rect_;
    
    auto x_() const -> float { 
        auto pos = rect_.getPosition();
        return pos.x;
    }
    
    auto y_() const -> float { 
        auto pos = rect_.getPosition();
        return pos.y;
    }

    auto w_() const -> float {
        auto size = rect_.getSize();
        return size.x;
    }

    auto h_() const -> float {
        auto size = rect_.getSize();
        return size.y;
    }

};






// The main driver of our entire game, we will create a new window with GameManager.start()
class GameManager {

public:

    GameManager() 
      : menu_{Menu::kMain}
      , window_{sf::VideoMode(800, 600), "SFML window"}
    {}

    GameManager(int w, int h) 
      : menu_{Menu::kMain}
      , window_{sf::VideoMode(w, h), "SFML window"}
    {}

    auto start() -> void;

    // get mouse x relavent to the currently rendered window
    auto get_mouse_x() const -> int {
        auto vec = sf::Mouse::getPosition(window_);
        return vec.x;
    }

    // get mouse y relavent to the currently rendered window
    auto get_mouse_y() const -> int {
        auto vec = sf::Mouse::getPosition(window_);
        return vec.y;
    }

    auto draw_button(const AbstractButton& button) const -> void {

        // If the mouse is in the button's bounded box, then draw color A

        // Else, draw color B    


    }

private:

    Menu menu_;
    sf::RenderWindow window_;

};

} // namespace all_star::game_mgr