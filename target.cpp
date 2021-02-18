#include "target.h"
#include <SFML/Graphics.hpp>

target::target(float s, float posx, float posy)
{
	size = s;
	x = posx;
	y = posy;
	dirx = -0.5;
	diry = -0.5;
}

void target::draw(sf::RenderWindow &window)
{
	sf::RectangleShape square(sf::Vector2f(size, size));
	square.setPosition(sf::Vector2f(x, y));

	window.draw(square);
}

void target::move()
{
	x += dirx;
	y += diry;
}
