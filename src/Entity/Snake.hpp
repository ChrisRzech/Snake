#pragma once
#include <vector>
#include "MoveableBlock.hpp"

namespace Entity
{
    using uint = unsigned int;

class Snake
{
public:
    /* Constructors */
    Snake(const TM::Map&, const TM::Tile& pos, const sf::Color&);

    /* Getters */
    uint getSize() const;
    TM::Tile getPos() const;
    Direction getDirection() const;
    sf::Color getColor(uint index) const;

    /* Setters */
    void setPos(const TM::Tile&);
    void setDirection(Direction);
    void setColor(const sf::Color&);
    void setColor(const sf::Color&, uint tailIndex);

    /* Tail */
    void grow(uint);
    void grow(uint, const sf::Color&);
    void shrink(uint);

    /* Updates */
    void reset(const TM::Tile& pos);
    void updatePos();
    void draw(sf::RenderWindow&);
    bool tailCollision() const;
    
    /* Public data */
    const TM::Map* map;

private:
    /* Data */
    bool m_collision;
    std::vector<MoveableBlock> m_snake;
    Direction m_userDir;
    Direction m_prevDir;
};
}
