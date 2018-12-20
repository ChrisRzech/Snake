#include "Tile.hpp"

namespace TM
{
/* Constructors */
Tile::Tile()
    : m_x(0), m_y(0)
{}

Tile::Tile(int x, int y)
    : m_x(x), m_y(y)
{}

Tile::Tile(const sf::Vector2u& pos)
    : m_x(pos.x), m_y(pos.y)
{}

Tile::Tile(const sf::Vector2i& pos)
    : m_x(pos.x), m_y(pos.y)
{}
Tile::Tile(const sf::Vector2f& pos)
    : m_x(pos.x), m_y(pos.y)
{}

/* Getters */
sf::Vector2i Tile::tilePos() const
{
    return sf::Vector2i(m_x, m_y);
}

/* Arithmetic overloads */
bool Tile::operator==(const Tile& rhs) const
{
    return m_x == rhs.m_x and m_y == rhs.m_y;
}

bool Tile::operator!=(const Tile& rhs) const
{
    return m_x != rhs.m_x or m_y != rhs.m_y;
}

Tile Tile::operator+(const Tile& rhs) const
{
    return Tile(m_x + rhs.m_x, m_x + rhs.m_x);
}

Tile Tile::operator-(const Tile& rhs) const
{
    return Tile(m_x - rhs.m_x, m_x - rhs.m_x);
}

Tile& Tile::operator=(const Tile& rhs)
{
    m_x = rhs.m_x;
    m_y = rhs.m_y;
    return *this;
}

Tile& Tile::operator+=(const Tile& rhs)
{
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    return *this;
}

Tile& Tile::operator-=(const Tile& rhs)
{
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    return *this;
}
}
