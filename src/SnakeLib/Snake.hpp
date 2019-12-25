#pragma once
#include <vector>
#include "MoveableBlock.hpp"

namespace Snake
{
    using uint = unsigned int;

class Snake
{
public:
    /* Constructors */
    Snake(TM::Map&, sf::Color);

    /* Getters */
    uint      getSize()      const;
    TM::Tile  getPosition()  const;
    Direction getDirection() const;
    sf::Color getColor(uint index) const;

    /* Setters */
    void setPosition(TM::Tile);
    void setDirection(Direction);
    void setColor(sf::Color);
    void setColor(sf::Color, uint index);

    /* Tail size */
    void increaseTailBy(uint);
    void increaseTailBy(uint, sf::Color);
    void decreaseTailBy(uint);

    /* Updates */
    void reset();
    void updatePosition();
    void draw(sf::RenderWindow&);
    bool tailCollision() const;

private:
    /* Tile mapping */
    TM::Map* m_map;

    /* Snake data */
    bool m_collision;
    std::vector<MoveableBlock> m_snake;
    Direction m_userDir;
    Direction m_prevDir;
};
}
