#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "world_cup/rng.hpp"
#include "mini_games/offense.hpp"

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
    // AbstractButton(sf::Color col, sf::Color col) 
        // : color_a_{col}
        // , color_b_{col}
        // , on_click_{[&] { std::cerr << "Default button operation\n"; }}
    // {}

    // Button that changes to color B when when the mouse is in the bounded box 
    AbstractButton(sf::Color col_a, sf::Color col_b = sf::Color::Black, 
        std::function<void(void)> on_click = [] {
            std::cerr << "Default Button Clicked\n";
        }) 
        : color_a_{col_a}
        , color_b_{col_b} 
        , on_click_{on_click}
    {}

    // Return the default color when not being interacted with
    auto color_a() const -> sf::Color { return color_a_; }
    // Return a second color when the mouse is hovered over the button
    auto color_b() const -> sf::Color { return color_b_; } 
    // return true when the mouse is in the button's bounded box
    // virtual auto update_color(float mouse_x, float mouse_y) -> const sf::Shape& = 0;
    // Set the behavior of this function once it's clicked
    void set_on_click(std::function<void(void)> on_click) {
        on_click_ = on_click;
    }

    void on_click() const {
        on_click_();
    }

    /**========================================================================
     *!                           Pure Virtual
     *========================================================================**/
    virtual auto mouse_in_bounded_box(float mouse_x, float mouse_y) const -> bool = 0;  
    virtual void update(float mouse_x, float mouse_y) = 0;
    virtual const sf::Shape& get_shape() const = 0;
    virtual void display(sf::RenderWindow &window) = 0;

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
 
    const sf::Shape& update_color(float mouse_x, float mouse_y) {
        if (mouse_in_bounded_box(mouse_x, mouse_y)) {
            rect_.setFillColor(color_b_);
            return rect_;
        } else {
            rect_.setFillColor(color_a_);
            return rect_;
        }
    }

    void update(float mouse_x, float mouse_y) override {
        update_color(mouse_x, mouse_y);
    }

    const sf::Shape& get_shape() const override {
        return rect_;
    }

    void display(sf::RenderWindow &window) override {
        window.draw(rect_);
        // std::cerr << "RectangleButton::display() called\n";
    }

protected:

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


// A TextButton is a rectangular button that has text displayed on it
class TextButton : public RectangleButton {

public:

    // We additionaly need text and character size for a TextButton 
    TextButton()
        : RectangleButton(sf::Color::Black, sf::Color::White, 30, 30, 400, 400) 
    {
        text_.setString("Default Button");
    }

    TextButton(sf::Color col_a, sf::Color col_b, float width, float height, float x, float y, std::string str = "Defualt")
        : RectangleButton(col_a, col_b, width, height, x, y) 
    {
        rect_.setPosition(x, y);
        text_.setString(str);
        text_.setCharacterSize(20);
        text_.setPosition(x + 20, y + 10);
        text_.setFillColor(col_b);
        std::cerr << "TextButton created with str: '" << str << "'\n";

    }

    // Update the Colors of the text and the rectangle
    void update(float mouse_x, float mouse_y) override {
        if (mouse_in_bounded_box(mouse_x, mouse_y)) {
            rect_.setFillColor(color_b_);
            text_.setFillColor(color_a_);
        } else {
            rect_.setFillColor(color_a_);
            text_.setFillColor(color_b_);
        }
    }

    // Draw to a RenderWindow this button and its text
    void display(sf::RenderWindow &window) override {
        // std::cerr << "TextButton::display() called\n";
        window.draw(rect_);
        window.draw(text_);
    }

    void set_font(sf::Font font) {
        text_.setFont(font);
    }


    void set_fill_color(sf::Color col) {
        text_.setFillColor(col);
    }


private:

    sf::Text text_;

};



inline auto mouse_x(const sf::RenderWindow& window) -> int { return sf::Mouse::getPosition(window).x; }
inline auto mouse_y(const sf::RenderWindow& window) -> int { return sf::Mouse::getPosition(window).y; }

class Screen {

public:

    Screen(sf::Color bg_color, sf::RenderWindow& window) 
        : bg_color_{bg_color}
        , window_{window}
    {

        font_.loadFromFile("arial.ttf");

    }

    Screen(const Screen &screen) = default;

    Screen& operator=(const Screen &screen) {

        this->buttons_ = screen.buttons_;
        this->bg_color_ = screen.bg_color_;
        this->text_buttons_ = screen.text_buttons_;
        return *this;

    }

    void add_bg(sf::Texture t) {
        draw_bg_ = true;
        bg_.setTexture(t);
    }

    // Called once per frame
    void display() {

        window_.clear(bg_color_);

        // if (draw_bg_) {
        //     window_.draw(bg_);
        // }

        for (auto &b : buttons_) {
            b.display(window_);
        }

        for (auto &b : text_buttons_) {
            // std::cerr << "Trying to draw text button\n";
            b.display(window_);
        }


        window_.display();

    }

    void update() {

        for (auto &b : buttons_) {
            b.update(mouse_x(window_), mouse_y(window_));
        }
        
        for (auto &b : text_buttons_) {
            b.update(mouse_x(window_), mouse_y(window_));
        }

    }

    void add_button(RectangleButton &button) {
        buttons_.push_back(button);
    }

    void add_text_button(TextButton &button) {
        button.set_font(font_);
        text_buttons_.push_back(button);
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

                    for (auto &b : text_buttons_) {
                        if (b.mouse_in_bounded_box(mouse_x(window_), mouse_y(window_))) {
                            b.on_click();
                        }
                    }
                }
            }
        }
    }


    std::vector<RectangleButton> buttons_;
    std::vector<TextButton> text_buttons_;



private:

    sf::Color bg_color_;
    sf::RenderWindow& window_;
    bool draw_bg_ = false;
    sf::Sprite bg_;
    sf::Font font_;

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

        // Let's get a sprite to draw as the background


        // Create the main menu
        RectangleButton start_button(sf::Color::Black, sf::Color::White, 200, 100, 250, 350);
        TextButton text_button(sf::Color::Blue, sf::Color::Black, 100, 50, 250, 450, "My Button");
        TextButton text_button2(sf::Color::White, sf::Color::Black, 200, 200, 0, 0, "Second Button");
        text_button.set_on_click([&] { std::cerr << "My button says hi!\n"; });
        text_button2.set_on_click([&] { std::cerr << "Where is my fucking text!\n"; });
        text_button2.set_fill_color(sf::Color::Green);

        start_button.set_on_click([&] { this->screen_ = second_menu(); });

        std::cerr << "Main menu created\n"; 

        Screen main_menu(sf::Color::Red, window_);

        main_menu.buttons_.push_back(start_button);
        main_menu.text_buttons_.push_back(text_button);
        main_menu.text_buttons_.push_back(text_button2);

        // let's get a backgroudn
        // sf::Texture t;
        // t.loadFromFile("cartoon_soccer_field.png");
        // main_menu.add_bg(t);

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