#pragma once
#include "MoveableBlock.hpp"
#include "../TileMap/TileMap.hpp"

namespace Snake
{
class Fruit : public MoveableBlock
{
public:
    /* Constructors */
    Fruit(TM::Map&, sf::Color);

    /* Member Functions */
    void reset();
};
}
