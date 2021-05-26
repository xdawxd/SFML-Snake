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

	sf::Text menu;
	menu.setFont(*font);
	menu.setOrigin(
		menu.getLocalBounds().left + menu.getLocalBounds().width / 2.f,
		menu.getLocalBounds().top + menu.getLocalBounds().height / 2.f
	);
	menu.setString("MENU");
	menu.setPosition(sf::Vector2f(State::SCREEN_WIDTH - 140, 3));

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
	window->draw(menu);
}

void RunningState::drawBoard()
{
	sf::RectangleShape board;
	board.setSize(sf::Vector2f(State::SCREEN_WIDTH / 1.2, State::SCREEN_HEIGHT / 1.2));
	board.setOrigin(
		board.getLocalBounds().left + board.getLocalBounds().width / 2.f,
		board.getLocalBounds().top + board.getLocalBounds().height / 2.f
	);
	board.setFillColor(sf::Color(0, 117, 20));
	board.setPosition(sf::Vector2f(State::SCREEN_WIDTH / 2, State::SCREEN_HEIGHT / 2));
	board.setOutlineColor(sf::Color(1, 66, 12));
	board.setOutlineThickness(5);

	window->draw(board);
}

void RunningState::drawBackground()
{
	sf::Sprite background;
	sf::Texture texture;
	texture.loadFromFile("static/images/gradient.jpg");
	background.setTexture(texture);

	window->draw(background);
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
	/* TODO
	if (menu.getGlobalBounds().contains(mousePosition)) 
		menu.setScale(1.1f, 1.1f);
	else
		menu.setScale(1.f, 1.f);
	*/
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
		else if (isSelftColiding() || isHittingWall())
			return MENU;
		//else if (event.type == sf::Event::MouseButtonReleased && menu.getGlobalBounds().contains(mousePosition))
			//return MENU;
	}
	return state;
}

void RunningState::render()
{
	update();
	
	window->clear(); // sf::Color(1, 87, 15, 128)

	drawBackground();
	drawBoard();
	window->draw(*apple);
	drawHeader();

	for (size_t i = 0; i < snakeParts.size(); ++i)
		window->draw(snakeParts[i]);
	
	updateSnakePosition();

	window->display();
}
