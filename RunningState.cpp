#include "RunningState.h"

RunningState::RunningState(GameState state, sf::RenderWindow& win, sf::Font& font) : State(state, win, font)
{
	dir = DOWN;
	applesEaten = 0;
}

RunningState::~RunningState()
{
	delete snake;
	delete apple;
}

void RunningState::drawHeader()
{
	sf::RectangleShape nav;
	nav.setFillColor(sf::Color(1, 26, 5, 128));
	nav.setSize(sf::Vector2f(State::SCREEN_WIDTH, State::SCREEN_HEIGHT / 14));

	sf::Text score;
	score.setFont(*font);
	score.setOrigin(
		score.getLocalBounds().left + score.getLocalBounds().width / 2.f,
		score.getLocalBounds().top + score.getLocalBounds().height / 2.f
	);
	score.setString(std::to_string(applesEaten));
	score.setPosition(sf::Vector2f(20, 3));

	sf::Text menu;
	menu.setFont(*font);
	menu.setOrigin(
		menu.getLocalBounds().left + menu.getLocalBounds().width / 2.f,
		menu.getLocalBounds().top + menu.getLocalBounds().height / 2.f
	);
	menu.setString("MENU");
	menu.setPosition(sf::Vector2f(State::SCREEN_WIDTH - 140, 3));


	window->draw(nav);
	window->draw(score);
	window->draw(menu);
}

void RunningState::appleInit()
{
	apple->setTexture(texture);
	apple->setScale(sf::Vector2f(1.25, 1.25));
	apple->setOrigin(
		apple->getLocalBounds().left + apple->getLocalBounds().width / 2.f,
		apple->getLocalBounds().top + apple->getLocalBounds().height / 2.f
	);
}

void RunningState::randomizeApplePosition()
{
	int fieldSize = 20;

	int posX = rand() % State::SCREEN_WIDTH - 20;
	int posY = rand() % State::SCREEN_HEIGHT - 20;

	int remainderX = posX % fieldSize;
	int remainderY = posY % fieldSize;


	int x = posX + fieldSize - remainderX;
	int y = posY + fieldSize - remainderY;

	applePosition = sf::Vector2f(x, y);

	apple->setPosition(x, y);
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

	if (checkAppleColision())
	{
		randomizeApplePosition();
		applesEaten++;
		snakeParts.push_back(snake->newPart(
			snakeParts.at(snakeParts.size() - 1).getPosition()
		));
	}

	if (isSelftColiding())
	{
		std::cout << "END" << std::endl;
	}
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
}

bool RunningState::checkAppleColision()
{
	if (snakeParts[0].getPosition() == applePosition)
		return true;
	return false;
}

bool RunningState::isSelftColiding() // TODO
{
	for (size_t i = 0; i < snakeParts.size(); ++i)
	{
		if (snakeParts[0].getPosition() == snakeParts[i].getPosition())
			return true;
	}
	return false;
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

	drawHeader();

	for (size_t i = 0; i < snakeParts.size(); ++i)
		window->draw(snakeParts[i]);
	
	updateSnakePosition();

	window->display();
}
