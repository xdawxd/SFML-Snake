#ifndef RUNNINGSTATE_H__
#define RUNNINGSTATE_H__

#include "Snake.h"
#include "State.h"

enum Directions { LEFT, RIGHT, UP, DOWN };

class RunningState : public State
{
public:
	RunningState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~RunningState();

private:
	Snake* snake;
	sf::Texture texture;
	sf::Sprite* apple;
	sf::Clock clock;
	float delay;
	Directions dir;
	std::vector<sf::Sprite> snakeParts;
	sf::Vector2f applePosition;

	void randomizeApplePosition();
	void appleInit();
	void updateSnakePosition();
	void snakeMove();
public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
