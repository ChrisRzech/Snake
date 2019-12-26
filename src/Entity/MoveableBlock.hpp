#pragma once
#include <SFML/Graphics.hpp>
#include "../TileMap/TileMap.hpp"

namespace Entity
{
enum Direction{UP = -2, LEFT = -1, PAUSE = 0, RIGHT = 1, DOWN = 2};

class MoveableBlock
{
public:
    /* Constructors */
    MoveableBlock(const TM::Map&, const TM::Tile& position = {0,0});

    /* Getters */
    float getSize() const;
    sf::Color getColor() const;

    /* Setters */
    void setSize(float);
    void setColor(const sf::Color&);

    /* Updates */
    void move(Direction);
    void draw(sf::RenderWindow&);
    
    /* Public data */
    const TM::Map* map;
    TM::Tile pos;

public:
    /* Data */
    sf::RectangleShape m_block;
};
}
