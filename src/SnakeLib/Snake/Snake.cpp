#include "Snake.hpp"

namespace Snake
{
/* Constructors */
Snake::Snake(TM::Map& m, sf::Color c, sf::Clock& cl, sf::Time ms)
	 : map(&m), userDir(PAUSE), clock(&cl), msPerTick(ms)
{
	TM::Tile startTile(map->GetTileCount().x / 2, map->GetTileCount().y / 2);

	MoveableBlock head(m, startTile);
	head.SetColor(c);

	snake.push_back(head);

	headCollision = false;
}



/* Getters */
unsigned int Snake::GetLength()    const {return snake.size();}
TM::Tile     Snake::GetHeadTile()  const {return snake[0].GetTile();}
Direction    Snake::GetDirection() const {return userDir;}



/* Setters */
void Snake::SetDirection(Direction d){userDir = d;}
void Snake::SetHeadPos(TM::Tile t)   {snake[0].SetTile(t);}
void Snake::SetColor(sf::Color c)
{
	for(unsigned int i = 0; i < snake.size(); i++)
		snake[i].SetColor(c);
}



/* Member Functions */
void Snake::IncreaseTailBy(int count, sf::Color c)
{
	if(count + snake.size() != 0)
	{
		MoveableBlock tail(*map, snake[snake.size() - 1].GetTile());
		tail.SetColor(c);
		tail.SetSize(snake[snake.size() - 1].GetSize());
		snake.resize(count + snake.size(), tail);
	}
}


void Snake::Update()
{
	if(clock->getElapsedTime() >= msPerTick)
	{
		clock->restart();

		if(userDir != PAUSE)
		{
			//Update all the tails starting at the end
			for(int i = snake.size() - 1; i > 0; i--)
				snake[i].SetTile(snake[i - 1].GetTile());


			//Update the head position
			static Direction prevDir = PAUSE;
			if(userDir != -prevDir)
				prevDir = userDir;
			snake[0].Move(prevDir);


			//Check for head collision
			for(unsigned int i = 1; i < snake.size(); i++)
				if(snake[0].GetTile() == snake[i].GetTile())
					headCollision = true;
		}
	}
}


bool Snake::CheckTailCollision() const
{return headCollision;}


void Snake::Draw(sf::RenderWindow& w)
{
	for(int i = snake.size() - 1; i >= 0; i--)
		snake[i].Draw(w);
}
}
