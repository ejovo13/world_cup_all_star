#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "world_cup/rng.hpp"
#include "mini_games/offense.hpp"
#include "game_mgr/buttons.hpp"
#include "game_mgr/scene.hpp"
#include "mini_games/offense.hpp"


namespace all_star::game_mgr {

// The main driver of our entire game, we will create a new window with GameManager.start()
class GameManager {

public:

    enum TextureSelection {
        kSoccerField = 0,
        kOffenseBG = 1,
        kBall = 2,
    };

    GameManager(int w = 800, int h = 800) 
      : window_{sf::VideoMode(w, h), "SFML window"}
      , textures_{load_textures()}
      , team_selected_{-1}
      , current_screen_{main_menu()}
      , font_{load_arial()}
    {

        // Initial window settings
        window_.setPosition(sf::Vector2i(50, 50));
        window_.setVerticalSyncEnabled(true);
        window_.setFramerateLimit(fps_);

    }

    auto start() -> void;

    void select_team(int x) { team_selected_ = x; }
    int get_selected_team() const { return team_selected_; }

    // Destroy all of the contents of the old screen, and make a new one
    void switch_screens(ScreenSelection next);
    
    // Get a constructred Scene object by passing in a ScreenSelection enumerator
    // Create a new std::unique_ptr<Screen>
    auto get_screen(ScreenSelection next) -> std::unique_ptr<Screen>;

    // Trigger a context switch to take place on the next frame
    // If we have a button that tries to immediately switch, we end up 
    // continuing to poll events for buttons that no longer exist
    void trigger_switch(ScreenSelection next);


    /**========================================================================
     *!                          Menu Functions 
     *========================================================================**/
    auto main_menu() -> std::unique_ptr<Screen>; 
    auto help_menu() -> std::unique_ptr<Screen>; 
    auto second_menu() -> std::unique_ptr<Screen>; 
    auto third_menu() -> std::unique_ptr<Screen>; 
    auto offense_game() -> std::unique_ptr<Screen>;
    auto team_select() -> std::unique_ptr<Screen>;

    /**========================================================================
     *!                        Functions for unified GUI
     *========================================================================**/
    sf::Color teal()  const { return sf::Color(46, 167, 204); } // rgb(46, 167, 204)
    sf::Color brown() const { return sf::Color(154, 115, 77); } // rgb(154, 115, 77)


private:

    /**========================================================================
     *!                           Utility Functions
     *========================================================================**/
    // Preload textures and reference them by a TextureSelection enum    
    auto load_textures() const -> std::unordered_map<TextureSelection, sf::Texture>; 

    auto load_arial() const -> sf::Font; 

    sf::RenderWindow window_;
    std::unordered_map<TextureSelection, sf::Texture> textures_;
    int team_selected_ = -1; // Number between 0 and 47 indicating the team that was selected in the team selection screen
    std::unique_ptr<Screen> current_screen_; // The current screen to display
    sf::Font font_;
    bool should_switch_ = false;
    ScreenSelection next_ = kMain;
    int frame_count_ = 0;
    int fps_ = 60;



};

auto load_texture(const std::string &filename) -> sf::Texture;
auto load_font(const std::string &filename) -> sf::Font;


} // namespace all_star::game_mgr