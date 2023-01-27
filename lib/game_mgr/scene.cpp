#include "game_mgr/scene.hpp"

namespace all_star::game_mgr {

// Used to switch contexts
Screen& Screen::operator=(const Screen &screen) {

    this->buttons_ = screen.buttons_;
    this->bg_color_ = screen.bg_color_;
    this->text_buttons_ = screen.text_buttons_;
    this->loop_ = screen.loop_;
    this->description_ = screen.description_;
    this->font_ = screen.font_;
    this->bg_ = screen.bg_;
    this->draw_bg_ = screen.draw_bg_;

    return *this;
}

void Screen::add_bg(const sf::Texture &t) {
    draw_bg_ = true;
    bg_.setTexture(t);
}

// Called once per frame
void Screen::display() {

    window_.clear(bg_color_);

    if (draw_bg_) {
        window_.draw(bg_);
    }

    for (auto &b : text_buttons_) {
        // std::cerr << "Trying to draw text button\n";
        b.display(window_);
    }

    for (auto &b : buttons_) {
        b.display(window_);
    }

    for (auto &d : drawable_items_) {
        window_.draw(*d);
    }

    for (auto &tb : text_boxes_) {
        tb.display(window_);
    }

    window_.display();
}

void Screen::update() {

    for (auto &b : buttons_) {
        b.update(mouse_x(window_), mouse_y(window_));
    }
    
    for (auto &b : text_buttons_) {
        b.update(mouse_x(window_), mouse_y(window_));
    }
}

void Screen::add_button(RectangleButton &button) {
    buttons_.push_back(button);
}

void Screen::add_text_box(TextBox &tb) {
    text_boxes_.push_back(tb);
}

// Take a drawable object and push it to the list of drawable objects
void Screen::add_drawable(std::unique_ptr<sf::Drawable> drawable) {
    drawable_items_.push_back(std::move(drawable)); 
}

void Screen::add_text_button(TextButton &button) {
    button.set_font(font_);
    text_buttons_.push_back(button);
}

void Screen::poll_events() {

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

} // namespace all_star::game_mgr