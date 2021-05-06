#ifndef STATE_H__
#define STATE_H__

#include "SFML/Graphics.hpp"

enum GameState { MENU, RUNNING, FINISH, END} ;

class State
{
public:
	State(GameState state, sf::RenderWindow& win, sf::Font& font);
	virtual ~State();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void handleEvents(sf::Event& event) = 0;
	virtual void render() = 0;

	GameState getGameState();

protected:
	// attempt to set a default font and store it in a pointer variable
	sf::Font* font;
	sf::RenderWindow* window;
	const GameState state;
};

#endif
