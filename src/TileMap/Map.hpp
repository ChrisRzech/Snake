#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

namespace TM
{
class Map
{
public:
    /* Constructors */
    Map(const sf::Vector2u& pixelSize, const sf::Vector2u& tileCount);

    /* Getters */
    sf::Vector2u getPixelSize() const;
    sf::Vector2u getTileCount() const;
    sf::Vector2f getTilePixelSize() const;

    /* Setters */
    void setPixelSize(const sf::Vector2u&);
    void setTileCount(const sf::Vector2u&);

    /* Conversions */
    sf::Vector2f tileToPixel(const Tile&) const;
    Tile pixelToTile(const sf::Vector2f&) const;

    /* Bounds check */
    bool isInBounds(const Tile&) const;

    /* Debug Functions */
    void draw(sf::RenderWindow&, const sf::Color& fill, const sf::Color& border) const;

private:
    /* Helpers */
    void updateTilePixelSize();

    /* Data */
    sf::Vector2u m_pixelSize;
    sf::Vector2u m_tileCount;
    sf::Vector2u m_tilePixelSize;
};
}
