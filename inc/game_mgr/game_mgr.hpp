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

private:

    Menu menu_;
    sf::RenderWindow window_;

};

} // namespace all_star::game_mgr