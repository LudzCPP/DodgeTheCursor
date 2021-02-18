#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "target.h"

int main()
{
    srand(time(NULL));

    unsigned int screenWidth = 1920;
    unsigned int screenHeight = 1080;
    float size = 50;
    bool agreement = false, playing = false;
    int score = 0;

    sf::RectangleShape point;
    std::vector <target> squares;
    sf::Mouse mouse;
    sf::Vector2i mpos;
    sf::Vector2f ppos;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Dodge The Cursor", sf::Style::Fullscreen);

    sf::Font font;
    font.loadFromFile("01_tama.TTF");

    sf::Text text;
    text.setFont(font);
    text.setString("Press Enter to start!");
    text.setCharacterSize(50);

    sf::Clock clock;
    float timer = 0, delay = 5;

    while (window.isOpen())
    {   
        float randx = rand() % 1520 + 200;
        float randy = rand() % 680 + 200;

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (!playing)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        score = 0;
                        timer = 0;
                        agreement = true;
                        playing = true;

                        target square(size, randx, randy);

                        squares.push_back(square);

                        agreement = true;

                        text.setString("Score: 0");

                        point.setFillColor(sf::Color::Yellow);
                        point.setPosition(randx, randy);
                        point.setSize(sf::Vector2f(size, size));
                    }
                }

                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    ppos = point.getPosition();
                    if ((ppos.x <= event.mouseButton.x) && (event.mouseButton.x <= (ppos.x + size)))
                        if ((ppos.y <= event.mouseButton.y) && (event.mouseButton.y <= (ppos.y + size)))
                        {
                            score++;

                            std::ostringstream ss2;
                            ss2 << "Score: " << score;
                            text.setString(ss2.str());

                            point.setPosition(randx, randy);
                        }
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (agreement)
        {
            for (size_t i = 0; i < squares.size(); i++)
            {
                if (((squares[i].x == 0) || (squares[i].x == 1870)))
                    squares[i].dirx *= -1;

                if (((squares[i].y == 0) || (squares[i].y == 1030)))
                    squares[i].diry *= -1;

                squares[i].move();

                mpos = mouse.getPosition();

                if ((squares[i].x < mpos.x) && (mpos.x < squares[i].x + size))
                    if ((squares[i].y < mpos.y) && (mpos.y < (squares[i].y + size)))
                    {
                        std::ostringstream ss1;
                        ss1 << "You lost! Your score is " << score << ". " << std::endl << "Press Enter to start again!";
                        text.setString(ss1.str());
                        point.setSize(sf::Vector2f(0, 0));
                        agreement = false;
                        playing = false;
                        squares.clear();
                    }
            }
          
            if (timer > delay)
            {
                timer = 0;
                score++;

                std::ostringstream ss;
                ss << "Score: " << score;
                text.setString(ss.str());
                
                target square(size, randx, randy);

                squares.push_back(square);
            } 
        }

        window.clear();

        for (size_t i = 0; i < squares.size(); i++)
        {
            squares[i].draw(window);
        }
        
        window.draw(text);
        window.draw(point);
        window.display();
    }

    return 0;
}