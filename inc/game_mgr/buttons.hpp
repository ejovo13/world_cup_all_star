/**========================================================================
 * ?                          buttons.hpp
 * @brief   : All about buttons
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-20
 *========================================================================**/

#pragma once

#include <iostream>
#include <string>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "world_cup/rng.hpp"
#include "mini_games/offense.hpp"

namespace all_star::game_mgr {

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
    virtual void update(sf::Event event) = 0;
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

    void update(sf::Event event) {
        update_color(event.mouseButton.x, event.mouseButton.y);
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

    TextButton(sf::Color col_a, sf::Color col_b, float width, float height, float x, float y, const sf::Font& font, std::string str = "Defualt", int char_size = 30)
        : RectangleButton(col_a, col_b, width, height, x, y)
        , x_offset_{10}
        , y_offset_{10}
    {


        // Figure out the number of characters in the string
        // int nchar = str.size();
        // assume we want a size offset of 10% in each direction
        // nchar * CharacterSize = 0.8 * width
        // CharacterSize = 0.8 * width / nchar

        // int char_size = 0.8 * width / nchar;
        int x_offset = 0.1 * width;
        int y_offset = 0.1 * height;

        rect_.setPosition(x, y);
        text_.setString(str);
        text_.setCharacterSize(char_size);
        text_.setPosition(x + x_offset, y + y_offset);
        text_.setFillColor(col_b);
        text_.setFont(font);
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

        if (this->text_.getFont() == NULL) {
            throw std::invalid_argument("Font is not properly loaded");
        }

        window.draw(rect_);
        window.draw(text_); 
    }

    void set_font(const sf::Font &font) {
        text_.setFont(font);
    }


    void set_fill_color(sf::Color col) {
        text_.setFillColor(col);
    }

    void set_y_offset(float y) {
        y_offset_ = y;
    }

    void set_x_offset(float x) {
        x_offset_ = x;
    }


private:

    sf::Text text_;
    float x_offset_; // x and y offset of the underlying text
    float y_offset_;


};

} // namespace all_star::game_mgr