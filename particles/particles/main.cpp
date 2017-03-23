
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include <algorithm>
#include <iostream>
#include "Vector2.hpp"
#include "MaterialPoint.hpp"
#include <vector>


const int VELOCITY = 100;
const int RADUIS = 10;


std::vector<sf::Color> colors = {
    sf::Color::Blue,
    sf::Color::Black,
    sf::Color::Yellow,
    sf::Color::Green,
    sf::Color::Red
};


class Ball: public MaterialPoint
{
public:
    float radius;
    int type;
};

struct GameField
{
    
    sf::Vector2i size;
    std::vector <Ball> balls;
    void update(float dt)
    {
        //Change the direction of the balls if they face the wall
        
        for (auto& b : balls)
        {
            if (b.position.x + 2 * b.radius >= size.x)
            {
                b.velocity = Vector2(b.velocity.x * -1, b.velocity.y);
            }
            if (b.position.x <= 0)
            {
                b.velocity = Vector2(b.velocity.x * -1, b.velocity.y);
            }
            if (b.position.y + 2 * b.radius >= size.y)
            {
                b.velocity = Vector2(b.velocity.x, b.velocity.y * -1);
            }
            if (b.position.y <= 0)
            {
                b.velocity = Vector2(b.velocity.x, b.velocity.y * -1);
            }
            b.updatePosition(dt);
        }
        
        for (int i = 0; i < balls.size(); i++)
        {
            for (int j = i + 1; j < balls.size(); j++)
            {
                
                Vector2 d = balls[j].position - balls[i].position;
                Vector2 dv = balls[j].velocity - balls[i].velocity;
                
                //collisions handling
                if ( (d.len() <= balls[i].radius + balls[j].radius) && (dv * d < 0) )
                {
                    float m = 1 / balls[j].mass + 1 / balls[i].mass;
                    Vector2 dp = 2 * (dv / m) * d.norm() * d.norm();
                    
                    balls[i].velocity += dp / balls[i].mass;
                    balls[j].velocity -= dp / balls[j].mass;
                }
            }
            balls[i].updatePosition(dt);
        }
    }
};

int main(int, char const**)
{
    float prevTime;
    GameField gameField;
    gameField.size = sf::Vector2i(800, 600);
    sf::CircleShape circle(50);
    sf::Clock clock;
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        sf::Time time = clock.getElapsedTime();
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                Ball ball;
                ball.position = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                ball.velocity = Vector2(rand() % VELOCITY, rand() % VELOCITY).rotate(rand() % 360);
                ball.type = rand() % 5;
                ball.radius = ball.type * RADUIS;
                ball.mass = ball.radius;
                gameField.balls.push_back(ball);
            }
        }
        gameField.update(time.asSeconds() - prevTime);
        prevTime = time.asSeconds();
        for (const auto& b : gameField.balls)
        {
            circle.setRadius(b.radius);
            circle.setPosition(b.position.x, b.position.y);
            circle.setFillColor(colors[b.type]);
            
            window.draw(circle);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
