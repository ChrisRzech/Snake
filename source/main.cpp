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
    const unsigned int MIN_TIME_PER_TICK = 50;
    const unsigned int MAX_TIME_PER_TICK = 100;
    unsigned int tickNumber = MIN_TIME_PER_TICK;
    sf::Time timePerTick = sf::milliseconds(tickNumber);

    /* Gamepieces */
    sf::Vector2u tileCount(20, 20);
    TM::Map map(screenSize, tileCount);
    Snake::Snake snake(map, sf::Color::Green);
    Snake::Fruit fruit(map, sf::Color::White);

    /* Score and messages */
    sf::Font textFont;
    TM::Tile scoreTile(1, 0);
    TM::Tile msgTile(3, tileCount.y - 2);
    sf::Text score(std::to_string(snake.getSize() - 1), textFont);
    sf::Text message("", textFont);
    score.setPosition(map.tilesToPixel(scoreTile));
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

    std::cout << "Movement: WASD or Arrow keys\n"
                 "Rainbow : 1\n"
                 "Borders : 2\n"
                 "Pause   : P\n"
                 "Speed+  : Page Up\n"
                 "Speed-  : Page Down\n\n"
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

                /* Key release events */
                switch(event.key.code)
                {
                case sf::Keyboard::Num1:     //Toggles snake color
                    rainbowSnake = !rainbowSnake;
                    break;
                case sf::Keyboard::Num2:     //Toggles border
                    wrapAround = !wrapAround;
                    break;
                case sf::Keyboard::P:        //Stops the snake from moving
                    snake.setDirection(Snake::Direction::PAUSE);
                    break;
                case sf::Keyboard::F1:       //Toggles tile drawing
                    debugTileDraw = !debugTileDraw;
                    break;
                case sf::Keyboard::F2:       //Toggles tile mouse click
                    debugTileClick = !debugTileClick;
                    break;
                case sf::Keyboard::PageUp:   //Decrease time per tick
                    if(tickNumber - 5 >= MIN_TIME_PER_TICK)
                    {
                        tickNumber -= 5;
                        timePerTick = sf::milliseconds(tickNumber);
                    }
                    break;
                case sf::Keyboard::PageDown: //Increase time per tick
                    if(tickNumber + 5 <= MAX_TIME_PER_TICK)
                    {
                        tickNumber += 5;
                        timePerTick = sf::milliseconds(tickNumber);
                    }
                    break;
                default:
                    break;
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) or
               sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                snake.setDirection(Snake::Direction::UP);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) or
               sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                snake.setDirection(Snake::Direction::LEFT);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) or
               sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                snake.setDirection(Snake::Direction::DOWN);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) or
               sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
            message.setFillColor(sf::Color::Red);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and inputAllowed)
            {
                message.setString("");
                message.setFillColor(sf::Color::White);
                gameover = false;
                fruit.reset();
                snake.reset();
            }
        }
        else
        {
            /* Tick based actions */
            if(gameClock.getElapsedTime() >= timePerTick)
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
            score.setString(std::to_string(snake.getSize() - 1));
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
        window.draw(score);
        window.draw(message);
        window.display();
    }

    return 0;
}
