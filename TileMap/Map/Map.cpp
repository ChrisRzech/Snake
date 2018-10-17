#include "Map.hpp"

namespace TM
{
/* Constructors */
Map::Map(sf::Vector2u scr, sf::Vector2u tile) : screen(scr), tileCount(tile)
{
	tilePixelSize = {screen.x / tileCount.x, screen.y / tileCount.y};
	tiles.resize(tileCount.x * tileCount.y);

	unsigned int i = 0;
	int x = 0, y = 0;
	while(i < tiles.size())
	{
		tiles[i] = Tile(x,y);

		if(static_cast<unsigned int>(x) == tileCount.x - 1)
		{
			y++;
			x = 0;
		}
		else
			x++;
		i++;
	}
}



/* Getters */
sf::Vector2u Map::GetScreenSize()    const {return (screen);}
sf::Vector2u Map::GetTileCount()     const {return (tileCount);}
sf::Vector2f Map::GetTilePixelSize() const {return static_cast<sf::Vector2f>(tilePixelSize);}



/* Member Functions */
sf::Vector2f Map::TilesToPixel(Tile tile) const
{
	float x = static_cast<float>(tile.TilePos().x * tilePixelSize.x);
	float y = static_cast<float>(tile.TilePos().y * tilePixelSize.y);
	return {x,y};
}

template<typename T>
Tile Map::PixelToTile(sf::Vector2<T> vec) const
{return {static_cast<int>(std::floor(vec.x / tilePixelSize.x)), static_cast<int>(std::floor(vec.y / tilePixelSize.y))};}


/* Debug Functions */
void Map::DrawTiles(sf::RenderWindow& window, sf::Color border, sf::Color fill) const
{
	sf::RectangleShape shape;

	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		shape.setPosition(TilesToPixel(tiles[i]));
		shape.setSize(static_cast<sf::Vector2f>(tilePixelSize));
		shape.setFillColor(fill);
		shape.setOutlineColor(border);
		shape.setOutlineThickness(0.5);

		window.draw(shape);
	}
}
}
