#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Components/ShapeRenderer.h"
#include "Components/SquareCollider.h"

void Scene::Update(float dt, int windowHeight)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Update(dt, windowHeight);
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	auto gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObjects.push_back(gameObject);
	return gameObject;
}

GameObject* Scene::CreateDummyGameObject(const std::string& name, float x, float y, const sf::Color color)
{
	GameObject* gameObject = CreateGameObject(name);
	gameObject->SetPosition(Maths::Vector2f(x, y));

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidth(20.f);
	squareCollider->SetHeight(20.f);

	ShapeRenderer* shapeRenderer = gameObject->CreateComponent<ShapeRenderer>();
	shapeRenderer->SetColor(color);

	return gameObject;
}
