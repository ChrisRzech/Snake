#include "Map.hpp"
#include <cmath>

namespace TM
{
Map::Map(const sf::Vector2u& pixelSize, const sf::Vector2u& tileCount)
    : m_pixelSize(pixelSize), m_tileCount(tileCount)
{
    updateTilePixelSize();
}

sf::Vector2u Map::getPixelSize() const
{
    return m_pixelSize;
}

sf::Vector2u Map::getTileCount() const
{
    return m_tileCount;
}

sf::Vector2f Map::getTilePixelSize() const
{
    return static_cast<sf::Vector2f>(m_tilePixelSize);
}

void Map::setPixelSize(const sf::Vector2u& a)
{
    m_pixelSize = a;
    updateTilePixelSize();
}

void Map::setTileCount(const sf::Vector2u& a)
{
    m_tileCount = a;
    updateTilePixelSize();
}

sf::Vector2f Map::tileToPixel(const Tile& a) const
{
    float x = static_cast<float>(a.getPos().x * m_tilePixelSize.x);
    float y = static_cast<float>(a.getPos().y * m_tilePixelSize.y);
    return sf::Vector2f(x,y);
}

Tile Map::pixelToTile(const sf::Vector2f& a) const
{
    int x = static_cast<int>(std::floor(a.x / m_tilePixelSize.x));
    int y = static_cast<int>(std::floor(a.y / m_tilePixelSize.y));
    return Tile(x, y);
}

/* Bounds check */
bool Map::isInBounds(const Tile& a) const
{
    return a.getPos().x >= 0                               &&
           a.getPos().x <  static_cast<int>(m_tileCount.x) &&
           a.getPos().y >= 0                               &&
           a.getPos().y <  static_cast<int>(m_tileCount.y);
}

void Map::draw(sf::RenderWindow& window, const sf::Color& fill, const sf::Color& border) const
{
    //TODO instead of drawing each tile, draw elongated rectangles as borders
    sf::RectangleShape block;

    for(unsigned int x = 0; x < m_tileCount.x; x++)
    {
        for(unsigned int y = 0; y < m_tileCount.y; y++)
        {
            block.setPosition(tileToPixel(Tile(x, y)));
            block.setSize(static_cast<sf::Vector2f>(m_tilePixelSize));
            block.setFillColor(fill);
            block.setOutlineColor(border);
            block.setOutlineThickness(0.5);
            window.draw(block);
        }
    }
}

void Map::updateTilePixelSize()
{
    m_tilePixelSize.x = m_pixelSize.x / m_tileCount.x;
    m_tilePixelSize.y = m_pixelSize.y / m_tileCount.y;
}
}
