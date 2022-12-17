#include "mini_games/offense.hpp"

namespace world_cup::mini_games {

int Ball::_radius = RADIUS;

Ball::Ball(int x, int y, sf::Texture& texture) : _x(x), _y(y), _y_Speed(0), _x_Speed(0)
{
    _ball.setRadius(_radius);
    _ball.setOrigin(_radius,_radius);
    _ball.setPosition(_x, _y);
    _ball.setFillColor(sf::Color::White);
    _ball.setTexture(&texture);
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
sf::CircleShape& Ball::getBall(){return _ball;}
float Ball::getYSpeed(){return _y_Speed;}

void Ball::update(){
    _y_Speed+=GRAVITY;
    if (_y + _y_Speed < 0){

        _y_Speed = - 2 * _y_Speed / 3;
    }
    _y += _y_Speed;
    _x+= _x_Speed;
    _ball.setPosition(_x, _y);
}

void Ball::update_touch(){
    _y_Speed=-6;
}

Game::Game(sf::Texture& texture) : _texture(texture){
    _listball.push_back(Ball(WINDOW_WIDTH/2, (int)WINDOW_HEIGHT/3, _texture));
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
             Ball b(random_ball_spawn_x(),random_ball_spawn_y(), _texture);
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

void Game::display(sf::RenderWindow& window){
    window.clear();
    for (auto &i : _listball){
        window.draw(i.getBall());
    }
    window.display();
}

// Randoms functions for balls spawns

int random_ball_spawn_x(){
    int min = 0;
    int max = WINDOW_WIDTH + RADIUS;
    return min + (int)((float)rand()*(max-min+1)/(RAND_MAX -1));
}
int random_ball_spawn_y(){
    int max = RADIUS;
    int min = WINDOW_HEIGHT - 6*RADIUS;
    return min + (int)((float)rand()*(max-min+1)/(RAND_MAX -1));
}
}