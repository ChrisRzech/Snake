#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TileMap/TileMap.hpp"
#include "SnakeLib/SnakeLib.hpp"

int main()
{
	srand(time(0));


	bool inputAllowed = true;
	bool debugTile = false;
	bool gameover = false;
	bool wrapAround = false;


	sf::RenderWindow window({600,600}, "Snake SFML", sf::Style::Close);
	window.setFramerateLimit(60);


	sf::Clock clock;
	sf::Time timePerTick = sf::milliseconds(50);


	const sf::Vector2u TILE_COUNT = {20,20};
	TM::Map map({600,600}, TILE_COUNT);
	Snake::Snake snake(map, sf::Color::Green, clock, timePerTick);
	Snake::Fruit fruit(map, sf::Color::White);



	while(window.isOpen())
	{
		/* Window and System Events */
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				if(event.key.code == sf::Keyboard::Space)
					snake.IncreaseTailBy(1, sf::Color::Red); //"Cheater" tail
				else if(event.key.code == sf::Keyboard::BackSpace)
					snake.IncreaseTailBy(-1); //Deletes a tail
				else if(event.key.code == sf::Keyboard::F3 and event.key.shift)
					debugTile = !debugTile; //Toggles tile drawing
				break;

			case sf::Event::LostFocus:
				inputAllowed = false;
				break;

			case sf::Event::GainedFocus:
				inputAllowed = true;
				break;

			default:
				break;
			}
		}



		/* Snake-Fruit Interaction */
		if(snake.GetHeadTile() == fruit.GetTile())
		{
			sf::Uint8 r = rand() % 255;
			sf::Uint8 g = rand() % 255;
			sf::Uint8 b = rand() % 255;
			snake.IncreaseTailBy(1, fruit.GetColor());
			fruit.Reset();
			fruit.SetColor({r,g,b});
		}



		if(wrapAround)
		{
			/* Enables Wrap-Around */
			if(snake.GetHeadTile().TilePos().x < 0)
			{
				TM::Tile newTile(map.GetTileCount().x - 1, snake.GetHeadTile().TilePos().y);
				snake.SetHeadPos(newTile);
			}
			else if(snake.GetHeadTile().TilePos().x >= (int)map.GetTileCount().x)
			{
				TM::Tile newTile(0, snake.GetHeadTile().TilePos().y);
				snake.SetHeadPos(newTile);
			}
			else if(snake.GetHeadTile().TilePos().y < 0)
			{
				TM::Tile newTile(snake.GetHeadTile().TilePos().x, map.GetTileCount().y - 1);
				snake.SetHeadPos(newTile);
			}
			else if(snake.GetHeadTile().TilePos().y >= (int)map.GetTileCount().y)
			{
				TM::Tile newTile(snake.GetHeadTile().TilePos().x, 0);
				snake.SetHeadPos(newTile);
			}
		}
		else
		{
			/* Enables Wall-Of-Deaths */
			if(snake.GetHeadTile().TilePos().x < 0                          or
			   snake.GetHeadTile().TilePos().x >= (int)map.GetTileCount().x or
			   snake.GetHeadTile().TilePos().y < 0                          or
			   snake.GetHeadTile().TilePos().y >= (int)map.GetTileCount().y)
				gameover = true;
		}

		gameover = snake.CheckTailCollision();



		/* Realtime Keyboard */
		if(inputAllowed)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				snake.SetDirection(Snake::Direction::UP);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				snake.SetDirection(Snake::Direction::LEFT);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				snake.SetDirection(Snake::Direction::DOWN);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				snake.SetDirection(Snake::Direction::RIGHT);
		}


		snake.Update();

		if(gameover)
			break;



		/* Drawing */
		window.clear();
		if(debugTile)
			map.DrawTiles(window, sf::Color::White);
		snake.Draw(window);
		fruit.Draw(window);
		window.display();
	}



	return 0;
}
