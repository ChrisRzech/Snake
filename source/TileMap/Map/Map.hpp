#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Tile/Tile.hpp"

namespace TM
{
class Map
{
public:
    /* Constructors */
    Map(sf::Vector2u screen, sf::Vector2u tileCount);

    /* Getters */
    sf::Vector2u getScreenSize()    const;
    sf::Vector2u getTileCount()     const;
    sf::Vector2f getTilePixelSize() const;

    /* Setters */
    void setScreenSize(sf::Vector2u);
    void setTileCount(sf::Vector2u);

    /* Conversions */
    sf::Vector2f tilesToPixel(Tile) const;
    Tile pixelToTile(sf::Vector2f)  const;

    /* Debug Functions */
    void drawTiles(sf::RenderWindow&, sf::Color border, sf::Color fill = sf::Color::Transparent) const;

private:
    /* Helpers */
    void updateTilePixelSize();

    /* Data */
    sf::Vector2u m_screen;
    sf::Vector2u m_tileCount;
    sf::Vector2u m_tilePixelSize;
    std::vector<Tile> m_tiles;
};
}
