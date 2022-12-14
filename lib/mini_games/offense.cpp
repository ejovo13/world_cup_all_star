#include "mini_games/offense.hpp"

int Ball::_radius = RADIUS;

Ball::Ball(int x, int y, int gravity) : _x(x), _y(y), _y_Speed(gravity), _x_Speed(0)
{
    _ball.setRadius(_radius);
    _ball.setPosition(_x, _y);
}

Ball::Ball(){
    _x = random_ball_spawn_x();
    _y = random_ball_spawn_y();
    _ball.setRadius(_radius);
    _ball.setPosition(_x, _y);
}

int Ball::getX(){return _x;}
int Ball::getY(){return _y;}

void Ball::update(){
    if (_y + _y_Speed > WINDOW_HEIGHT ){

        _y_Speed = - _y_Speed;
    }
    _y += _y_Speed;
    _x+= _x_Speed;
    _ball.setPosition(_x, _y);
}

void Ball::update_touch(){
    _y_Speed=-GRAVITY;
}

Game::Game(){
    _gravity = GRAVITY;
    _balls.push_back(Ball(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, GRAVITY));
}

void Game::updategame(){
    for (auto& i : _balls)
    {
        i.update();
    }
}

void Game::updategame_touch(sf::Event event){
    
}

bool Game::checklose(){
    for (auto& i : _balls){
        if (i.getY() < RADIUS){
            return false;
        }
    }
    return true;
}

// Randoms functions for balls spawns

int random_ball_spawn_x(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(WINDOW_WIDTH + RADIUS, WINDOW_WIDTH - RADIUS);
}
int random_ball_spawn_y(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1/4 * WINDOW_HEIGHT, WINDOW_HEIGHT - RADIUS);
}