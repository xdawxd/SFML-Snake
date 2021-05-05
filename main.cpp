#include <iostream>

#include <SFML/Graphics.hpp>


int main()
{
    constexpr int screen_width = 800;
    constexpr int screen_height = 600;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sssnake");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            }
        }
    }
}
