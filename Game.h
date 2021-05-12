#ifndef GAME_H__
#define GAME_H__

#include "State.h"
#include "MenuState.h"
#include "RunningState.h"
#include "FinishState.h"
#include "EndState.h"

class Game 
{
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

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
