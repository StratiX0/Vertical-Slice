#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameObject.h"
#include "Scene.h"

int main()
{
    Scene scene;

    GameObject* player = scene.CreateDummyGameObject("Player", 200.f, 700.f, sf::Color::Red);

    GameObject* enemy = scene.CreateDummyGameObject("Enemy", 400.f, 500.f, sf::Color::Blue);

    int windowWidth = 1600;
    int windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Engine");

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::D)
                    player->SetMoveRight(true);
                else if (event.key.code == sf::Keyboard::Q)
                    player->SetMoveLeft(true);
                else if (event.key.code == sf::Keyboard::Z)
                    player->Jump(); // Appel à la fonction de saut
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::D)
                    player->SetMoveRight(false);
                else if (event.key.code == sf::Keyboard::Q)
                    player->SetMoveLeft(false);
            }
        }

        float dt = clock.restart().asSeconds();

        scene.Update(dt, windowHeight);

        window.clear(sf::Color::Black);
        scene.Render(&window);
        window.display();
    }


    return 0;
}