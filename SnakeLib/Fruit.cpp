#include "Fruit.hpp"

namespace Snake
{
/* Constructors */
Fruit::Fruit(TM::Map& mN, sf::Color cN)
	 : MoveableBlock(mN, {rand() % (int)mN.GetTileCount().x, rand() % (int)mN.GetTileCount().y})
{SetColor(cN);} //note: using RandTile() will be using an uninitialized pointer (MoveableBlock::TM::Map* map)



/* Member Functions */
void Fruit::Reset()
{SetTile({rand() % (int)GetMap()->GetTileCount().x, rand() % (int)GetMap()->GetTileCount().y});}
}
