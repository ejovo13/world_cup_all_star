#include <SFML/Graphics.hpp>

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

    GameManager() : menu_{Menu::kMain} {}



    auto start() const -> void;

private:

    Menu menu_;

};

} // namespace all_star::game_mgr