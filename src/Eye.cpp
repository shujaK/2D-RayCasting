#include "Eye.h"
#include <cmath>
#include "Colours.h"

Eye::Eye(sf::Vector2f p, float da) : pos(p), dAngle(da)
{
    c = sf::CircleShape(5.0f, 8);
    c.setOrigin({ 2.5f, 2.5f });
    c.setFillColor(Colours::colour2);
    va = sf::VertexArray(sf::PrimitiveType::Lines);

    setRays();
}

void Eye::setRays()
{
    rays.clear();
    // create rays in a full 360 degree circle
    for (float i = 0; i < 360; i += dAngle)
    {
        rays.emplace_back(Ray(pos, i));
    }
}

void Eye::move(sf::Vector2f p)
{
    pos = p;
    setRays();
}

void Eye::intersectRays(std::vector<Wall>& walls)
{
    // check each ray against all walls for intersections
    for (auto& r : rays)
    {
        for (auto& w : walls)
        {
            r.intersect(w);
        }
    }
}

void Eye::draw(sf::RenderWindow& window)
{
    c.setPosition(pos);
    va.clear();

    // draw each ray from eye position
    for (auto& r : rays)
    {
        va.append(sf::Vertex(pos, r.col));
        if (r.hits)
            va.append(sf::Vertex(r.hitPos, r.col));        // draw to hit point
        else
            va.append(sf::Vertex((r.pos + (r.dir * 1000.0f)), r.col)); // draw extended ray
    }

    window.draw(va);
    window.draw(c);
}
