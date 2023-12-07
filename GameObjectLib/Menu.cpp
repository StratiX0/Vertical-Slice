#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window) {
    if (!font.loadFromFile("arial.ttf")) {
        // G�rez l'erreur si la police ne peut pas �tre charg�e
    }

    playText.setFont(font);
    playText.setString("Jouer");
    playText.setCharacterSize(50);
    playText.setFillColor(sf::Color::Red);
    playText.setPosition(250, 200);

    quitText.setFont(font);
    quitText.setString("Options");
    quitText.setCharacterSize(50);
    quitText.setFillColor(sf::Color::Blue);
    quitText.setPosition(250, 300);

    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(50);
    quitText.setFillColor(sf::Color::Green);
    quitText.setPosition(250, 300);
}

Menu::~Menu() {
    // Lib�rez les ressources si n�cessaire
}

int Menu::run() {
    while (window.isOpen()) {
        handleInput();
        draw();
    }

    // Retournez la s�lection du joueur (0 pour Quitter, 1 pour Jouer, par exemple)
    return 0; // Mettez la valeur appropri�e
}

void Menu::draw() {
    window.clear();

    // Dessinez tous les �l�ments du menu
    window.draw(playText);
    window.draw(quitText);

    window.display();
}

void Menu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (playText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                // Le joueur a cliqu� sur "Jouer"
                // Vous pouvez ex�cuter l'action de d�marrage du jeu ici
            }
            else if (quitText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                window.close();
            }
        }
    }
}
