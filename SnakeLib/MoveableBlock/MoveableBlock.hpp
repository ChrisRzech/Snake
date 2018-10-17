#ifndef SNAKELIB_MOVEABLEBLOCK_MOVEABLEBLOCK_HPP_
#define SNAKELIB_MOVEABLEBLOCK_MOVEABLEBLOCK_HPP_

#include <SFML/Graphics.hpp>
#include "../../TileMap/TileMap.hpp"

namespace Snake
{
enum Direction{UP = -2, LEFT, PAUSE, RIGHT, DOWN};

class MoveableBlock
{
public:
	/* Constructors */
	MoveableBlock(TM::Map&, TM::Tile);


	/* Setters */
	void SetTile (TM::Tile);
	void SetColor(sf::Color);
	void SetSize (float);


	/* Getters */
	sf::Color GetColor() const;
	float     GetSize()  const;
	TM::Tile  GetTile()  const;
	TM::Map*  GetMap()   const;


	/* Member Functions */
	void Move(Direction);
	void Draw(sf::RenderWindow&);



public:
	TM::Map* map;
	TM::Tile tile;
	sf::RectangleShape block;
};
}

#endif /* SNAKELIB_MOVEABLEBLOCK_MOVEABLEBLOCK_HPP_ */
