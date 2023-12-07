#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Update(float dt, int windowHeight);
	void Render(sf::RenderWindow* _window);

	GameObject* CreateGameObject(const std::string& _name);

	GameObject* CreateDummyGameObject(const std::string& name, float x, float y, const sf::Color color);

private:
	std::vector<GameObject*> gameObjects;
};
