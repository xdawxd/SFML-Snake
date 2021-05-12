#ifndef FINISHSTATE_H__
#define FINISHSTATE_H__

#include "State.h"

class FinishState : public State
{
public:
	FinishState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~FinishState();

private:


public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
