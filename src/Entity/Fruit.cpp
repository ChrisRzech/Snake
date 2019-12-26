#include "Fruit.hpp"

namespace Entity
{
Fruit::Fruit(const TM::Map& map, const sf::Color& color)
    : MoveableBlock(map)
{
    reset();
    setColor(color);
}

void Fruit::reset()
{
    int tileCountX = map->getTileCount().x;
    int tileCountY = map->getTileCount().y;
    pos = TM::Tile(rand() % tileCountX, rand() % tileCountY);
}
}
