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
        current_screen_.display();
        current_screen_.poll_events();

        if (should_switch_) {
            switch_screens(next_);
        } else {
            current_screen_.update();
        }

        frame_count_++;
    }
}

// Destroy all of the contents of the old screen, and make a new one
void GameManager::switch_screens(ScreenSelection next) {

    current_screen_.close();
    should_switch_ = false;
    current_screen_ = get_screen(next);
}

// Get a constructred Scene object by passing in a ScreenSelection enumerator
auto GameManager::get_screen(ScreenSelection next) -> Screen {

    switch (next) {
        
    case kMain: return main_menu(); break;
    case kHelp: return help_menu(); break;
    case kSecond: return second_menu(); break;
    case kThird: return third_menu(); break;
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
auto GameManager::main_menu() -> Screen {

    sf::Color teal { 46, 167, 204}; // rgb(46, 167, 204)
    sf::Color brown{154, 115, 77 }; // rgb(154, 115, 77)

    // Create a new main menu button
    auto create_button = [&] (float w, float h, float x, float y, std::string txt) -> TextButton {
        return TextButton(teal, sf::Color::White, w, h, x, y, font_, txt);
    };

    auto start_button = create_button(200, 100, 300, 400, "Start");
    auto help_button = create_button(200, 100, 300, 600, "My help button");

    Screen main_menu(sf::Color::Red, window_, font_);

    start_button.set_on_click([&] { trigger_switch(kSecond); });
    help_button.set_on_click([&] { trigger_switch(kHelp); });

    std::cerr << "Main menu created\n"; 


    main_menu.text_buttons_.push_back(start_button);
    main_menu.text_buttons_.push_back(help_button);

    // main_menu.text_buttons_.push_back(text_button);
    // main_menu.text_buttons_.push_back(text_button2);

    // let's get a backgroudn
    main_menu.add_bg(textures_[kSoccerField]);

    return main_menu;

}

auto GameManager::help_menu() -> Screen {

    Screen help {sf::Color::Green, window_, font_, "Help Menu"};

    // Let's add some text
    // ...
    //


    // Button to take us back to the main menu
    TextButton mm_button = TextButton(sf::Color::Black, sf::Color::Red, 200, 100, 50, 50, font_, "Main Menu");

    mm_button.set_on_click([&] { switch_screens(kMain); });

    help.add_text_button(mm_button);

    return help;
}

auto GameManager::second_menu() -> Screen {

    // Create the main menu
    RectangleButton magic_button(sf::Color::Magenta, sf::Color::Black, 30, 30, world_cup::rng::runif(50, 750), world_cup::rng::runif(50, 600));
    magic_button.set_on_click([&] { 
        this->current_screen_ = main_menu(); 
        std::cerr << "WHAT THE FUCKKKKKK\n";
    });

    Screen main_menu(sf::Color::Black, window_, font_);

    // Let's try and create a screen with some text to display
    main_menu.buttons_.push_back(magic_button);

    return main_menu;

}

auto GameManager::third_menu() -> Screen {

    // Let's add a third menu that only contains the all star text
    Screen third(sf::Color::White, window_, font_);

    std::cerr << "Third menu initialized\n";

    third.loop_ = [this, &third] {

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

        this->window_.clear(third.get_bg_color());
        this->window_.draw(all_star);
        this->window_.display();
    };

    return third;
}


/**========================================================================
 *!                           Utility Functions
*========================================================================**/
// Preload textures and reference them by a TextureSelection enum    
auto GameManager::load_textures() const -> std::unordered_map<TextureSelection, sf::Texture> {

    std::unordered_map<TextureSelection, sf::Texture> map; 

    sf::Texture main_menu_bg;
    if (!main_menu_bg.loadFromFile("cartoon_soccer_field.png")) {
        throw std::invalid_argument("Cartoon soccer field not found");
    }

    map[kSoccerField] = main_menu_bg;

    std::cerr << "Succesfully loaded textures\n";
    return map;
}

auto GameManager::load_arial() const -> sf::Font {

    sf::Font arial;
    if(!arial.loadFromFile("arial.ttf")) {
        throw std::invalid_argument("Arial not found");
    };

    return arial;
}


auto mouse_pos_str(sf::RenderWindow &window_) -> std::string {

    std::string x = std::to_string(mouse_x(window_));
    std::string y = std::to_string(mouse_y(window_));
    std::string lp = "(";
    std::string rp = ")";
    std::string com = ", ";

    return lp + x + com + y + rp;
};

} // namespace all_start::game_mgr