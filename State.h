#ifndef STATE_H__
#define STATE_H__

#include "SFML/Graphics.hpp"

#include <iostream>
#include <string>
#include <vector>

/*
* MENU - Start of the game -> displaying menu
* RUNNING - Game running -> displaying the gameplay
* FINISH - Player lost/won the game -> displaying you lost/won
* END - Game ended -> display "Do want to play again?"
* if END statement == true:
* END -> RUNNING | difficulty stays the same
* else:
* END -> MENU
*/

enum GameState { MENU, RUNNING, FINISH, END };


class State
{
public:
	State(GameState state, sf::RenderWindow& win, sf::Font& font);
	virtual ~State();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual GameState handleEvents(sf::Event& event) = 0;
	virtual void render() = 0;

	GameState getGameState() const;

protected:
	// attempt to set a default font and store it in a pointer variable
	sf::Font* font;
	sf::RenderWindow* window;
	const GameState state;
};

#endif