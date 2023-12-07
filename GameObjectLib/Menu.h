#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    ~Menu();

    int run();

private:
    void draw();
    void handleInput();

    sf::RenderWindow& window;
    sf::Font font;
    sf::Text playText;
    sf::Text quitText;
};

