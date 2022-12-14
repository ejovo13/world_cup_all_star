#include "../../inc/mini_games/offense.hpp"

int Ball::_radius = RADIUS;

Ball::Ball(int x, int y, float gravity) : _x(x), _y(y), _y_Speed(gravity), _x_Speed(0)
{
    _ball.setRadius(_radius);
    _ball.setOrigin(_radius,_radius);
    _ball.setPosition(_x, _y);
    _ball.setFillColor(sf::Color::Red);
}

Ball::Ball(){
    _x = random_ball_spawn_x();
    _y = random_ball_spawn_y();
    _ball.setRadius(_radius);
    _ball.setOrigin(_radius,_radius);
    _ball.setPosition(_x, _y);
}

int Ball::getX(){return _x;}
int Ball::getY(){return _y;}
sf::CircleShape Ball::getBall(){return _ball;}
float Ball::getYSpeed(){return _y_Speed;}

void Ball::update(){
    if (_y + _y_Speed < 0){

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
    _listball.push_back(Ball(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, _gravity));
}

void Game::update_game(){
    for (auto& i : _listball)
    {
        i.update();
    }
}

void Game::update_balls(sf::Event event){
    for (auto& i : _listball){
        if (i.getBall().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)&&(i.getYSpeed()>=0)){
            i.update_touch();
             Ball b(random_ball_spawn_x(),random_ball_spawn_y(),_gravity);
            _listball.push_back(b); 
        }
    }
}

bool Game::checklose(){
    for (auto& i : _listball){
        if (i.getY() > WINDOW_HEIGHT - RADIUS){
            return false;
        }
    }
    return true;
}

void Game::displaythegame(sf::RenderWindow& window){
    window.clear();
    for (auto &i : _listball){
        window.draw(i.getBall());
    }
    window.display();
}

// Randoms functions for balls spawns

int random_ball_spawn_x(){
    int min = WINDOW_WIDTH + RADIUS;
    int max = WINDOW_HEIGHT - RADIUS;
    return min + (int)((float)rand()*(max-min+1)/(RAND_MAX -1));
}
int random_ball_spawn_y(){
    int max = RADIUS;
    int min = WINDOW_HEIGHT - RADIUS;
    return min + (int)((float)rand()*(max-min+1)/(RAND_MAX -1));
}