#include "Game.h"

int main()
{
	Game game;
	game.runGame();
}

/*
#include "SFML/Graphics.hpp"

#include "Snake.h"

#include <iostream>
#include <vector>


class Food
{
	sf::RenderWindow& window;
	sf::CircleShape foodObj;

	int posX;
	int posY;

public:
	Food(sf::RenderWindow& window);
	~Food();
	void randomizePosition();
	bool checkPosition(int posX, int posY);

};

// ---------------------------------------------

Food::Food(sf::RenderWindow& window) : window(window)
{
	foodObj.setFillColor(sf::Color::Green);
	foodObj.setRadius(8);
	foodObj.setOrigin(
		foodObj.getGlobalBounds().left + foodObj.getGlobalBounds().width / 2.0f,
		foodObj.getGlobalBounds().top + foodObj.getGlobalBounds().height / 2.0f
	);
	randomizePosition();

}

Food::~Food()
{
}

void Food::randomizePosition()
{
	int fieldSize = 16;
	posX = rand() & window.getSize().x;
	posY = rand() & window.getSize().y;

	int remainderX = posX % fieldSize;
	int remainderY = posY % fieldSize;

	int x = posX + fieldSize - remainderX;
	int y = posY + fieldSize - remainderY;

	foodObj.setPosition(sf::Vector2f(x, y));
	window.draw(foodObj);
}

bool Food::checkPosition(int headX, int headY)
{
	if (posX == headX && posY == headY)
		return true;
	return false;
}

// ---------------------------------------------

int main()
{
	srand(time(nullptr));

	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;

	float timer = 0, delay = 0.1;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake");
	window.setFramerateLimit(60);

	Food food(window);
	Snake snake(window);
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time time = clock.getElapsedTime();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (time.asSeconds() >= delay)
		{
			snake.move();
			clock.restart();
		}

		window.clear();

		snake.updatePosition();

		window.display();
	}
	return 0;
}
*/
