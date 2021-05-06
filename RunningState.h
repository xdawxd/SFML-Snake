#ifndef RUNNINGSTATE_H__
#define RUNNINGTATE_H__

#include "State.h"

class RunningState : public State
{
public:
	RunningState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~RunningState();

private:


public:
	virtual void init() override;
	virtual void update() override;
	virtual void handleEvents(sf::Event& event) override;
	virtual void render() override;

};


#endif
