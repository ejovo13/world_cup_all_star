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
    _score = 0;
    _restart_button = configure_button(sf::Color::White, sf::Color::Red, 2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    _restart_text = configure_button_text(_restart_button, "RESTART",sf::Color::Red,"arial.ttf");
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
    window.clear();
    window.draw(_restart_button);
    window.draw(_restart_text);
    window.display();
}

bool Game::game_over_click(sf::RenderWindow& windows, sf::Event event){
    return false;
}

sf::RectangleShape configure_button(sf::Color fill_color, sf::Color outline_color, float thickness, int x, int y){
    sf::RectangleShape button;
    button.setFillColor(fill_color);
    button.setOutlineColor(outline_color);
    button.setOutlineThickness(thickness);
    button.setPosition(x,y);
    button.setSize(sf::Vector2f(300,150));
    return button;
}

sf::Text configure_button_text(sf::RectangleShape& button, std::string mytext,sf::Color color, std::string font_file){
    sf::Text text;
    text.setString(mytext);
    text.setCharacterSize(BUTTON_CHARACTER_SIZE);
    text.setFillColor(color);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw std::invalid_argument("Bad font");
    }
    text.setFont(font);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f((button.getPosition().x + button.getSize().x) / 2, (button.getPosition().y + button.getSize().y)/2));
    return text;
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