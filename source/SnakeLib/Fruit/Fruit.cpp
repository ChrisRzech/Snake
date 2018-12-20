#include "Fruit.hpp"

namespace Snake
{
/* Constructors */
Fruit::Fruit(TM::Map& map, sf::Color color)
    : MoveableBlock(map)
{
    reset();
    setColor(color);
}

/* Member Functions */
void Fruit::reset()
{
    int tileCountX = getMap()->getTileCount().x;
    int tileCountY = getMap()->getTileCount().y;
    TM::Tile tile(rand() % tileCountX, rand() % tileCountY);
    setTile(tile);
}
}
