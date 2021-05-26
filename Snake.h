#ifndef SNAKE_H__
#define SNAKE_H__

#include "SFML/Graphics.hpp"
#include "State.h"
#include <vector>

class Snake
{
	std::vector<sf::Sprite> snake;
	GameState state;
	sf::Texture head;
	sf::Texture body;
	sf::Sprite sprite;
	int length;
	int speed;
	int fieldSize;

public:
	Snake(GameState state);
	~Snake();
	void initSnake();
	sf::Sprite newPart(sf::Vector2f pos);
	int getSpeed();
	int getLength();
	std::vector<sf::Sprite> getSnake();
};

#endif
