#ifndef SNAKELIB_FRUIT_FRUIT_HPP_
#define SNAKELIB_FRUIT_FRUIT_HPP_

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
	void ResetTilePos();
};
}

#endif /* SNAKELIB_FRUIT_FRUIT_HPP_ */
