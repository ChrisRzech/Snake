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
    if(!icon.loadFromFile("res/icon.png"))
    {
        std::cout << "\"res/icon.png\" failed to load, aborting";
        return -1;
    }

    /* Window settings */
    sf::Vector2u screenSize(800, 600);
    sf::Vector2u gameSize(600, 600);
    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Snake", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    /* Internal clock */
    sf::Clock gameClock;
    const sf::Time MIN_TICK_FREQ = sf::milliseconds(40);
    const sf::Time INITIAL_TICK_FREQ = sf::milliseconds(100);
    const sf::Time TICK_FREQ_INTERVAL = sf::milliseconds(5);
    sf::Time tickFreq = INITIAL_TICK_FREQ;

    /* Gamepieces */
    sf::Vector2u tileCount(20, 20);
    TM::Map map(gameSize, tileCount);
    Snake::Snake snake(map, sf::Color::Green);
    Snake::Fruit fruit(map, sf::Color::White);

    /* Text */
    const unsigned int FONT_SIZE = 20;
    sf::Font textFont;
    if(!textFont.loadFromFile("res/bit5x3.ttf"))
    {
        std::cout << "\"res/bit5x3.ttf\" failed to load, aborting";
        return -1;
    }

    TM::Tile msgTile(0, 0);
    TM::Tile scoreTile(tileCount.x + 1, 0);
    TM::Tile borderTile(tileCount.x + 1, 2);

    sf::Text deathText("Dead, press space to restart", textFont, FONT_SIZE);
    sf::Text scoreText("", textFont, FONT_SIZE);
    sf::Text borderText("", textFont, FONT_SIZE);

    deathText.setFillColor(sf::Color::Red);
    deathText.setPosition(map.tilesToPixel(msgTile));
    scoreText.setPosition(map.tilesToPixel(scoreTile));
    borderText.setPosition(map.tilesToPixel(borderTile));

    /* Game-text border */
    sf::RectangleShape gameTextBorder(sf::Vector2f(1, gameSize.y));
    gameTextBorder.setPosition(gameSize.x, 0);
    gameTextBorder.setFillColor(sf::Color::White);

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
    bool borders      = true;
    bool rainbow      = false;

    std::cout << "Movement: WASD or Arrow keys\n"
                 "Rainbow : 1\n"
                 "Borders : 2\n"
                 "Pause   : P\n\n"
                 "Settings\n"
                 "Window Size: " << screenSize.x << 'x' << screenSize.y << "\n"
                 "Game Size  : " << gameSize.x   << 'x' << gameSize.y   << "\n"
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
                snake.setDirection(Snake::Direction::PAUSE);
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
                    rainbow = !rainbow;
                    break;
                case sf::Keyboard::Num2:     //Toggles border
                    borders = !borders;
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

            /* Speed increase */
            if(tickFreq - TICK_FREQ_INTERVAL >= MIN_TICK_FREQ and (snake.getSize() - 1) % 5 == 0)
                tickFreq -= sf::milliseconds(5);
        }

        /* Handle gameover state */
        if(gameover)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and inputAllowed)
            {
                gameover = false;
                fruit.reset();
                snake.reset();
                tickFreq = INITIAL_TICK_FREQ;
            }
        }
        else
        {
            /* Tick based actions */
            if(gameClock.getElapsedTime() >= tickFreq)
            {
                gameClock.restart();

                /* Snake color */
                if(rainbow)
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

            /* Border handling */
            if(borders)
            {
                if(!map.isInBounds(snake.getPosition()))
                {
                    gameover = true;
                }
            }
            else
            {
                if(snake.getPosition().tilePos().x < 0)
                {
                    TM::Tile newTile(map.getTileCount().x - 1, snake.getPosition().tilePos().y);
                    snake.setPosition(newTile);
                }
                else if(snake.getPosition().tilePos().x >= static_cast<int>(map.getTileCount().x))
                {
                    TM::Tile newTile(0, snake.getPosition().tilePos().y);
                    snake.setPosition(newTile);
                }
                else if(snake.getPosition().tilePos().y < 0)
                {
                    TM::Tile newTile(snake.getPosition().tilePos().x, map.getTileCount().y - 1);
                    snake.setPosition(newTile);
                }
                else if(snake.getPosition().tilePos().y >= static_cast<int>(map.getTileCount().y))
                {
                    TM::Tile newTile(snake.getPosition().tilePos().x, 0);
                    snake.setPosition(newTile);
                }
            }
        }

        /* Text updates */
        scoreText.setString("Score: " + std::to_string(snake.getSize() - 1));
        borderText.setString(static_cast<std::string>("Borders: ") + static_cast<std::string>((borders ? "On" : "Off")));

        /* Drawing */
        window.clear();
        if(debugTileDraw)
            map.drawTiles(window, sf::Color::Transparent, sf::Color::White);
        snake.draw(window);
        fruit.draw(window);
        window.draw(gameTextBorder);
        if(gameover)
            window.draw(deathText);
        window.draw(scoreText);
        window.draw(borderText);
        window.display();
    }

    return 0;
}
