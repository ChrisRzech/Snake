#include "Fruit.hpp"

namespace Snake
{
/* Constructors */
Fruit::Fruit(TM::Map& map, sf::Color color)
    : MoveableBlock(map)
{
    resetTilePos();
    setColor(color);
}

/* Member Functions */
void Fruit::resetTilePos()
{
    int tileCountX = getMap()->getTileCount().x;
    int tileCountY = getMap()->getTileCount().y;
    TM::Tile tile(rand() % tileCountX, rand() % tileCountY);
    setTile(tile);
}
}
