#ifndef SNAKELIB_FRUIT_HPP_
#define SNAKELIB_FRUIT_HPP_

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
	void Reset();
};
}

#endif /* SNAKELIB_FRUIT_HPP_ */
