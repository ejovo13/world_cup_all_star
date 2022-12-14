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
#define RADIUS 35
#define GRAVITY 0.06 //To make the balls fall

namespace world_cup::mini_games {

int random_ball_spawn_x(); // Get a random x coordinate for the next ball spawn
int random_ball_spawn_y(); // Get a random y coordinate for the next ball spawn

class Ball{
    private :
    int _x; // X coordinate
    int _y; // Y coordinate
    sf::CircleShape _ball; // SFML Object to interact with
    float _y_Speed;// to move the ball on the Y axis
    float _x_Speed;// to move the ball on the X axis
    static int _radius; // Ball Radius
    public :
    Ball(int x, int y, sf::Texture& texture); //Constructor with given coordinates
    Ball(); //Random constructor for next balls
    void update(); //Update ball position within time
    void update_touch(); // Update ball position within user click/
    int getX(); //get X coordinate
    int getY(); //get Y coordinate
    sf::CircleShape& getBall(); //Get the sf::CircleShape Object of the Ball
    float getYSpeed(); //Get the y_Speed of the ball
};

class Game{
    private :
    sf::Texture _texture; //for the ball graphics
    std::vector<Ball> _listball; //Store every balls that are in the game
    public:
    Game(sf::Texture& texture); // Create the Game with one ball
    void update_game(); //Update all balls positions
    void update_balls(sf::Event event); //Update balls speed if there's a mouse click
    bool checklose(); //Check that there's no ball on the ground
    void display(sf::RenderWindow& window); // To display everything in real time
};
}