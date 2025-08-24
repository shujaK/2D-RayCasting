#include <iostream>
#include <SFML/Graphics.hpp>
#include <limits>
#include <vector>
#define INF_VEC {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()}
#define _USE_MATH_DEFINES
#include <math.h>
#define PI_180 M_PI / 180

sf::Color colour1(38, 39, 48, 255);
sf::Color colour2(239, 240, 209, 255);
sf::Color colour3(211, 63, 73, 255);

class Wall
{
public:
    sf::Vector2f a, b;

    Wall (sf::Vector2f p1, sf::Vector2f p2) : a(p1), b(p2) {}

    void draw(sf::RenderWindow& window)
    {
        sf::VertexArray va(sf::PrimitiveType::Lines);

        va.append(sf::Vertex(a, colour2));
        va.append(sf::Vertex(b, colour2));

        window.draw(va);
    }
};

class Ray
{
public:
    sf::Vector2f pos, dir;
    sf::Color col;
    float angle;
    float distSq;

    bool hits;
    sf::Vector2f hitPos;

    Ray(sf::Vector2f p, float a) : pos(p), angle(a) 
    {
        dir.x = std::cos(PI_180 * a);
        dir.y = std::sin(PI_180 * a);

        col = colour2;
        hits = false;
        hitPos = INF_VEC;
        distSq = std::numeric_limits<float>::infinity();
    }

    sf::Vector2f intersect(Wall w)
    {
        sf::Vector2f wall_dir = w.b - w.a;
        
        float denom = wall_dir.x * (-dir.y) - wall_dir.y * (-dir.x);
        
        if (std::abs(denom) < 1e-6f)
        {
            return INF_VEC;
        }
        
        sf::Vector2f to_ray = pos - w.a;
        
        float t = (to_ray.x * (-dir.y) - to_ray.y * (-dir.x)) / denom;
        float u = -(to_ray.x * wall_dir.y - to_ray.y * wall_dir.x) / denom;
        
        if (t >= 0.0f && t <= 1.0f && u > 0.0f) 
        {
            hits = true;
            sf::Vector2f newHitPos = w.a + t * wall_dir;

            float newDistSq = (newHitPos.x - pos.x) * (newHitPos.x - pos.x) + (newHitPos.y - pos.y) * (newHitPos.y - pos.y);
            if (newDistSq < distSq)
            {
                distSq = newDistSq;
                hitPos = newHitPos;
            }

            return hitPos;
        }
        else
        {
            return INF_VEC;
        }
    }
};


class Eye
{
public:
    sf::Vector2f pos;
    std::vector<Ray> rays;
    float dAngle;

    sf::CircleShape c;
    sf::VertexArray va;

    Eye(sf::Vector2f p, float da) : pos(p), dAngle (da)
    {
        c = sf::CircleShape(5.0f, 8);
        c.setOrigin({ 2.5f, 2.5f });
        c.setFillColor(colour2);
        va = sf::VertexArray(sf::PrimitiveType::Lines);

        setRays();
    }

    void setRays()
    {
        rays.clear();
        for (float i = 0; i < 360; i+= dAngle)
        {
            rays.emplace_back(Ray(pos, i));
        }
    }

    void move(sf::Vector2f p)
    {
        pos = p;
        setRays();
    }

    void intersectRays(std::vector<Wall> &walls)
    {
        for (auto& r : rays)
        {
            for (auto& w : walls)
            {
                r.intersect(w);
            }
        }
    }

    void draw(sf::RenderWindow &window)
    {
        c.setPosition(pos);
        va.clear();

        for (auto& r : rays)
        {
            va.append(sf::Vertex(pos, r.col));
            if (r.hits)
                va.append(sf::Vertex(r.hitPos, r.col));
            else
                va.append(sf::Vertex((r.pos + (r.dir * 1000.0f)), r.col));
        }

        window.draw(va);
        window.draw(c);
    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "2D Raycast (Press D to clear walls)");
    window.setFramerateLimit(144);
    window.setMouseCursorVisible(false);

    Eye eye({ 100.0f, 100.0f }, 5.0f);

    std::vector<Wall> walls;
    walls.emplace_back(Wall({ 400.0f, 200.0f }, { 400.0f, 600.0f }));

    sf::VertexArray newWallVa(sf::PrimitiveType::Lines);
    newWallVa.resize(2);

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
                newWallVa[0] = sf::Vertex(mousePosF, colour2);
                drawRays = false;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                newWallP2 = mousePosF;
                if (newWallP1 != newWallP2 ) walls.emplace_back(Wall(newWallP1, newWallP2));
                drawRays = true;
            }
        }

        window.clear(colour1);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            newWallVa[1] = sf::Vertex(mousePosF, colour2);
            window.draw(newWallVa);
        }

        for (auto& w : walls)
        {
            w.draw(window);
        }

        eye.move(mousePosF);
        eye.intersectRays(walls);
        if (drawRays) eye.draw(window);

        window.display();
    }
}
