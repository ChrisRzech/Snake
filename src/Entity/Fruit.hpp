#pragma once
#include "MoveableBlock.hpp"
#include "../TileMap/TileMap.hpp"

namespace Entity
{
class Fruit : public MoveableBlock
{
public:
    /* Constructors */
    Fruit(const TM::Map&, const sf::Color&);

    /* Updates */
    void reset();
};
}
