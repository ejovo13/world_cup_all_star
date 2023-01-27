/**========================================================================
 * ?                          defense.hpp
 * @brief   : Defense of incoming 3d projectiles
 * @details : 
 * @author  : Evan Voyles
 * @email   : ejovo13@yahoo.com
 * @date    : 2022-12-17
 *========================================================================**/
#pragma once

#include "mini_games/offense.hpp"
#include "game_mgr/game_mgr.hpp"

// #include "mini_games/defense.hpp"
// #include <iostream>

namespace all_star::mini_games {

// class 
template <class T>
struct Vec {

    Vec(T __x, T __y, T __z) : x(__x), y(__y), z(__z) {}
    T x, y, z;

    Vec& print() {
        std::cout << *this << "\n";
        return *this;
    } 

    const Vec& print() const {
        std::cout << *this << "\n";
        return *this;
    } 

    Vec cross(const Vec &rhs) {
        auto new_x = y * rhs.z - z * rhs.y;
        auto new_y = z * rhs.x - x * rhs.z;
        auto new_z = x * rhs.y - y * rhs.x;
        Vec out {new_x, new_y, new_z};
        return out;
    }

    static Vec zero() {
        Vec z {0, 0, 0};
        return z;
    }

    Vec& operator+=(const Vec<T> &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }


};

template <class T>
Vec<T> operator+(const Vec<T> &lhs, const Vec<T> &rhs) {
    Vec out (lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    return out;
}

template <class T>
Vec<T> operator-(const Vec<T> &lhs, const Vec<T> &rhs) {
    Vec out (lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    return out;
}

template <class T>
std::ostream& operator<<(std::ostream &os, const Vec<T>& vec) {
    os << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
    return os;
}


// extern const Vec<float> k_gravity;
Vec<float> gravity();

// Now with a simple 3d vector in place we can create a physics engine

class Ball3D {


public:

    const static int s_center_x_ = 0;
    const static int s_center_y_ = 0;
    
    // Choose an initial position for the ball
    Ball3D(float x, float y, float z) 
        : pos_(x, y, z)
        , vel_{0, 0, 0}
        , acc_{0, 0, 0} 
    {
        circle_.setFillColor(sf::Color::White);
        circle_.setPosition(pos_.x + s_center_x_, pos_.y + s_center_y_);
        circle_.setRadius(10);

        const static int size_0m = 10;
        // circle_.setPosition(pos_)
    }

    Ball3D(Vec<float> pos, Vec<float> vel, Vec<float> acc) 
        : pos_{pos}
        , vel_{vel}
        , acc_{acc}
    {
        circle_.setFillColor(sf::Color::White);
        update_pos();
    }

    auto update(sf::RenderWindow &window) -> Ball3D& {
        constrain(window);
        pos_ += vel_;
        vel_ += acc_;
        acc_ = Vec<float>::zero();

        update_pos();
        circle_.setRadius(10 * (1 + pos_.z * 0.05));

        return *this;
    }

    void set_vel(float x, float y, float z) {
        vel_.x = x;
        vel_.y = y;
        vel_.z = z;
    }

    auto next_x () const -> float {
        return pos_.x + s_center_x_ + vel_.x + circle_.getRadius();
    }

    auto next_y () const -> float {
        return pos_.y + s_center_y_ + vel_.y + circle_.getRadius();
    }
    
    // Make sure the ball doesn't go out of bounds of the window
    auto constrain(sf::RenderWindow &window) -> void {
        auto size = window.getSize();

        // don't let the ball leave the bounds
        if (next_x() >= size.x) pos_.x = size.x - s_center_x_;
        if (next_x() <= 0) {
            pos_.x = -s_center_x_;
            vel_ = Vec<float>::zero();
            acc_ = Vec<float>::zero();
            // acc_ = 
        }
        if (next_y() >= size.y) {
            pos_.y = size.y - s_center_y_ - circle_.getRadius();
            // vel_ = Vec<float>::zero();
            vel_.y = -0.80 * vel_.y;
            acc_ = Vec<float>::zero();
        }
        // if (pos_.y + s_center_y_ > size.y) pos_.y = 0;
        // if (pos_.y + s_center_y_ > size.y) pos_.y = size.y - s_center_y_;
        if (next_y() <= 0) {
            pos_.y = -s_center_y_ - circle_.getRadius();
            vel_ = Vec<float>::zero();
            acc_ = Vec<float>::zero();
        }

    }

    auto update_pos() -> void {
        circle_.setPosition(pos_.x + s_center_x_, pos_.y + s_center_y_);
    }

    auto apply_force(const Vec<float> &force) -> Ball3D& {
        acc_ += force;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Ball3D &ball) {
        os << "pos: " << ball.pos_;
        return os;
    }
    auto apply_gravity() -> Ball3D& {
        acc_ += all_star::mini_games::gravity(); 
        return *this;
    }

    auto display(sf::RenderWindow &window) {
        // Draw a white ball
        window.draw(circle_);
    }

private:

    Vec<float> pos_;
    Vec<float> vel_;
    Vec<float> acc_;
    sf::CircleShape circle_;

};




} // all_star::mini_games