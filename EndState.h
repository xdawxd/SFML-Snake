#ifndef ENDSTATE_H__
#define ENDSTATE_H__

#include "State.h"

class EndState : public State
{
public:
	EndState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~EndState();

private:


public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
