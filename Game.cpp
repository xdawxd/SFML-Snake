#include "Game.h"

void Game::changeState()
{
	
	delete currentState;

	switch (gameState)
	{
	case MENU:
		currentState = new MenuState(MENU, window, font);
		break;
	case RUNNING_EASY:
		currentState = new RunningState(RUNNING_EASY, window, font);
		break;
	case RUNNING_NORMAL:
		currentState = new RunningState(RUNNING_NORMAL, window, font);
		break;
	case RUNNING_HARD:
		currentState = new RunningState(RUNNING_HARD, window, font);
		break;
	/*
	case FINISH:
		currentState = new FinishState(FINISH, window, font);
		break;
	*/
	}
	currentState->init();
}

void Game::handleState()
{
	gameState = currentState->handleEvents(event);
	currentState->update();
	currentState->render();

}

Game::Game() : gameState(MENU)
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sssnake");
	window.setFramerateLimit(60);
	window.clear();
	window.display();

	if (!font.loadFromFile("static/fonts/DarSkin-xRpr.ttf"))
	{
		std::cout << "ERROR: font not found!" << std::endl;
	}

	gameState = MENU;
}

Game::~Game()
{
}

void Game::runGame()
{
	currentState = new MenuState(MENU, window, font);
	currentState->init();
	
	while (gameState != END)
	{
		if (gameState != currentState->getGameState())
			changeState();

		handleState();
	}
	window.close();
}