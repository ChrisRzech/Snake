#include "MoveableBlock.hpp"

namespace Entity
{
MoveableBlock::MoveableBlock(const TM::Map& map, const TM::Tile& pos)
    : map(&map), pos(pos)
{
    m_block.setSize(map.getTilePixelSize());
}

float MoveableBlock::getSize() const
{
    return m_block.getSize().x;
}

sf::Color MoveableBlock::getColor() const
{
    return m_block.getFillColor();
}

void MoveableBlock::setSize(float size)
{
    m_block.setSize(sf::Vector2f(size,size));
}

void MoveableBlock::setColor(const sf::Color& color)
{
    m_block.setFillColor(color);
}

/* Member Functions */
void MoveableBlock::move(Direction dir)
{
    TM::Tile tile(0,0);
    
    switch(dir)
    {
    case Direction::PAUSE:
        //Do nothing
        break;
    case Direction::UP:
        tile.y = -1;
        break;
    case Direction::DOWN:
        tile.y = 1;
        break;
    case Direction::LEFT:
        tile.x = -1;
        break;
    case Direction::RIGHT:
        tile.x = 1;
        break;
    }

    pos += tile;
}

void MoveableBlock::draw(sf::RenderWindow& w)
{
    if(!map->isInBounds(pos))
        return;

    /*
     * If placed in move() or ctor(), weird things happen
     * This also prevents making this a const member function :(
     */
    m_block.setPosition(map->tileToPixel(pos));
    //TODO figure out why we can't place this in the ctor and move()

    w.draw(m_block);
}
}
