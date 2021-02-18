#pragma once
#include <SFML/Graphics.hpp>

class target
{
public:

	float x, y;
	float dirx, diry;
	float size;


	void draw(sf::RenderWindow&);
	void move();
	target(float, float, float);
};

