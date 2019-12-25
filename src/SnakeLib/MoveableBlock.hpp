#pragma once
#include <SFML/Graphics.hpp>
#include "../TileMap/TileMap.hpp"

namespace Snake
{
enum class Direction{UP = -2, LEFT, PAUSE, RIGHT, DOWN};

class MoveableBlock
{
public:
    /* Constructors */
    MoveableBlock(TM::Map&, TM::Tile = {0,0});

    /* Getters */
    TM::Tile  getTile()  const;
    float     getSize()  const;
    sf::Color getColor() const;
    TM::Map*  getMap()   const;

    /* Setters */
    void setTile(TM::Tile);
    void setSize(float);
    void setColor(sf::Color);

    /* Updates */
    void move(Direction);
    void draw(sf::RenderWindow&);

public:
    TM::Map* m_map;
    TM::Tile m_tile;
    sf::RectangleShape m_block;
};
}
