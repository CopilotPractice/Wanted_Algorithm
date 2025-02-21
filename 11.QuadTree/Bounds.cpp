#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{
    if (other.x > MaxX()) return false;

    if (other.MaxX() < x) return false;

    if (other.y > MaxY()) return false;

    if (other.MaxY() < y) return false;
    
    return true;
}
