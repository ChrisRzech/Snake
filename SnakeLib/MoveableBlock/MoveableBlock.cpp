#include "MoveableBlock.hpp"

namespace Snake
{
/* Constructors */
MoveableBlock::MoveableBlock(TM::Map& mN, TM::Tile tN) : map(&mN), tile(tN)
{block.setSize(map->GetTilePixelSize());}



/* Setters */
void MoveableBlock::SetTile  (TM::Tile tN)  {tile = tN;}
void MoveableBlock::SetSize  (float fN)     {block.setSize({fN,fN});}
void MoveableBlock::SetColor (sf::Color cN) {block.setFillColor(cN);}



/* Getters */
sf::Color MoveableBlock::GetColor() const {return block.getFillColor();}
float     MoveableBlock::GetSize()  const {return block.getSize().x;}
TM::Tile  MoveableBlock::GetTile()  const {return tile;}
TM::Map*  MoveableBlock::GetMap()   const {return map;}



/* Member Functions */
void MoveableBlock::Move(Direction dir)
{
	sf::Vector2i dirVec;
	switch(dir)
	{
	case UP:
		dirVec = {0,-1};
		break;
	case DOWN:
		dirVec = {0,1};
		break;
	case LEFT:
		dirVec = {-1,0};
		break;
	case RIGHT:
		dirVec = {1,0};
		break;
	case PAUSE:
		dirVec = {0,0};
		break;
	}

	tile += dirVec;
}


void MoveableBlock::Draw(sf::RenderWindow& w)
{
	block.setPosition(map->TilesToPixel(tile));
	w.draw(block);
}
}
