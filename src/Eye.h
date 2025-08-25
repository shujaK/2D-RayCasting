#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ray.h"
#include "Wall.h"
#include "Colours.h"
#include <algorithm>

// eye class that casts multiple rays and tracks intersections
class Eye
{
public:
    sf::Vector2f pos;           // position of the eye
    std::vector<Ray> rays;      // rays that go to the edge of the screen
    std::vector<Ray> CornerRays;// rays that hit wall corners
    float dAngle;               // angle increment between rays
    
    sf::CircleShape c;          // visual representation of the eye
    sf::VertexArray va;         // vertex array for drawing rays

    Eye(sf::Vector2f p, float da);
    void setRays();
    void setRaysSmooth(std::vector<Wall>& walls);
    void move(sf::Vector2f p, std::vector<Wall>& walls);
    void intersectRays(std::vector<Wall>& walls);
    void draw(sf::RenderWindow& window);
    void drawSmooth(sf::RenderWindow& window);
};
