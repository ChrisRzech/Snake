#ifndef TILEMAP_TILE_TILE_HPP_
#define TILEMAP_TILE_TILE_HPP_

#include <SFML/Graphics.hpp>

namespace TM
{
class Tile
{
public:
	/* Constructors */
	Tile();
	Tile(int xPosInTileSpace, int yPosInTileSpace);
	Tile(const sf::Vector2u& posInTileSpace);
	Tile(const sf::Vector2i& posInTileSpace);
	Tile(const sf::Vector2f& posInTileSpace);


	/* Getters */
	sf::Vector2i TilePos() const;


	/* Operator Overloads */
	bool  operator==(const Tile&) const;
	bool  operator!=(const Tile&) const;
	Tile  operator+ (const Tile&) const;
	Tile  operator- (const Tile&) const;
	Tile& operator= (const Tile&);
	Tile& operator+=(const Tile&);
	Tile& operator-=(const Tile&);



private:
	int x, y;
};
}

#endif /* TILEMAP_TILE_TILE_HPP_ */
