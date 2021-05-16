#include "Snake.h"

Snake::Snake(sf::RenderWindow& window) : window(window)
{
	length = 3;
	speed = 20;
	fieldSize = 20;

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

		sprite.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f + 32 + i * 32));

		snake.push_back(sprite);
	}
}

Snake::~Snake()
{
}

void Snake::updatePosition()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dir = LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir = RIGHT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dir = UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dir = DOWN;

	for (size_t i = 0; i < snake.size(); ++i)
	{
		window.draw(snake[0]);
	}

}

void Snake::move()
{
	int headX = snake[0].getPosition().x;
	int headY = snake[0].getPosition().y;

	if (dir == DOWN)
	{
		snake[0].setPosition(headX, headY + speed);
		snake[0].setRotation(360.f);
	}
	if (dir == LEFT)
	{
		snake[0].setPosition(headX - speed, headY);
		snake[0].setRotation(90.f);
	}
	if (dir == RIGHT)
	{
		snake[0].setPosition(headX + speed, headY);
		snake[0].setRotation(270.f);
	}
	if (dir == UP)
	{
		snake[0].setPosition(headX, headY - speed);
		snake[0].setRotation(180.f);
	}

	for (size_t i = 1; i < snake.size(); ++i)
	{
		int bodyX = snake[i].getPosition().x;
		int bodyY = snake[i].getPosition().y;

		snake[i].setPosition(sf::Vector2f(headX, headY));

		headX = bodyX;
		headY = bodyY;
	}

	//addParts(headX, headY);
}

/*
void Snake::addParts(int headX, int headY)
{
	if (food.checkPosition(headX, headY))
	{
		length++;
		food.randomizePosition(fieldSize);
	}
}
*/