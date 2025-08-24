#include <iostream>
#include <SFML/Graphics.hpp>
#include <limits>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Colours.h"
#include "Wall.h"
#include "Ray.h"
#include "Eye.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "2D Raycast (Press D to clear walls)");
    window.setFramerateLimit(144);
    window.setMouseCursorVisible(false);

    // create eye with 2 degree ray spacing
    Eye eye({ 100.0f, 100.0f }, 2.0f);

    // initialize walls container with one default wall
    std::vector<Wall> walls;
    walls.emplace_back(Wall({ 400.0f, 200.0f }, { 400.0f, 600.0f }));

    // vertex array for drawing new walls
    sf::VertexArray newWallVa(sf::PrimitiveType::Lines);
    newWallVa.resize(2);

    // wall creation variables
    sf::Vector2f newWallP1, newWallP2;
    bool drawRays = true;
    sf::Clock deltaClock;
    
    while (window.isOpen())
    {
        auto mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = { (float)mousePosI.x, (float)mousePosI.y };

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                {
                    walls.clear();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                newWallP1 = mousePosF;
                newWallVa[0] = sf::Vertex(mousePosF, Colours::colour2);
                drawRays = false;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                newWallP2 = mousePosF;
                if (newWallP1 != newWallP2) walls.emplace_back(Wall(newWallP1, newWallP2));
                drawRays = true;
            }
        }

        window.clear(Colours::colour1);

        // draw preview of new wall while dragging
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            newWallVa[1] = sf::Vertex(mousePosF, Colours::colour2);
            window.draw(newWallVa);
        }

        // draw all existing walls
        for (auto& w : walls)
        {
            w.draw(window);
        }

        // update eye position and calculate ray intersections
        eye.move(mousePosF);
        eye.intersectRays(walls);
        if (drawRays) eye.draw(window);

        window.display();
    }
}
