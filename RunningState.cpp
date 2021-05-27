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
	nav.setFillColor(sf::Color(1, 66, 12));
	nav.setSize(sf::Vector2f(State::SCREEN_WIDTH, State::SCREEN_HEIGHT / 12));

	sf::Text score;
	score.setFont(*font);
	score.setOrigin(
		score.getLocalBounds().left + score.getLocalBounds().width / 2.f,
		score.getLocalBounds().top + score.getLocalBounds().height / 2.f
	);
	score.setString(std::to_string(applesEaten));
	score.setPosition(sf::Vector2f(80, 6));

	sf::Sprite appleScore;
	sf::Texture texture;
	texture.loadFromFile("static/images/apple_nav.png");
	appleScore.setTexture(texture);
	appleScore.setOrigin(
		appleScore.getLocalBounds().left + appleScore.getLocalBounds().width / 2.f,
		appleScore.getLocalBounds().top + appleScore.getLocalBounds().height / 2.f
	);
	appleScore.setPosition(score.getPosition().x - 20, score.getPosition().y + 15);
	appleScore.setScale(sf::Vector2f(2, 2));

	window->draw(nav);
	window->draw(score);
	window->draw(appleScore);
}

void RunningState::drawBoard()
{
	board.setSize(sf::Vector2f(State::SCREEN_WIDTH / 1.2, State::SCREEN_HEIGHT / 1.2));
	board.setOrigin(
		board.getLocalBounds().left + board.getLocalBounds().width / 2.f,
		board.getLocalBounds().top + board.getLocalBounds().height / 2.f
	);
	board.setFillColor(sf::Color(0, 120, 0));
	board.setPosition(sf::Vector2f(State::SCREEN_WIDTH / 2, State::SCREEN_HEIGHT / 2));
	board.setOutlineColor(sf::Color(1, 66, 12));
	board.setOutlineThickness(5);

	window->draw(board);
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

	int leftRight = State::SCREEN_WIDTH - State::SCREEN_WIDTH / 1.2;
	int upDown = State::SCREEN_HEIGHT - State::SCREEN_HEIGHT / 1.2;

	int posX = (rand() % static_cast<int>(State::SCREEN_WIDTH - leftRight * 2)) + leftRight;
	int posY = (rand() % static_cast<int>(State::SCREEN_HEIGHT - upDown * 2)) + upDown;

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
	/*
	int snakeSpeed = snake->getSpeed();
	if (snakeParts[0].getPosition().x + snakeSpeed > board.getLocalBounds().width) // right
	{

	}
	if (snakeParts[0].getPosition().y - snakeSpeed < 0) // left
	{

	}
	if (snakeParts[0].getPosition().y - snakeSpeed < nav.getLocalBounds().height) // ended here
	{

	}
	*/
	if (checkAppleColision())
	{
		randomizeApplePosition();
		applesEaten++;
		snakeParts.push_back(snake->newPart(
			snakeParts.at(snakeParts.size() - 1).getPosition()
		));
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

bool RunningState::isSelftColiding() // FIX THIS
{
	for (size_t i = 1; i < snakeParts.size(); ++i)
	{
		if (snakeParts[0].getPosition() == snakeParts[i].getPosition())
			return true;
	}
	return false;
}

bool RunningState::isHittingWall()
{
	sf::Sprite head = snakeParts[0];
	if (head.getPosition().x >= 733 || head.getPosition().x <= 67)
		return true;
	if (head.getPosition().y >= 550 || head.getPosition().y <= 49)
		return true;
	return false;
		
}

void RunningState::drawWin()
{
	sf::Text winnerText;
	winnerText.setOrigin(
		winnerText.getLocalBounds().left + winnerText.getLocalBounds().width / 2.f,
		winnerText.getLocalBounds().top + winnerText.getLocalBounds().height / 2.f
	);
	winnerText.setString("You Won!");
	winnerText.setCharacterSize(96);
	winnerText.setFillColor(sf::Color(0, 120, 0));
	winnerText.setOutlineColor(sf::Color::Black);
	winnerText.setOutlineThickness(4);

	window->draw(winnerText);
}

void RunningState::drawLose()
{
	sf::Text loseText;
	loseText.setOrigin(
		loseText.getLocalBounds().left + loseText.getLocalBounds().width / 2.f,
		loseText.getLocalBounds().top + loseText.getLocalBounds().height / 2.f
	);
	loseText.setString("You Lost!");
	loseText.setCharacterSize(96);
	loseText.setFillColor(sf::Color(120, 0, 0));
	loseText.setOutlineColor(sf::Color::Black);
	loseText.setOutlineThickness(4);
	loseText.setPosition(sf::Vector2f(State::SCREEN_WIDTH / 2, State::SCREEN_HEIGHT / 2));

	window->draw(loseText);
}

void RunningState::init()
{
	snake = new Snake(state);
	apple = new sf::Sprite();
	texture.loadFromFile("static/images/apple_bg.png");

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
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
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
		if (isSelftColiding() || isHittingWall())
			return MENU;
	}
	return state;
}

void RunningState::render()
{
	update();
	
	window->clear(sf::Color(0, 32, 0, 128));

	drawBoard();
	window->draw(*apple);
	drawHeader();

	for (size_t i = 0; i < snakeParts.size(); ++i)
		window->draw(snakeParts[i]);
	
	updateSnakePosition();



	window->display();
}
