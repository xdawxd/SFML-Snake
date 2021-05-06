#ifndef MENUSTATE_H__
#define MENUSTATE_H__

#include "State.h"

class MenuState : public State
{
public:
	MenuState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~MenuState();

private:


public:
	virtual void init() override;
	virtual void update() override;
	virtual void handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
