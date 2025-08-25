#include "Eye.h"
#include <cmath>
#include "Colours.h"

Eye::Eye(sf::Vector2f p, float da) : pos(p), dAngle(da)
{
    c = sf::CircleShape(5.0f, 8);
    c.setOrigin({ 2.5f, 2.5f });
    c.setFillColor(Colours::colour2);
    va = sf::VertexArray(sf::PrimitiveType::Lines);

    // setRays();
}

void Eye::setRaysSmooth(std::vector<Wall>& walls)
{
    CornerRays.clear();
    rays.clear();
    for (auto& w : walls)
    {
        CornerRays.emplace_back(Ray(w.a));
        CornerRays.emplace_back(Ray(w.b));

        // Generate grazing rays around each corner
        sf::Vector2f dA = w.a - pos;
        float angle_a = std::atan2(dA.y, dA.x);
        rays.emplace_back(Ray(pos, angle_a + 0.001f));  // Slightly past corner
        rays.emplace_back(Ray(pos, angle_a - 0.001f));  // Slightly before corner

        sf::Vector2f dB = w.b - pos;
        float angle_b = std::atan2(dB.y, dB.x);
        rays.emplace_back(Ray(pos, angle_b + 0.001f));
        rays.emplace_back(Ray(pos, angle_b - 0.001f));
    }
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

void Eye::move(sf::Vector2f p, std::vector<Wall>& walls)
{
    pos = p;
    setRaysSmooth(walls);
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

void Eye::drawSmooth(sf::RenderWindow& window)
{
    c.setPosition(pos);
    va.clear();

    // draw each ray from eye position
    for (auto& r : CornerRays)
    {
        va.append(sf::Vertex(pos, r.col));
        va.append(sf::Vertex(r.pos, r.col));

    }

    for (auto& r : rays)
    {
        va.append(sf::Vertex(pos, r.col));
        if (r.hits)
            va.append(sf::Vertex(r.hitPos, r.col));        // draw to hit point
        else
            va.append(sf::Vertex((r.pos + (r.dir * 1000.0f)), r.col)); // draw miss ray (not used since we have a bounding box now)
    }

    sf::VertexArray lightVa(sf::PrimitiveType::TriangleFan);
    std::sort(rays.begin(), rays.end()); // sort rays by angle so we can make a clockwise polygon

    lightVa.append(sf::Vertex(pos, Colours::colour2)); // first point should be loc of eye
    for (auto& r : rays)
    {
        lightVa.append(sf::Vertex(r.hitPos, Colours::colour2));
    }
    lightVa.append(sf::Vertex(rays[0].hitPos, Colours::colour2)); // include first element to complete last tri


    window.draw(lightVa);
    window.draw(c);
}
