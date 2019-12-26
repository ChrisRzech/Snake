#include "Snake.hpp"

namespace Entity
{
Snake::Snake(const TM::Map& map, const TM::Tile& pos, const sf::Color& color)
    : map(&map), m_collision(false), m_userDir(Direction::PAUSE), m_prevDir(Direction::PAUSE)
{
    MoveableBlock head(map, pos);
    head.setColor(color);

    m_snake.push_back(head);
}

uint Snake::getSize() const
{
    return m_snake.size();
}

TM::Tile Snake::getPos() const
{
    return m_snake.front().pos;
}

std::vector<TM::Tile> Snake::getAllPos() const
{
    std::vector<TM::Tile> positions;
    
    for(const MoveableBlock& block : m_snake)
        positions.push_back(block.pos);
    
    return positions;
}

Direction Snake::getDirection() const
{
    return m_userDir;
}

sf::Color Snake::getColor(uint a) const
{
    return m_snake.at(a).getColor();
}

void Snake::setDirection(Direction a)
{
    m_userDir = a;
}

void Snake::setPos(const TM::Tile& a)
{
    m_snake.front().pos = a;
}

void Snake::setColor(const sf::Color& a)
{
    for(MoveableBlock& block : m_snake)
        block.setColor(a);
}

void Snake::setColor(const sf::Color& color, uint i)
{
    m_snake.at(i).setColor(color);
}

void Snake::grow(uint a)
{
    grow(a, m_snake.back().getColor());
}

void Snake::grow(uint count, const sf::Color& color)
{
    MoveableBlock tail(*map, m_snake.back().pos);
    tail.setColor(color);
    m_snake.resize(count + m_snake.size(), tail);
}

void Snake::shrink(uint count)
{
    if(count < m_snake.size())
        m_snake.resize(m_snake.size() - count, m_snake.front());

    /*
     * Since std::vector::resize() requires a value_type and MoveableBlock
     * doesn't have a default ctor, we just pass in head as a type. It
     * also doesn't make any difference since this function will never
     * create new elements to the vector
     */
}

void Snake::reset(const TM::Tile& a)
{
    setPos(a);
    shrink(m_snake.size() - 1);
    m_collision = false;
    m_userDir = Direction::PAUSE;
    m_prevDir = Direction::PAUSE;
}

void Snake::updatePos()
{
    if(m_userDir != Direction::PAUSE)
    {
        MoveableBlock newHead = m_snake.front();

        /* Update the head position */
        if(static_cast<int>(m_userDir) != -1 * static_cast<int>(m_prevDir))
            m_prevDir = m_userDir;
        newHead.move(m_prevDir);

        /* Update all the tails starting at the end */
        for(unsigned int i = m_snake.size() - 1; i > 0; i--)
        {
            m_snake[i].pos = m_snake[i - 1].pos;

            if(newHead.pos == m_snake[i].pos)
                m_collision = true;
        }

        m_snake.front() = newHead;
    }
}

void Snake::draw(sf::RenderWindow& w)
{
    /*
     * Drawing the blocks in reverse allows the head to
     * be on top of all the blocks
     */
    for(auto it = m_snake.rbegin(); it != m_snake.rend(); it++)
        it->draw(w);
}

bool Snake::tailCollision() const
{
    return m_collision;
}
}
