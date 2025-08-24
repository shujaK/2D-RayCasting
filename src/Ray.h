#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"

class Ray
{
public:
    sf::Vector2f pos, dir;
    sf::Color col;          // ray color
    float angle;            // angle in degrees
    float distSq;           // squared distance to hit point
    
    bool hits;              // whether ray hits a wall
    sf::Vector2f hitPos;    // position where ray hits wall

    Ray(sf::Vector2f p, float a);
    sf::Vector2f intersect(Wall w);
};
