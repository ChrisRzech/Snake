#include "MoveableBlock.hpp"
#include <iostream>

namespace Snake
{
/* Constructors */
MoveableBlock::MoveableBlock(TM::Map& map, TM::Tile tile)
    : m_map(&map), m_tile(tile)
{
    m_block.setSize(map.getTilePixelSize());
}

/* Getters */
TM::Tile MoveableBlock::getTile() const
{
    return m_tile;
}

float MoveableBlock::getSize() const
{
    return m_block.getSize().x;
}

sf::Color MoveableBlock::getColor() const
{
    return m_block.getFillColor();
}

TM::Map* MoveableBlock::getMap() const
{
    return m_map;
}

/* Setters */
void MoveableBlock::setTile(TM::Tile tile)
{
    m_tile = tile;
}

void MoveableBlock::setSize(float size)
{
    m_block.setSize(sf::Vector2f(size,size));
}

void MoveableBlock::setColor(sf::Color color)
{
    m_block.setFillColor(color);
}

/* Member Functions */
void MoveableBlock::move(Direction dir)
{
    if(dir == Direction::PAUSE)
    {
        m_tile += TM::Tile(0, 0);
    }
    else if(dir == Direction::UP)
    {
        m_tile += TM::Tile(0, -1);
    }
    else if(dir == Direction::DOWN)
    {
        m_tile += TM::Tile(0, 1);
    }
    else if(dir == Direction::LEFT)
    {
        m_tile += TM::Tile(-1,0);
    }
    else if(dir == Direction::RIGHT)
    {
        m_tile += TM::Tile(1,0);
    }
}

void MoveableBlock::draw(sf::RenderWindow& w)
{
    /*
     * If placed in move() or ctor(), weird things happen
     * This also prevents making this a const member function :(
     */
    m_block.setPosition(m_map->tilesToPixel(m_tile));
    //TODO figure out why we can't place this in the ctor and move()

    w.draw(m_block);
}
}
