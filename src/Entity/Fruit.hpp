#pragma once
#include "MoveableBlock.hpp"
#include "../TileMap/TileMap.hpp"

namespace Entity
{
class Fruit : public MoveableBlock
{
public:
    /* Constructors */
    Fruit(const TM::Map&, const std::vector<TM::Tile>& possiblePositions, const sf::Color&);

    /* Updates */
    void reset();
    
    /* Public data */
    std::vector<TM::Tile> possiblePositions;
};
}
