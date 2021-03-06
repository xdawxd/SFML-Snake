#ifndef RUNNINGSTATE_H__
#define RUNNINGSTATE_H__

#include "Snake.h"
#include "State.h"

#include <Windows.h>

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
	sf::RectangleShape nav;
	sf::RectangleShape board;
	float delay;
	int applesEaten;
	Directions dir;
	std::vector<sf::Sprite> snakeParts;
	sf::Vector2f applePosition;

	void drawHeader();
	void drawBoard();

	void appleInit();
	void randomizeApplePosition();

	void snakeMove();
	void updateSnakePosition();

	bool checkAppleColision();
	bool isSelftColiding();
	bool isHittingWall();

	void drawWin();
	void drawLose();
public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
