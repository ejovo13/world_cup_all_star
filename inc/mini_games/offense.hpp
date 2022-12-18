#pragma once
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <random>
#include <cstdlib>
#include <ctime>

#define WINDOW_HEIGHT 800 
#define WINDOW_WIDTH 800
#define RADIUS 40
#define GRAVITY 0.06 //To make the balls fall
#define DEFAULT_BALL_SPEED 6
#define BUTTON_CHARACTER_SIZE 30

namespace world_cup::mini_games {

int random_ball_spawn_x(); // Get a random x coordinate for the next ball spawn
int random_ball_spawn_y(); // Get a random y coordinate for the next ball spawn
sf::RectangleShape configure_button(sf::Color fill_color, sf::Color outline_color, float thickness, int x, int y);//configure a new button
sf::Text configure_button_text(sf::RectangleShape& button, std::string mytext, sf::Color color, sf::Font& font);
sf::Text configure_text(std::string mytext, sf::Color color, sf::Font& font, int x, int y);

class Ball{
    private :
    int _x; // X coordinate
    int _y; // Y coordinate
    sf::CircleShape _ball; // SFML Object to interact with
    float _y_Speed;// to move the ball on the Y axis
    float _x_Speed;// to move the ball on the X axis
    static int _radius; // Ball Radius
    public :
    Ball(int x, int y, sf::Texture& texture); //Constructor with given coordinates and the ball texture
    Ball(); //Random constructor for next balls
    void update(); //Update ball position within time
    void update_touch(sf::Event event); // Update ball position within user click/
    int getX(); //get X coordinate
    int getY(); //get Y coordinate
    sf::CircleShape& getBall(); //Get the sf::CircleShape Object of the Ball
    float getYSpeed(); //Get the y_Speed of the ball
};

class Game{
    private :
    sf::Texture _texture; //for the all balls graphics
    std::vector<Ball> _listball; //Store every balls that are in the game
    int _score;
    sf::Font _font;
    sf::RectangleShape _restart_button;
    sf::Text _restart_text;
    public:
    Game(sf::Texture& texture, sf::Font& font); // Create the Game with one ball
    void update_game(); //Update all balls positions
    void update_balls(sf::Event event); //Update balls speed if there's a mouse click
    bool checklose(); //Check that there's no ball on the ground
    void display(sf::RenderWindow& window, sf::Sprite&); // To display everything in real time
    void game_over(sf::RenderWindow& window, sf::Sprite& background); //The game over screen with buttons
    bool game_over_click(sf::RenderWindow& window, sf::Event event, sf::Sprite& background); //Same with users interaction
};
}