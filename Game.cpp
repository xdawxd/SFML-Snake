#include "Game.h"

void Game::changeState()
{
	switch (stateID)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void Game::handleState()
{

}

Game::Game() : stateID(MENU)
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Sssnake");
	window->setFramerateLimit(60);
	window->clear();
	window->display();

	// font handling...

}

Game::~Game()
{
}

void Game::runGame()
{
	
}