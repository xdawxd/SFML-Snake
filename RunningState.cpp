#include "RunningState.h"

RunningState::RunningState(GameState state, sf::RenderWindow& win, sf::Font& font) : State(state, win, font)
{
}

RunningState::~RunningState()
{
	delete snake;
	delete apple;
}

void RunningState::randomizePosition()
{
	
}

void RunningState::init()
{
	snake = new Snake(*window);
	apple = new sf::CircleShape();

	switch (state)
	{
	case RUNNING_EASY:
		delay = 0.1;
		break;
	case RUNNING_NORMAL:
		delay = 0.8;
		break;
	case RUNNING_HARD:
		delay = 0.5;
		break;
	}
}

void RunningState::update()
{

}

GameState RunningState::handleEvents(sf::Event& event)
{
	GameState state = RUNNING_EASY;
	return state;
}

void RunningState::render()
{
	sf::Clock clock;

	sf::Time time = clock.getElapsedTime();

	if (time.asSeconds() >= delay)
	{
		snake->move();
		clock.restart();
	}

	window->clear();

	snake->updatePosition();

	window->display();
}
