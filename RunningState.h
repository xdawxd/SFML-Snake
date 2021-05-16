#ifndef RUNNINGSTATE_H__
#define RUNNINGSTATE_H__

#include "Snake.h"
#include "State.h"

class RunningState : public State
{
public:
	RunningState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~RunningState();

private:
	Snake* snake;
	sf::CircleShape* apple;
	float delay;

	void randomizePosition();
public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
