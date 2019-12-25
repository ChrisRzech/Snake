#include "Map.hpp"

namespace TM
{
/* Constructors */
Map::Map(sf::Vector2u screen, sf::Vector2u tileCount)
    : m_screen(screen), m_tileCount(tileCount)
{
    updateTilePixelSize();
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
    int tileX = static_cast<int>(std::floor(vec.x / m_tilePixelSize.x));
    int tileY = static_cast<int>(std::floor(vec.x / m_tilePixelSize.y));
    return Tile(tileX, tileY);
}

/* Bounds check */
bool Map::isInBounds(TM::Tile tile) const
{
    return tile.tilePos().x >= 0                               and
           tile.tilePos().x <  static_cast<int>(m_tileCount.x) and
           tile.tilePos().y >= 0                               and
           tile.tilePos().y <  static_cast<int>(m_tileCount.y);
}

/* Debug Functions */
void Map::drawTiles(sf::RenderWindow& window, sf::Color fill, sf::Color border) const
{
    //TODO instead of drawing each tile, draw elongated rectangles as borders
    sf::RectangleShape block;

    for(unsigned int x = 0; x < m_tileCount.x; x++)
    {
        for(unsigned int y = 0; y < m_tileCount.y; y++)
        {
            block.setPosition(tilesToPixel(Tile(x, y)));
            block.setSize(static_cast<sf::Vector2f>(m_tilePixelSize));
            block.setFillColor(fill);
            block.setOutlineColor(border);
            block.setOutlineThickness(0.5);
            window.draw(block);
        }
    }
}

/* Helpers */
void Map::updateTilePixelSize()
{
    m_tilePixelSize.x = m_screen.x / m_tileCount.x;
    m_tilePixelSize.y = m_screen.y / m_tileCount.y;
}
}
