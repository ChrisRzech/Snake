#include "Snake.hpp"

namespace Snake
{
/* Constructors */
Snake::Snake(TM::Map& map, sf::Color color, sf::Clock& cl, sf::Time ms)
    : m_map(&map), m_collision(false), m_userDir(Direction::PAUSE), m_clock(&cl), m_msPerTick(ms)
{
    TM::Tile startTile(m_map->getTileCount().x / 2, m_map->getTileCount().y / 2);

    MoveableBlock head(*m_map, startTile);
    head.setColor(color);

    m_snake.push_back(head);
}

/* Getters */
uint Snake::getSize() const
{
    return m_snake.size();
}

TM::Tile Snake::getPosition() const
{
    return m_snake[0].getTile();
}

Direction Snake::getDirection() const
{
    return m_userDir;
}

sf::Color Snake::getColor(uint i) const
{
    return m_snake[i].getColor();
}

/* Setters */
void Snake::setDirection(Direction d)
{
    m_userDir = d;
}

void Snake::setPosition(TM::Tile t)
{
    m_snake[0].setTile(t);
}

void Snake::setColor(sf::Color c)
{
    for(MoveableBlock block : m_snake)
        block.setColor(c);
}

void Snake::setColor(sf::Color color, uint i)
{
    m_snake[i].setColor(color);
}

/* Tail size */
void Snake::increaseTailBy(uint count, sf::Color c)
{
    MoveableBlock tail(*m_map, m_snake[m_snake.size() - 1].getTile());
    tail.setColor(c);
    tail.setSize(m_snake[m_snake.size() - 1].getSize());
    m_snake.resize(count + m_snake.size(), tail);
}

void Snake::decreaseTailBy(uint count)
{
    if(m_snake.size() - count != 0)
        m_snake.resize(m_snake.size() - count, m_snake[0]);

    /*
     * Since std::vector::resize() requires a value_type and MoveableBlock
     * doesn't have a default ctor, we just pass in head as a type. It
     * also doesn't make any difference since this function will never
     * create new elements to the vector
     */
}

/* Updates */
void Snake::updatePosition()
{
    if(m_clock->getElapsedTime() >= m_msPerTick)
    {
        m_clock->restart();

        if(m_userDir != Direction::PAUSE)
        {
            /* Update all the tails starting at the end */
            for(int i = m_snake.size() - 1; i > 0; i--)
                m_snake[i].setTile(m_snake[i - 1].getTile());

            /* Update the head position */
            static Direction prevDir = Direction::PAUSE;
            if(static_cast<int>(m_userDir) != -1 * static_cast<int>(prevDir))
                prevDir = m_userDir;
            m_snake[0].move(prevDir);

            /* Check for head collision */
            for(uint i = 1; i < m_snake.size(); i++)
            {
                if(m_snake[0].getTile() == m_snake[i].getTile())
                    m_collision = true;
            }
        }
    }
}

void Snake::draw(sf::RenderWindow& w)
{
    /*
     * Drawing the blocks in reverse
     * allows the head to be on top
     * of all the blocks
     */
    for(int i = m_snake.size() - 1; i >= 0; i--)
        m_snake[i].draw(w);
}

bool Snake::tailCollision() const
{
    return m_collision;
}
}
