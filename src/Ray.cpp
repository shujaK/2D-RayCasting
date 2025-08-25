#include "Ray.h"
#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Colours.h"
#define INF_VEC {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()}

Ray::Ray(sf::Vector2f p, float a) : pos(p), angle(a) 
{
    dir.x = std::cos(a);
    dir.y = std::sin(a);

    col = Colours::colour2;
    hits = false;
    hitPos = INF_VEC;
    distSq = std::numeric_limits<float>::infinity();
}

Ray::Ray(sf::Vector2f p) : pos(p)
{
    col = Colours::colour3;
}

sf::Vector2f Ray::intersect(Wall w)
{
    // direction vector
    sf::Vector2f wall_dir = w.b - w.a;
    
    // determinant for line intersection calculation
    float denom = wall_dir.x * (-dir.y) - wall_dir.y * (-dir.x);
    
    // check if lines are parallel
    if (std::abs(denom) < 1e-6f)
    {
        return INF_VEC;
    }
    
    // vector from wall start to ray origin
    sf::Vector2f to_ray = pos - w.a;
    
    // calculate intersection parameters
    float t = (to_ray.x * (-dir.y) - to_ray.y * (-dir.x)) / denom;
    float u = -(to_ray.x * wall_dir.y - to_ray.y * wall_dir.x) / denom;
    
    // check if intersection is within wall bounds and ray direction
    if (t >= 0.0f && t <= 1.0f && u > 0.0f) 
    {
        hits = true;
        sf::Vector2f newHitPos = w.a + t * wall_dir;

        // update hit position if this is the closest intersection
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
