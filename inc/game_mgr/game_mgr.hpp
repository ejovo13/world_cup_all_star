#include <iostream>
#include <string>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "world_cup/rng.hpp"

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
    AbstractButton(sf::Color col) 
        : color_a_{col}
        , color_b_{col}
        , on_click_{[&] { std::cerr << "Default button operation\n"; }}
    {}

    // Button that changes to color B when when the mouse is in the bounded box 
    AbstractButton(sf::Color col_a, sf::Color col_b) 
        : color_a_{col_a}
        , color_b_{col_b} 
        , on_click_{[&] { std::cerr << "Default button operation\n"; }}
    {}

    // Return the default color when not being interacted with
    auto color_a() const -> sf::Color { return color_a_; }
    // Return a second color when the mouse is hovered over the button
    auto color_b() const -> sf::Color { return color_b_; } 
    // return true when the mouse is in the button's bounded box
    virtual auto mouse_in_bounded_box(float mouse_x, float mouse_y) const -> bool = 0;  
    virtual auto update_color(float mouse_x, float mouse_y) -> const sf::Shape& = 0;

    // Set the behavior of this function once it's clicked
    void set_on_click(std::function<void(void)> on_click) {
        on_click_ = on_click;
    }

    void on_click() const {
        on_click_();
    }

    virtual const sf::Shape& get_shape() const = 0;

protected:

    sf::Color color_a_;
    sf::Color color_b_;
    std::function<void(void)> on_click_; // Something that happens when a function is clicked

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

        return mouse_x >= x && mouse_x <= x + w &&
               mouse_y >= y && mouse_y <= y + h;
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

    const sf::Shape& get_shape() const override {
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


inline auto mouse_x(const sf::RenderWindow& window) -> int { return sf::Mouse::getPosition(window).x; }
inline auto mouse_y(const sf::RenderWindow& window) -> int { return sf::Mouse::getPosition(window).y; }

class Screen {

public:

    Screen(sf::Color bg_color, sf::RenderWindow& window) 
        : bg_color_{bg_color}
        , window_{window}
    {}

    Screen(const Screen &screen) = default;

    Screen& operator=(const Screen &screen) {

        this->buttons_ = screen.buttons_;
        this->bg_color_ = screen.bg_color_;
        return *this;

    }

    // Called once per frame
    void display() {

        window_.clear(bg_color_);

        for (auto &b : buttons_) {
            window_.draw(b.get_shape());
        }

        window_.display();

    }

    void update() {

        for (auto &b : buttons_) {
            b.update_color(mouse_x(window_), mouse_y(window_));
        }

    }

    void add_button(RectangleButton &button) {
        buttons_.push_back(button);
    }

    void poll_events() {

        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (auto &b : buttons_) {
                        if (b.mouse_in_bounded_box(mouse_x(window_), mouse_y(window_))) {
                            b.on_click();
                        }
                    }
                }
            }
        }
    }


    std::vector<RectangleButton> buttons_;



private:

    sf::Color bg_color_;
    sf::RenderWindow& window_;

};



// The main driver of our entire game, we will create a new window with GameManager.start()
class GameManager {

public:

    GameManager() 
      : menu_{Menu::kMain}
      , window_{sf::VideoMode(800, 600), "SFML window"}
      , screen_{main_menu()}
    {}

    GameManager(int w, int h) 
      : menu_{Menu::kMain}
      , window_{sf::VideoMode(w, h), "SFML window"}
      , screen_{main_menu()}
    {}

    auto start() -> void;

    /**========================================================================
     *!                           Static Menus
     *========================================================================**/
    auto main_menu() -> Screen {

        // Create the main menu
        RectangleButton start_button(sf::Color::Red, sf::Color::White, 200, 100, 250, 350);
        start_button.set_on_click([&] { this->screen_ = second_menu(); });

           Screen main_menu(sf::Color::White, window_);

        main_menu.buttons_.push_back(start_button);

        return main_menu;

    }

    auto second_menu() -> Screen {

        // Create the main menu
        RectangleButton magic_button(sf::Color::Magenta, sf::Color::Black, 30, 30, world_cup::rng::runif(50, 750), world_cup::rng::runif(50, 600));
        magic_button.set_on_click([&] { this->screen_ = main_menu(); });

        Screen main_menu(sf::Color::Black, window_);

        main_menu.buttons_.push_back(magic_button);

        return main_menu;

    }


private:

    Menu menu_;
    sf::RenderWindow window_;
    Screen screen_; // The current screen to display

};

// Start implementing the different menu types




} // namespace all_star::game_mgr