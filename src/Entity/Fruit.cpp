#include "Fruit.hpp"

namespace Entity
{
Fruit::Fruit(const TM::Map& map, const std::vector<TM::Tile>& possiblePositions, const sf::Color& color)
    : MoveableBlock(map), possiblePositions(possiblePositions)
{
    reset();
    setColor(color);
}

void Fruit::reset()
{
    if(possiblePositions.size() == 0)
        throw std::invalid_argument("Possible positions for fruit is zero");\
    
    pos = possiblePositions[rand() % possiblePositions.size()];
}
}
