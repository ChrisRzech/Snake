#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TileMap/TileMap.hpp"
#include "SnakeLib/SnakeLib.hpp"

int main()
{
    srand(time(nullptr));

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
    const sf::Time TIME_PER_TICK = sf::milliseconds(50);

    /* Gamepieces */
    sf::Vector2u tileCount(20, 20);
    TM::Map map(screenSize, tileCount);
    Snake::Snake snake(map, sf::Color::Green);
    Snake::Fruit fruit(map, sf::Color::White);

    /* Score and messages */
    sf::Font textFont;
    TM::Tile msgTile(1, 0);
    sf::Text message("", textFont);
    message.setPosition(map.tilesToPixel(msgTile));
    if(!textFont.loadFromFile("resources/bit5x3.ttf"))
    {
        std::cout << "\"resources/bit5x3.ttf\" failed to load, aborting";
        return -1;
    }

    /* Rainbow color */
    unsigned int nextColorIndex = 0;
    const unsigned int MAX_COLOR = 24;
    const sf::Color RAINBOW[MAX_COLOR] =
            {{255,   0,   0}, {255,  64,   0}, {255, 128,   0}, {255, 191,   0},
             {255, 255,   0}, {191, 255,   0}, {128, 255,   0}, { 64, 255,   0},
             {  0, 255,   0}, {  0, 255,  64}, {  0, 255, 128}, {  0, 255, 191},
             {  0, 255, 255}, {  0, 191, 255}, {  0, 128, 255}, {  0,  64, 255},
             {  0,   0, 255}, { 64,   0, 255}, {128,   0, 255}, {191,   0, 255},
             {255,   0, 255}, {255,   0, 191}, {255,   0, 128}, {255,   0, 64}};
    //Colors obtained from https://www.w3schools.com/colors/colors_picker.asp

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
                if(!inputAllowed)
                    break;

                if(event.key.code == sf::Keyboard::Num1)      //Toggles snake color
                {
                    rainbowSnake = !rainbowSnake;
                }
                else if(event.key.code == sf::Keyboard::Num2) //Toggles border
                {
                    wrapAround = !wrapAround;
                }
                else if(event.key.code == sf::Keyboard::P)    //Pause
                {
                    snake.setDirection(Snake::Direction::PAUSE);
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
                snake.setDirection(Snake::Direction::UP);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                snake.setDirection(Snake::Direction::LEFT);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                snake.setDirection(Snake::Direction::DOWN);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                snake.setDirection(Snake::Direction::RIGHT);
        }

        /* Snake-fruit interaction */
        if(snake.getPosition() == fruit.getTile())
        {
            snake.increaseTailBy(1);
            fruit.reset();
        }

        /* Handle gameover state */
        if(gameover)
        {
            message.setString("Dead, press space to restart!");

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and inputAllowed)
            {
                gameover = false;
                fruit.reset();
                snake.reset();
            }
        }
        else
        {
            /* Tick based actions */
            if(gameClock.getElapsedTime() >= TIME_PER_TICK)
            {
                gameClock.restart();

                /* Snake color */
                if(rainbowSnake)
                {
                    snake.setColor(RAINBOW[nextColorIndex %= MAX_COLOR]);
                    nextColorIndex++;
                }
                else
                {
                    snake.setColor(sf::Color::Green);
                }

                //This updates a collision flag
                snake.updatePosition();
            }

            gameover = snake.tailCollision();
            message.setString(std::to_string(snake.getSize() - 1));
        }

        /* Wrap-around or border-of-death */
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
            if((snake.getPosition().tilePos().x < 0) or
               (snake.getPosition().tilePos().x >= (int) map.getTileCount().x) or
               (snake.getPosition().tilePos().y < 0) or
               (snake.getPosition().tilePos().y >= (int) map.getTileCount().y))
            {
                gameover = true;
            }
        }

        /* Drawing */
        window.clear();
        if(debugTileDraw)
            map.drawTiles(window, sf::Color::White);
        snake.draw(window);
        fruit.draw(window);
        window.draw(message);
        window.display();
    }

    return 0;
}
