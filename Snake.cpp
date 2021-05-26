#include "Snake.h"

Snake::Snake(GameState state) : state(state)
{
	length = 3;
	speed = 20;
	fieldSize = 20;
}

Snake::~Snake()
{
}

void Snake::initSnake()
{
	for (int i = 0; i < length; ++i)
	{

		if (i == 0)
		{
			head.loadFromFile("static/images/head.png");
			sprite.setTexture(head);
		}
		else
		{
			body.loadFromFile("static/images/body.png");
			sprite.setTexture(body);
		}

		sprite.setOrigin(
			sprite.getLocalBounds().left + sprite.getLocalBounds().width / 2.f,
			sprite.getLocalBounds().top + sprite.getLocalBounds().height / 2.f
		);

		sprite.setPosition(sf::Vector2f(State::SCREEN_WIDTH / 2.f, State::SCREEN_HEIGHT / 2.f + 20 - i * 20));

		snake.push_back(sprite);
	}
}

int Snake::getSpeed()
{
	return speed;
}

int Snake::getLength()
{
	return length;
}

std::vector<sf::Sprite> Snake::getSnake()
{
	return snake;
}
