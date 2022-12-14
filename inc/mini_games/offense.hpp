#pragma once
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <random>

#define WINDOW_HEIGHT 800 
#define WINDOW_WIDTH 600
#define RADIUS 30
#define GRAVITY -40 //To make the balls fall

int random_ball_spawn_x(); // Get a random x coordinate for the next ball spawn
int random_ball_spawn_y(); // Get a random y coordinate for the next ball spawn

class Ball{
    private :
    int _x; // X coordinate
    int _y; // Y coordinate
    sf::CircleShape _ball; // SFML Object to interact with
    int _y_Speed;// to move the ball on the Y axis
    int _x_Speed;// to move the ball on the X axis
    static int _radius; // Ball Radius
    public :
    Ball(int x, int y, int gravity); //Constructor with given coordinates
    Ball(); //Random constructor for next balls
    void update(); //Update ball position within time
    void update_touch(); // Update ball position within user click/
    int getX(); //get X coordinate
    int getY(); //get Y coordinate
};

class Game{
    private :
    std::vector<Ball> _balls; //Store every balls that are in the game
    int _gravity; //To update balls positions
    public:
    Game(); // Create the Game with one ball
    void updategame(); //Update all ball positions
    void updategame_touch(sf::Event event); //Update the ball touched by the user
    bool checklose(); //Vérifie qu'aucune balle ne touche le sol
};