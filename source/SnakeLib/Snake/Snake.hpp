#pragma once
#include <vector>
#include "../MoveableBlock/MoveableBlock.hpp"

namespace Snake
{
    using uint = unsigned int;

class Snake
{
public:
    /* Constructors */
    Snake(TM::Map&, sf::Color, sf::Clock&, sf::Time msPerTick);

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
    void increaseTailBy(uint, sf::Color = sf::Color::Green);
    void decreaseTailBy(uint);

    /* Updates */
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

    /* Timing */
    sf::Clock* m_clock;
    sf::Time m_msPerTick;
};
}
