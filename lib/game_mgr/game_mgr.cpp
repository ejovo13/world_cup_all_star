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

    std::cerr << "Starting game\n";

    // Main game loop
    while (window_.isOpen())
    {
        current_screen_->display();
        current_screen_->poll_events();

        if (should_switch_) {
            switch_screens(next_);
        } else {
            current_screen_->update();
        }

        frame_count_++;
    }
}

// Destroy all of the contents of the old screen, and make a new one
void GameManager::switch_screens(ScreenSelection next) {

    current_screen_->close();
    should_switch_ = false;
    current_screen_ = get_screen(next);
}

// Get a constructred Scene object by passing in a ScreenSelection enumerator
auto GameManager::get_screen(ScreenSelection next) -> std::unique_ptr<Screen> {

    switch (next) {
        
    case kMain: return main_menu(); break;
    case kHelp: return help_menu(); break;
    case kSecond: return second_menu(); break;
    case kThird: return third_menu(); break;
    case kOffense: return offense_game(); break;
    default: return main_menu(); break;

    } 
}

// Trigger a context switch to take place on the next frame
// If we have a button that tries to immediately switch, we end up 
// continuing to poll events for buttons that no longer exist
void GameManager::trigger_switch(ScreenSelection next) {
    std::cerr << "Triggering switch to " << next << "\n";
    should_switch_ = true;
    next_ = next;
}


/**========================================================================
 *!                          Menu Functions 
*========================================================================**/
auto GameManager::main_menu() -> std::unique_ptr<Screen> {

    sf::Color teal { 46, 167, 204}; // rgb(46, 167, 204)
    sf::Color brown{154, 115, 77 }; // rgb(154, 115, 77)

    // Create a new main menu button
    auto create_button = [&] (float w, float h, float x, float y, std::string txt) -> TextButton {
        return TextButton(teal, sf::Color::White, w, h, x, y, font_, txt);
    };

    auto start_button = create_button(200, 100, 300, 400, "Start");
    auto help_button = create_button(200, 100, 300, 600, "My help button");
    auto offense_button = create_button(200, 100, 300, 700, "Offense Minigame");

    Screen *main_menu = new Screen(sf::Color::Red, window_, font_);

    start_button.set_on_click([&] { trigger_switch(kSecond); });
    help_button.set_on_click([&] { trigger_switch(kHelp); });
    offense_button.set_on_click([&] { trigger_switch(kOffense); });

    std::cerr << "Main menu created\n"; 


    main_menu->text_buttons_.push_back(start_button);
    main_menu->text_buttons_.push_back(help_button);
    main_menu->text_buttons_.push_back(offense_button);

    // main_menu.text_buttons_.push_back(text_button);
    // main_menu.text_buttons_.push_back(text_button2);

    // let's get a backgroudn
    main_menu->add_bg(textures_[kSoccerField]);

    return std::unique_ptr<Screen>(main_menu);

}

auto GameManager::help_menu() -> std::unique_ptr<Screen> {

    Screen* help = new Screen(sf::Color::Green, window_, font_, "Help Menu");

    // Let's add some text
    // ...
    //


    // Button to take us back to the main menu
    TextButton mm_button = TextButton(sf::Color::Black, sf::Color::Red, 200, 100, 50, 50, font_, "Main Menu");

    mm_button.set_on_click([&] { switch_screens(kMain); });

    help->add_text_button(mm_button);

    return std::unique_ptr<Screen>(help);
}

auto GameManager::second_menu() -> std::unique_ptr<Screen> {

    // Create the main menu
    RectangleButton magic_button(sf::Color::Magenta, sf::Color::Black, 30, 30, world_cup::rng::runif(50, 750), world_cup::rng::runif(50, 600));
    magic_button.set_on_click([&] { 
        this->current_screen_ = main_menu(); 
        std::cerr << "WHAT THE FUCKKKKKK\n";
    });

    Screen *main_menu = new Screen(sf::Color::Black, window_, font_);

    // Let's try and create a screen with some text to display
    main_menu->buttons_.push_back(magic_button);

    return std::unique_ptr<Screen>(main_menu);

}

auto GameManager::third_menu() -> std::unique_ptr<Screen> {

    // Let's add a third menu that only contains the all star text
    Screen *third = new Screen(sf::Color::White, window_, font_);

    std::cerr << "Third menu initialized\n";

    third->loop_ = [this, &third] {

        sf::Text all_star;
        all_star.setString("All Star World Cup");
        all_star.setPosition(320, 300);
        all_star.setFont(font_);
        all_star.setCharacterSize(24);
        // all_star.setSize(20);
        all_star.setFillColor(sf::Color::Black);
        std::cerr << "Text created\n"; 

        sf::Event event;
        while (this->window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window_.close();
        }

        this->window_.clear(third->get_bg_color());
        this->window_.draw(all_star);
        this->window_.display();
    };

    return std::unique_ptr<Screen>(third);
}

// using all_star::mini_games;

class OffenseGame : public Screen {

public: 

    // I need to override the display function
    OffenseGame(sf::Texture &ball_texture, sf::Font &font, sf::RenderWindow &window_, sf::Texture &bg) 
        : Screen(sf::Color::Black, window_, font, "Offense Game")
        , minigame_{ball_texture, font}
        , bg_{mini_games::load_background(bg)}
    {}

    void display() override {

        minigame_.display(window_, bg_);

    }

    void poll_events() override {

        sf::Event event;
        while (window_.pollEvent(event)) // check if user does something
        {
            if (event.type == sf::Event::Closed)
            {
                window_.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                minigame_.update_balls(event);
            }
        }
    }

    void update() override {

        if (!minigame_.checklose()) {
            on_lose_();
        } else {
            minigame_.update_game();
        }
    }

    void set_on_lose(std::function<void(void)> on_lose) {
        on_lose_ = on_lose;
    }


private:

    mini_games::Game minigame_;
    std::function<void(void)> on_lose_; // action to perform on a loss
    sf::Sprite bg_;


};

auto GameManager::offense_game() -> std::unique_ptr<Screen> {

    // I want to create an offense Screen who's display function is customized
    OffenseGame *og = new OffenseGame(textures_[kBall], font_, window_, textures_[kOffenseBG]);

    og->set_on_lose(std::function<void(void)>(
        [&] {
            trigger_switch(kMain);
        }
    ));

    return std::unique_ptr<Screen>(og);
}


/**========================================================================
 *!                           Utility Functions
*========================================================================**/
// Preload textures and reference them by a TextureSelection enum    
auto GameManager::load_textures() const -> std::unordered_map<TextureSelection, sf::Texture> {

    std::unordered_map<TextureSelection, sf::Texture> map; 

    map[kSoccerField] = load_texture("cartoon_soccer_field.png");
    map[kOffenseBG]   = load_texture("offense_background.png");
    map[kBall]        = load_texture("ball.png");

    std::cerr << "Succesfully loaded textures\n";
    return map;
}

auto GameManager::load_arial() const -> sf::Font {
    return load_font("arial.ttf");
}


auto mouse_pos_str(sf::RenderWindow &window_) -> std::string {

    std::string x = std::to_string(mouse_x(window_));
    std::string y = std::to_string(mouse_y(window_));
    std::string lp = "(";
    std::string rp = ")";
    std::string com = ", ";

    return lp + x + com + y + rp;
};




/**========================================================================
 *!                           Functions for loading textures
 *========================================================================**/
auto load_texture(const std::string &filename) -> sf::Texture {

    std::string path  = std::string("resources/") + filename;
    std::string path2 = std::string("../resources/") + filename;

    sf::Texture texture;

    if (texture.loadFromFile(path)) {
        // then we found the texture
        return texture;
    } else if (texture.loadFromFile(path2)) {
        return texture;
    } else {
        std::string err_msg = std::string("Texture: '") + filename + std::string("' not found");
        throw std::invalid_argument(err_msg);
    }

}

auto load_font(const std::string &filename) -> sf::Font {

    std::string path  = std::string("resources/") + filename;
    std::string path2 = std::string("../resources/") + filename;

    sf::Font font;

    if (font.loadFromFile(path)) {
        // then we found the font 
        return font;
    } else if (font.loadFromFile(path2)) {
        return font;
    } else {
        std::string err_msg = std::string("Font '") + filename + std::string("' not found");
        throw std::invalid_argument(err_msg);
    }

}



} // namespace all_start::game_mgr