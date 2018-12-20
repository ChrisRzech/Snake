#include "Map.hpp"

namespace TM
{
/* Constructors */
Map::Map(sf::Vector2u screen, sf::Vector2u tileCount)
    : m_screen(screen), m_tileCount(tileCount)
{
    updateTilePixelSize();
    m_tiles.resize(m_tileCount.x * m_tileCount.y);

    unsigned int i = 0;
    int x = 0;
    int y = 0;

    while(i < m_tiles.size())
    {
        m_tiles[i] = Tile(x,y);

        if(static_cast<unsigned int>(x) == m_tileCount.x - 1)
        {
            y++;
            x = 0;
        }
        else
        {
            x++;
        }

        i++;
    }

    //TODO this ctor is a mess, clean it up bud
}

/* Getters */
sf::Vector2u Map::getScreenSize() const
{
    return m_screen;
}

sf::Vector2u Map::getTileCount() const
{
    return m_tileCount;
}

sf::Vector2f Map::getTilePixelSize() const
{
    return static_cast<sf::Vector2f>(m_tilePixelSize);
}

/* Setters */
void Map::setScreenSize(sf::Vector2u size)
{
    m_screen = size;
    updateTilePixelSize();
}

void Map::setTileCount(sf::Vector2u tileCount)
{
    m_tileCount = tileCount;
    updateTilePixelSize();
}

/* Conversions */
sf::Vector2f Map::tilesToPixel(Tile tile) const
{
    float x = static_cast<float>(tile.tilePos().x * m_tilePixelSize.x);
    float y = static_cast<float>(tile.tilePos().y * m_tilePixelSize.y);
    return sf::Vector2f(x,y);
}

Tile Map::pixelToTile(sf::Vector2f vec) const
{
    int tileX = std::floor(vec.x / m_tilePixelSize.x);
    int tileY = std::floor(vec.x / m_tilePixelSize.y);
    return Tile(tileX, tileY);
}

/* Debug Functions */
void Map::drawTiles(sf::RenderWindow& window, sf::Color border, sf::Color fill) const
{
    sf::RectangleShape block;

    for(Tile tile : m_tiles)
    {
        block.setPosition(tilesToPixel(tile));
        block.setSize(static_cast<sf::Vector2f>(m_tilePixelSize));
        block.setFillColor(fill);
        block.setOutlineColor(border);
        block.setOutlineThickness(0.5);

        window.draw(block);
    }
}

/* Helpers */
void Map::updateTilePixelSize()
{
    m_tilePixelSize.x = m_screen.x / m_tileCount.x;
    m_tilePixelSize.y = m_screen.y / m_tileCount.y;
}
}
