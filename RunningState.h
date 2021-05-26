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
	sf::Text menu;
	sf::Clock clock;
	float delay;
	int applesEaten;
	Directions dir;
	std::vector<sf::Sprite> snakeParts;
	sf::Vector2f applePosition;

	void drawHeader();
	void drawBoard();
	void drawBackground();

	void appleInit();
	void randomizeApplePosition();

	void snakeMove();
	void updateSnakePosition();

	bool checkAppleColision();
	bool isSelftColiding();
	bool isHittingWall();
public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
