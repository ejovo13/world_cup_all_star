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
    if ((_x + _x_Speed > WINDOW_WIDTH - RADIUS) || (_x + _x_Speed < RADIUS)){
        _x_Speed = -2 * _x_Speed / 3;
    }
    _y += _y_Speed;
    _x+= _x_Speed;
    _ball.setPosition(_x, _y);
}

void Ball::update_touch(sf::Event event){
    _y_Speed=-DEFAULT_BALL_SPEED;
    _x_Speed = DEFAULT_BALL_SPEED * (_x - event.mouseButton.x)/RADIUS;
}

Game::Game(sf::Texture& texture) : _texture(texture), _score(1){
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
            i.update_touch(event);
             Ball b(random_ball_spawn_x(),random_ball_spawn_y(), _texture);
            _listball.push_back(b);
            _score++;
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

void Game::display(sf::RenderWindow& window, sf::Sprite& background){
    window.clear(sf::Color::Blue);
    window.draw(background);
    for (auto &i : _listball){
        window.draw(i.getBall());
    }
    window.display();
}

void Game::game_over(sf::RenderWindow& window){
    sf::RectangleShape button1;
    sf::RectangleShape button2;
}

bool Game::game_over_click(sf::RenderWindow& windows, sf::Event event){

}

sf::RectangleShape configure_button(sf::Color fill_color, sf::Color outline_color, float thickness, int x, int y, std::string text){

}
// Randoms functions for balls spawns

int random_ball_spawn_x(){
    int min = 0;
    int max = WINDOW_WIDTH + RADIUS;
    return min + (int)((float)rand()*(max-min+1)/(RAND_MAX -1));
}
int random_ball_spawn_y(){
    int max = RADIUS;
    int min = WINDOW_HEIGHT - 8*RADIUS;
    return min + (int)((float)rand()*(max-min+1)/(RAND_MAX -1));
}
}