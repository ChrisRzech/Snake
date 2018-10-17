#ifndef SNAKELIB_SNAKE_HPP_
#define SNAKELIB_SNAKE_HPP_

#include <vector>
#include <algorithm>
#include "MoveableBlock.hpp"

namespace Snake
{
class Snake
{
public:
	/* Constructors */
	Snake(TM::Map&, sf::Color, sf::Clock&, sf::Time millisecondPerTick);


	/* Getters */
	unsigned int GetLength()   const;
	TM::Tile     GetHeadTile() const;


	/* Setters */
	void SetDirection(Direction);
	void SetHeadPos(TM::Tile);
	void SetColor(sf::Color);


	/* Member Functions */
	bool CheckTailCollision() const;
	void IncreaseTailBy(int count, sf::Color = sf::Color::Green);
	void Update();
	void Draw(sf::RenderWindow&);



private:
	/* Tile Mapping */
	TM::Map* map;


	/* Snake Data */
	bool headCollision;
	std::vector<MoveableBlock> snake;
	Direction userDir;


	/* Clock & Ticks */
	sf::Clock* clock;
	sf::Time msPerTick;
};
}

#endif /* SNAKE_HPP_ */
