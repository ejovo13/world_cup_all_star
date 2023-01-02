#include "all_star.hpp"

// #include "SFML/Graphics/"

using namespace all_star::game_mgr;
using namespace all_star::mini_games;
using namespace all_star::world_cup;

int main() {

    std::cout << "Defense\n"; 

    Vec<int> v {1, 2, 3};

    std::cout << v << "\n";
    Vec<int> v2 = v + v; 
    auto v3 = v2 + v;
    v3.print();
    v2.print();

    auto vc = v.cross(v3);
    vc.print();

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML window");

    window.setPosition(sf::Vector2i(50, 50));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(30);

    // Let's create a ball
    Ball3D ball (100, 0, 0);

    std::vector<Ball3D> balls;

    balls.push_back(Ball3D(100, 0, 0));
    balls.push_back(Ball3D(200, 30, 0));
    balls[1].set_vel(0, 0, 1);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (auto &b : balls) {
            b.display(window);
            b.update(window);
            b.apply_gravity();
            // std::cerr << b << "\n";
            // b.constrain(window);
        }

        // ball.display(window);
        // ball.apply_force(gravity());
        // ball.update();
        // ball.constrain(window); 
        // window.draw(text);
        // std::cerr << ball << "\n";

        window.display();
    }


    return 0;
}