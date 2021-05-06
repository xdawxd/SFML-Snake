#include "State.h"

State::State(GameState state, sf::RenderWindow& win, sf::Font& font) : state(state), window(&win), font(&font)
{
}

State::~State()
{
}

GameState State::getGameState()
{
	return state;
}
