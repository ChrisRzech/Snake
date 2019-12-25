#pragma once
#include <SFML/System/Vector2.hpp>

namespace TM
{
class Tile
{
public:
    /* Constructors */
    Tile();
    Tile(int x, int y);
    Tile(const sf::Vector2u& pos);
    Tile(const sf::Vector2i& pos);
    Tile(const sf::Vector2f& pos);

    /* Getters */
    sf::Vector2i tilePos() const;

    /* Arithmetic overloads */
    bool  operator==(const Tile&) const;
    bool  operator!=(const Tile&) const;
    Tile  operator+ (const Tile&) const;
    Tile  operator- (const Tile&) const;
    Tile& operator= (const Tile&);
    Tile& operator+=(const Tile&);
    Tile& operator-=(const Tile&);

private:
    int m_x;
    int m_y;
};
}
