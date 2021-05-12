#include "MenuState.h"

MenuState::MenuState(GameState state, sf::RenderWindow& win, sf::Font& font) : State(state, win, font)
{
}

MenuState::~MenuState()
{
}

void MenuState::backgroundInit()
{
	if (!bgTexture.loadFromFile("static/images/gradient_2.jpg"))
	{
		std::cout << "ERROR: background not found!" << std::endl;
	}
	background.setTexture(bgTexture);
}

void MenuState::titleInit()
{	
	std::string titleStr = "SNAKE";

	title.setString(titleStr);
	title.setFont(*font);

	title.setFillColor(sf::Color(0, 80, 0));
	title.setCharacterSize(86);
	title.setOrigin(
		title.getGlobalBounds().left + title.getGlobalBounds().width / 2.0f,
		title.getGlobalBounds().top + title.getGlobalBounds().height / 2.0f
	);
	title.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 12.0f));
}

void MenuState::optionsInit()
{

}

void MenuState::init()
{
	backgroundInit();
	titleInit();
}

void MenuState::update()
{
	
}

GameState MenuState::handleEvents(sf::Event& event)
{
	GameState state = MENU;
	return state;
}


void MenuState::render()
{
	window->clear();

	window->draw(background);
	window->draw(title);

	window->display();
}
