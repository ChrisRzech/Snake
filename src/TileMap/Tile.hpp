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
    template<typename T>
    Tile(const sf::Vector2<T>& pos);

    /* Getters */
    sf::Vector2i getPos() const;

    /* Operator overloads */
    bool  operator==(const Tile&) const;
    bool  operator!=(const Tile&) const;
    Tile  operator+ (const Tile&) const;
    Tile  operator- (const Tile&) const;
    Tile& operator= (const Tile&);
    Tile& operator+=(const Tile&);
    Tile& operator-=(const Tile&);

    /* Public data */
    int x;
    int y;
};
}
