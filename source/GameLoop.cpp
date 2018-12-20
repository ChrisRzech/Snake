#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TileMap/TileMap.hpp"
#include "SnakeLib/SnakeLib.hpp"

int main()
{
    srand(time(0));

    /* Window icon */
    sf::Image icon;
    if(!icon.loadFromFile("resources/icon.png"))
    {
        std::cout << "\"resources/icon.png\" failed to load, aborting";
        return -1;
    }

    /* Window settings */
    sf::Vector2u screenSize(600, 600);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Snake", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    /* Internal clock */
    sf::Clock gameClock;
    sf::Time timePerTick = sf::milliseconds(50);

    /* Gamepieces */
    sf::Vector2u tileCount(20, 20);
    TM::Map map(screenSize, tileCount);
    Snake::Snake snake(map, sf::Color::Green, gameClock, timePerTick);
    Snake::Fruit fruit(map, sf::Color::White);
    Snake::Direction direction = Snake::Direction::PAUSE;

    /* Debug flags */
    bool debugTileDraw  = false;
    bool debugTileClick = false;

    /* Game flags */
    bool inputAllowed = true;
    bool gameover     = false;
    bool wrapAround   = false;
    bool rainbowSnake = false;

    std::cout << "WASD: Movement\n"
                 "Num1: Toggle Rainbow Snake\n"
                 "Num2: Toggle Wrap-Around\n"
                 "P   : Pause\n\n"
                 "Settings\n"
                 "Window Size: " << screenSize.x << 'x' << screenSize.y << "\n"
                 "Tile Count : " << tileCount.x  << 'x' << tileCount.y  << "\n\n" << std::flush;

    /* Window loop */
    while(window.isOpen())
    {
        /* Events */
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::LostFocus:
                inputAllowed = false;
                break;
            case sf::Event::GainedFocus:
                inputAllowed = true;
                break;
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::Num1)      //Enables rainbow snake and fruit
                {
                    rainbowSnake = !rainbowSnake;
                }
                else if(event.key.code == sf::Keyboard::Num2) //Enables wrap-around
                {
                    wrapAround = !wrapAround;
                }
                else if(event.key.code == sf::Keyboard::P)    //Pause
                {
                    direction = Snake::Direction::PAUSE;
                }
                else if(event.key.code == sf::Keyboard::F1)   //Toggles tile drawing
                {
                    debugTileDraw = !debugTileDraw;
                }
                else if(event.key.code == sf::Keyboard::F2)   //Toggles tile mouse click
                {
                    debugTileClick = !debugTileClick;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(debugTileClick)
                {
                    sf::Vector2f mouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    std::cout << "Tile: (" << map.pixelToTile(mouse).tilePos().x
                              << ','       << map.pixelToTile(mouse).tilePos().y
                              << ")\n";
                }
                break;
            default:
                break;
            }
        }

        /* Realtime input */
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

            snake.setDirection(direction);
        }

        /* Snake-fruit interaction */
        if(snake.getPosition() == fruit.getTile())
        {
            if(rainbowSnake)
            {
                sf::Uint8 r = rand() % 255;
                sf::Uint8 g = rand() % 255;
                sf::Uint8 b = rand() % 255;
                snake.increaseTailBy(1, fruit.getColor());
                fruit.resetTilePos();
                fruit.setColor({r, g, b});
            }
            else
            {
                snake.increaseTailBy(1);
                fruit.resetTilePos();
                fruit.setColor(sf::Color::White);
            }
        }

        /* Wrap-around or border-of-death*/
        if(wrapAround)
        {
            if(snake.getPosition().tilePos().x < 0)
            {
                TM::Tile newTile(map.getTileCount().x - 1, snake.getPosition().tilePos().y);
                snake.setPosition(newTile);
            }
            else if(snake.getPosition().tilePos().x >= (int) map.getTileCount().x)
            {
                TM::Tile newTile(0, snake.getPosition().tilePos().y);
                snake.setPosition(newTile);
            }
            else if(snake.getPosition().tilePos().y < 0)
            {
                TM::Tile newTile(snake.getPosition().tilePos().x, map.getTileCount().y - 1);
                snake.setPosition(newTile);
            }
            else if(snake.getPosition().tilePos().y >= (int) map.getTileCount().y)
            {
                TM::Tile newTile(snake.getPosition().tilePos().x, 0);
                snake.setPosition(newTile);
            }
        }
        else
        {
            if((snake.getPosition().tilePos().x < 0)                          or
               (snake.getPosition().tilePos().x >= (int)map.getTileCount().x) or
               (snake.getPosition().tilePos().y < 0)                          or
               (snake.getPosition().tilePos().y >= (int)map.getTileCount().y))
            {
                gameover = true;
            }
        }

        /*
         * This updates a flag that determines
         * if the head collides with itself
         */
        snake.updatePosition();

        if(!gameover)
            gameover = snake.tailCollision();

        /* Drawing */
        window.clear();
        if(debugTileDraw)
            map.drawTiles(window, sf::Color::White);
        snake.draw(window);
        fruit.draw(window);
        window.display();

        /* Handling gameover State */
        if(gameover)
        {
            std::cout << "Dead, press space to close!" << std::endl;
            while(window.isOpen())
            {
                window.pollEvent(event);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) or event.type == sf::Event::Closed)
                    window.close();
            }
        }
    }

    return 0;
}
