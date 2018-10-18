#ifndef TILEMAP_MAP_MAP_HPP_
#define TILEMAP_MAP_MAP_HPP_

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
	Map(sf::Vector2u screenSize, sf::Vector2u tileCount);

	
	/* Getters */
	sf::Vector2u GetScreenSize()    const;
	sf::Vector2u GetTileCount()     const;
	sf::Vector2f GetTilePixelSize() const;


	/* Member Functions */
	sf::Vector2f TilesToPixel(Tile) const;
	Tile PixelToTile(sf::Vector2f)  const;


	/* Debug Functions */
	void DrawTiles(sf::RenderWindow&, sf::Color border, sf::Color fill = sf::Color::Transparent) const;



private:
	sf::Vector2u screen;
	sf::Vector2u tileCount;
	sf::Vector2u tilePixelSize;
	std::vector<Tile> tiles;
};
}

#endif /* TILEMAP_MAP_MAP_HPP_ */
