#ifndef GAME_H__
#define GAME_H__

#include "State.h"
#include "MenuState.h"
#include "RunningState.h"

class Game 
{
private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Font font;
	
	State* currentState;
	GameState gameState;

	void changeState();
	void handleState();

public:
	Game();
	~Game();
	void runGame();
};

#endif
