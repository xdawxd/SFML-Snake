#include "RunningState.h"

RunningState::RunningState(GameState state, sf::RenderWindow& win, sf::Font& font) : State(state, win, font)
{
	dir = DOWN;
}

RunningState::~RunningState()
{
	delete snake;
	delete apple;
}

void RunningState::randomizeApplePosition()
{
	int posX = rand() % State::SCREEN_WIDTH;
	int posY = rand() % State::SCREEN_HEIGHT;

	applePosition = sf::Vector2f(posX, posY);

	apple->setPosition(posX, posY);
}

void RunningState::appleInit()
{
	apple->setTexture(texture);
	apple->setScale(sf::Vector2f(1.25, 1.25));
}

void RunningState::updateSnakePosition()
{
	if (dir == DOWN || dir == UP)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dir = LEFT;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dir = RIGHT;
	}
	else if (dir == LEFT || dir == RIGHT)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) dir = UP;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) dir = DOWN;
	}
	// fix a bug with the snake moving inside itself
}

void RunningState::snakeMove()
{
	int snakeSpeed = snake->getSpeed();

	int headX = snakeParts[0].getPosition().x;
	int headY = snakeParts[0].getPosition().y;

	if (dir == DOWN)
	{
		snakeParts[0].setPosition(headX, headY + snakeSpeed);
		snakeParts[0].setRotation(360.f);
	}
	if (dir == LEFT)
	{
		snakeParts[0].setPosition(headX - snakeSpeed, headY);
		snakeParts[0].setRotation(90.f);
	}
	if (dir == RIGHT)
	{
		snakeParts[0].setPosition(headX + snakeSpeed, headY);
		snakeParts[0].setRotation(270.f);
	}
	if (dir == UP)
	{
		snakeParts[0].setPosition(headX, headY - snakeSpeed);
		snakeParts[0].setRotation(180.f);
	}

	for (size_t i = 1; i < snakeParts.size(); ++i)
	{
		int bodyX = snakeParts[i].getPosition().x;
		int bodyY = snakeParts[i].getPosition().y;

		snakeParts[i].setPosition(sf::Vector2f(headX, headY));

		headX = bodyX;
		headY = bodyY;
	}
}

void RunningState::init()
{
	snake = new Snake(state);
	apple = new sf::Sprite();
	texture.loadFromFile("static/images/apple.png");

	snake->initSnake();
	snakeParts = snake->getSnake();
	appleInit();
	randomizeApplePosition();
	
	if (state == RUNNING_EASY) delay = 0.1;
	else if (state == RUNNING_NORMAL) delay = 0.08;
	else if (state == RUNNING_HARD) delay = 0.06;
}

void RunningState::update()
{
	sf::Time time = clock.getElapsedTime();

	if (time.asSeconds() >= delay)
	{
		snakeMove();
		clock.restart();
	}
}

GameState RunningState::handleEvents(sf::Event& event)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return END;
	}
	return state;
}

void RunningState::render()
{
	update();
	
	window->clear();

	window->draw(*apple);

	for (size_t i = 0; i < snakeParts.size(); ++i)
		window->draw(snakeParts[i]);
	
	updateSnakePosition();

	window->display();
}
