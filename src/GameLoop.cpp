#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TileMap/TileMap.hpp"
#include "SnakeLib/SnakeLib.hpp"

int main()
{
	srand(time(0));


	sf::Vector2u screenSize({600,600});
	sf::RenderWindow window({screenSize.x, screenSize.y}, "Snake", sf::Style::Close);


	sf::Clock gameClock;
	sf::Time timePerTick = sf::milliseconds(50);


	sf::Vector2u tileCount({20,20});
	TM::Map map(screenSize, tileCount);
	Snake::Snake snake(map, sf::Color::Green, gameClock, timePerTick);
	Snake::Fruit fruit(map, sf::Color::White);
	Snake::Direction direction = Snake::Direction::PAUSE;


	bool debugTileDraw  = false;
	bool debugTileClick = false;

	bool inputAllowed = true;
	bool gameover     = false;
	bool wrapAround   = false;
	bool rainbowSnake = false;


	std::cout << "Controls\n"
				 "WASD: Movement\n"
				 "Num1: Toggle Rainbow Snake\n"
				 "Num2: Toggle Wrap-Around\n"
				 "P   : Pause\n\n\n"
				 "Debugging Controls\n"
				 "Backspace: Delete a tail\n"
				 "F1       : Toggle Tile Drawing\n"
				 "F2       : Toggle Tile Position w/ L-Click\n\n\n"
				 "Current Settings\n"
				 "Window Size: " << screenSize.x << " x " << screenSize.y << "\n"
				 "Tile Count : " << tileCount.x  << " x " << tileCount.y  << "\n\n" << std::flush;



	/* Window Loop */
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
				if(event.key.code == sf::Keyboard::Num1)           //Enables rainbow snake and fruit
					rainbowSnake = !rainbowSnake;
				else if(event.key.code == sf::Keyboard::Num2)      //Enables wrap-around
					wrapAround = !wrapAround;
				else if(event.key.code == sf::Keyboard::BackSpace) //Deletes a tail
					snake.IncreaseTailBy(-1);
				else if(event.key.code == sf::Keyboard::P)         //Toggle pause
					direction = Snake::Direction::PAUSE;
				else if(event.key.code == sf::Keyboard::F1)        //Toggles tile drawing
					debugTileDraw = !debugTileDraw;
				else if(event.key.code == sf::Keyboard::F2)        //Toggles tile mouse click
					debugTileClick = !debugTileClick;
				break;

			case sf::Event::MouseButtonPressed:
				if(debugTileClick)
				{
					sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
					std::cout << "Tile: (" << map.PixelToTile(mouse).TilePos().x << ','
							  << map.PixelToTile(mouse).TilePos().y << ')' << std::endl;
				}
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



		/* Realtime Keyboard */
		if(inputAllowed)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				direction = Snake::Direction::UP;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				direction = Snake::Direction::LEFT;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				direction = Snake::Direction::DOWN;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				direction = Snake::Direction::RIGHT;
		}
		snake.SetDirection(direction);



		/* Snake-Fruit Interaction */
		if(snake.GetHeadTile() == fruit.GetTile())
		{
			if(rainbowSnake)
			{
				sf::Uint8 r = rand() % 255;
				sf::Uint8 g = rand() % 255;
				sf::Uint8 b = rand() % 255;
				snake.IncreaseTailBy(1, fruit.GetColor());
				fruit.ResetTilePos();
				fruit.SetColor({r,g,b});
			}
			else
			{
				snake.IncreaseTailBy(1);
				fruit.ResetTilePos();
				fruit.SetColor(sf::Color::White);
			}
		}



		/* Enables Wrap-Around or Border-Of-Death*/
		if(wrapAround)
		{
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
			if((snake.GetHeadTile().TilePos().x < 0)                          or
			   (snake.GetHeadTile().TilePos().x >= (int)map.GetTileCount().x) or
			   (snake.GetHeadTile().TilePos().y < 0)                          or
			   (snake.GetHeadTile().TilePos().y >= (int)map.GetTileCount().y))
				gameover = true;
		}



		snake.Update(); //Update the snake
		/* note:
		 * snake.Update() updates a flag that determines if
		 * the head is one of the tiles of the tail
		 */
		if(!gameover)
			gameover = snake.CheckTailCollision(); //Update tail collision



		/* Drawing */
		window.clear();
		if(debugTileDraw)
			map.DrawTiles(window, sf::Color::White);
		snake.Draw(window);
		fruit.Draw(window);
		window.display();



		/* Handling gameover State */
		if(gameover)
		{
			std::cout << "Died, press any key!" << std::endl;
			do
			{
				window.pollEvent(event);
				if(event.type == sf::Event::KeyPressed or event.type == sf::Event::Closed)
					window.close();
			} while(window.isOpen());
		}
	}



	return 0;
}
