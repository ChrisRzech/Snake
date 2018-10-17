#include "Tile.hpp"

namespace TM
{
/* Constructors */
Tile::Tile() : x(0), y(0) {}
Tile::Tile(int xN, int yN) : x(xN), y(yN) {}
Tile::Tile(const sf::Vector2u& pos) : x(pos.x), y(pos.y) {}
Tile::Tile(const sf::Vector2i& pos) : x(pos.x), y(pos.y) {}
Tile::Tile(const sf::Vector2f& pos) : x(pos.x), y(pos.y) {}



/* Getters */
sf::Vector2i Tile::TilePos() const {return {x,y};}



/* Operator Overloads */
bool  Tile::operator==(const Tile& rhs) const {return (x == rhs.x) and (y == rhs.y);}
bool  Tile::operator!=(const Tile& rhs) const {return *this != rhs;}
Tile  Tile::operator+ (const Tile& rhs) const {return {this->x + rhs.x, this->x + rhs.x};}
Tile  Tile::operator- (const Tile& rhs) const {return {this->x - rhs.x, this->x - rhs.x};}
Tile& Tile::operator= (const Tile& rhs)       {this->x  = rhs.x; this->y  = rhs.y; return *this;}
Tile& Tile::operator+=(const Tile& rhs)       {this->x += rhs.x; this->y += rhs.y; return *this;}
Tile& Tile::operator-=(const Tile& rhs)       {this->x -= rhs.x; this->y -= rhs.y; return *this;}
}
