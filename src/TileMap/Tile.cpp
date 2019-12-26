#include "Tile.hpp"

namespace TM
{
Tile::Tile()
    : Tile(0,0)
{}

Tile::Tile(int x, int y)
    : x(x), y(y)
{}

template<typename T>
Tile::Tile(const sf::Vector2<T>& pos)
    : Tile((static_cast<int>(pos.x)), static_cast<int>(pos.y))
{}

sf::Vector2i Tile::getPos() const
{
    return sf::Vector2i(x, y);
}

bool Tile::operator==(const Tile& a) const
{
    return x == a.x and y == a.y;
}

bool Tile::operator!=(const Tile& a) const
{
    return x != a.x or y != a.y;
}

Tile Tile::operator+(const Tile& a) const
{
    return Tile(x + a.x, x + a.x);
}

Tile Tile::operator-(const Tile& a) const
{
    return Tile(x - a.x, x - a.x);
}

Tile& Tile::operator=(const Tile& a)
{
    x = a.x;
    y = a.y;
    return *this;
}

Tile& Tile::operator+=(const Tile& a)
{
    x += a.x;
    y += a.y;
    return *this;
}

Tile& Tile::operator-=(const Tile& a)
{
    x -= a.x;
    y -= a.y;
    return *this;
}
}
