#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
    sf::Vector2f a, b; // start and end points of the wall

    Wall(sf::Vector2f p1, sf::Vector2f p2);
    void draw(sf::RenderWindow& window);
};
