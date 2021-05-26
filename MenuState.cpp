#include "MenuState.h"

MenuState::MenuState(GameState state, sf::RenderWindow& win, sf::Font& font) : State(state, win, font)
{
}

MenuState::~MenuState()
{
}

void MenuState::backgroundInit()
{
	if (!bgTexture.loadFromFile("static/images/gradient.jpg"))
	{
		std::cout << "ERROR: background not found!" << std::endl;
	}
	background.setTexture(bgTexture);
}

void MenuState::titleInit()
{	
	title.setString("SNAKE");
	title.setFont(*font);

	title.setFillColor(sf::Color(0, 80, 0));
	title.setCharacterSize(86);
	title.setOrigin(
		title.getGlobalBounds().left + title.getGlobalBounds().width / 2.f,
		title.getGlobalBounds().top + title.getGlobalBounds().height / 2.f
	);
	title.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 12.f));
}

void MenuState::optionsInit()
{
	std::vector<std::string> options = {"EASY", "NORMAL", "HARD", "EXIT"};

	for (size_t i = 0; i < options.size(); ++i)
	{
		sf::Text diff;
		diff.setString(options[i]);
		diff.setFont(*font);
		diff.setCharacterSize(57);
		diff.setOrigin(diff.getGlobalBounds().width / 2.f, diff.getGlobalBounds().height / 2.f);
		diff.setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f - 76.f + 4.f * i * 22.f));

		if (options[i] == "EASY")
			diff.setFillColor(sf::Color(0, 120, 0));
		else if (options[i] == "NORMAL")
			diff.setFillColor(sf::Color(180, 180, 0));
		else if (options[i] == "HARD")
			diff.setFillColor(sf::Color(150, 0, 0));
		else
			diff.setFillColor(sf::Color(80, 80, 80));

		menuOptions.push_back(diff);
	}
}

void MenuState::init()
{
	backgroundInit();
	titleInit();
	optionsInit();
}

void MenuState::update()
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	for (size_t i = 0; i < menuOptions.size(); ++i)
	{
		if (menuOptions[i].getGlobalBounds().contains(mousePosition))
			menuOptions[i].setScale(1.1f, 1.1f);
		else
			menuOptions[i].setScale(1.f, 1.f);
	}
}

GameState MenuState::handleEvents(sf::Event& event)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::MouseButtonReleased && menuOptions[3].getGlobalBounds().contains(mousePosition)))
			return END;
		else if (event.type == sf::Event::MouseButtonReleased && menuOptions[0].getGlobalBounds().contains(mousePosition))
			return RUNNING_EASY;			
		else if (event.type == sf::Event::MouseButtonReleased && menuOptions[1].getGlobalBounds().contains(mousePosition))
			return RUNNING_NORMAL;
		else if (event.type == sf::Event::MouseButtonReleased && menuOptions[2].getGlobalBounds().contains(mousePosition))
			return RUNNING_HARD;
	}
	return state;
}


void MenuState::render()
{
	window->clear();

	window->draw(background);
	window->draw(title);
	
	for (size_t i = 0; i < menuOptions.size(); i++)
	{
		window->draw(menuOptions[i]);
	}

	window->display();
}
