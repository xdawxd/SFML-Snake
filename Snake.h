#ifndef SNAKE_H__
#define SNAKE_H__

#include "SFML/Graphics.hpp"
#include <vector>

enum Directions {LEFT, RIGHT, UP, DOWN};

class Snake
{
	std::vector<sf::Sprite> snake;
	sf::RenderWindow& window;
	sf::Texture head;
	sf::Texture body;
	sf::Sprite sprite;
	Directions dir;
	int length;
	int speed;
	int fieldSize;

public:
	Snake(sf::RenderWindow& window);
	~Snake();
	void updatePosition();
	void move();
	//void addParts(int headX, int headY);
};

#endif
