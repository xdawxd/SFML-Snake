#ifndef MENUSTATE_H__
#define MENUSTATE_H__

#include "State.h"

class MenuState : public State
{
public:
	MenuState(GameState state, sf::RenderWindow& win, sf::Font& font);
	~MenuState();

private:
	void backgroundInit();
	void titleInit();
	void optionsInit();

	sf::Texture bgTexture;
	sf::Sprite background;
	sf::Text title;
	std::vector<sf::Text> menuOptions;

public:
	virtual void init() override;
	virtual void update() override;
	virtual GameState handleEvents(sf::Event& event) override;
	virtual void render() override;

};

#endif
