#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define PI_180 M_PI / 180

class Ray
{
public:
    sf::Vector2f pos, dir;
    sf::Color col;          // ray color
    float angle;            // angle in radians
    float distSq;           // squared distance to hit point
    
    bool hits;              // whether ray hits a wall
    sf::Vector2f hitPos;    // position where ray hits wall

    Ray(sf::Vector2f p, float a);
    Ray(sf::Vector2f p);
    sf::Vector2f intersect(Wall w);
    bool Ray::operator<(const Ray& r) const
    {
        return (angle < r.angle);
    }
};
