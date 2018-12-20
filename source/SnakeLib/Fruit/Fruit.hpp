#pragma once
#include "../MoveableBlock/MoveableBlock.hpp"
#include "../../TileMap/TileMap.hpp"

namespace Snake
{
class Fruit : public MoveableBlock
{
public:
    /* Constructors */
    Fruit(TM::Map&, sf::Color);

    /* Member Functions */
    void resetTilePos();
};
}
