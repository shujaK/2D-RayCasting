#include "Wall.h"
#include "Colours.h"

Wall::Wall(sf::Vector2f p1, sf::Vector2f p2) : a(p1), b(p2) {}

void Wall::draw(sf::RenderWindow& window)
{
    sf::VertexArray va(sf::PrimitiveType::Lines);
    va.append(sf::Vertex(a, Colours::colour2));
    va.append(sf::Vertex(b, Colours::colour2));
    window.draw(va);
}
