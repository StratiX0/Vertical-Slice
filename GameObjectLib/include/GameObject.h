#pragma once
#include <string>
#include <vector>

#include "Maths/Vector2.h"
#include "Components/Component.h"

class Component;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	std::string GetName() const { return name; }
	Maths::Vector2<float> GetPosition() const { return position; }

	void SetName(const std::string& _name) { name = _name; }
	void SetPosition(const Maths::Vector2<float>& _position) { position = _position; }

	void AddComponent(Component* _component);

	template<typename T>
	T* CreateComponent()
	{
		T* component = new T();
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	void SetVelocity(const Maths::Vector2f& _velocity)
	{
		velocity = _velocity;
	}

	void Move(const Maths::Vector2f& offset)
	{
		position += offset;
	}

	void SetMoveRight(bool state)
	{
		moveRight = state;
		UpdateVelocity();
	}

	void SetMoveLeft(bool state)
	{
		moveLeft = state;
		UpdateVelocity();
	}

	void SetMoveUp(bool state)
	{
		moveUp = state;
		UpdateVelocity();
	}

	void SetMoveDown(bool state)
	{
		moveDown = state;
		UpdateVelocity();
	}

	void UpdateVelocity()
	{
		float horizontalVelocity = (moveRight ? 10.f : 0.f) - (moveLeft ? 10.f : 0.f);
		velocity.x = horizontalVelocity * 100.f;

		// Ne modifiez la vélocité verticale que si le saut n'est pas en cours
		if (!isJumping)
		{
			float verticalVelocity = (moveDown ? 1.f : 0.f) - (moveUp ? 1.f : 0.f);
			velocity.y = verticalVelocity * 100.f;
		}

		// Si aucune touche de mouvement n'est enfoncée, réinitialisez la vélocité à zéro
		if (!moveRight && !moveLeft && !moveDown && !moveUp)
		{
			velocity = Maths::Vector2f(0.f, velocity.y);
		}
	}


	void Jump()
	{
		// Vérifier si l'objet est au sol et ne saute pas déjà
		if (isGrounded && !isJumping)
		{
			velocity.y = -jumpSpeed; // Ajustez la valeur en fonction de la hauteur du saut souhaitée
			isGrounded = false; // Marquer l'objet comme étant en l'air après le saut
			isJumping = true; // Indiquer que le saut est en cours
		}
	}


	void SetGrounded(bool grounded)
	{
		isGrounded = grounded;
	}

	void SetGravity(float value)
	{
		gravity = value;
	}

	void Update(float dt, int windowHeight)
	{
		// Appliquer la gravité
		velocity.y += gravity * dt;

		// Mise à jour de la position en fonction de la vélocité
		position += velocity * dt;

		// Mise à jour de isGrounded (l'objet est au sol si sa position est en bas de la fenêtre)
		isGrounded = (position.y >= windowHeight - 100.f); // Assurez-vous d'ajuster en fonction de la taille de votre objet

		// Réinitialiser isJumping si l'objet est au sol
		if (isGrounded)
		{
			position.y = windowHeight - 100.f; // Ajustez la position pour rester au sol
			velocity.y = 0.0f; // Arrêter le mouvement vertical lorsque l'objet est au sol
			isJumping = false; // Réinitialiser l'état de saut
		}


		// Restreindre la vitesse de chute maximale
		if (velocity.y > maxFallSpeed)
		{
			velocity.y = maxFallSpeed;
		}

		// Restreindre la vitesse horizontale
		if (velocity.x > maxHorizontalSpeed)
		{
			velocity.x = maxHorizontalSpeed;
		}
		else if (velocity.x < -maxHorizontalSpeed)
		{
			velocity.x = -maxHorizontalSpeed;
		}
	}

	void RemoveComponent(Component* _component);
	void Update(float dt, int windowHeight) const;
	void Render(sf::RenderWindow* _window) const;

private:
	std::string name = "GameObject";
	Maths::Vector2<float> position = Maths::Vector2f::Zero;
	std::vector<Component*> components;
	Maths::Vector2f velocity;
	bool moveRight;
	bool moveLeft;
	bool moveUp;
	bool moveDown;
	bool isJumping;
	bool isGrounded; // Ajouter une variable pour suivre si l'objet est au sol
	float groundLevel; // Ajouter la position du sol (ajuster en fonction de votre jeu)
	float gravity = 500.0f;          // Ajustez la valeur en fonction de la gravité souhaitée
	float jumpSpeed = 200.0f;        // Ajustez la valeur en fonction de la vitesse de saut souhaitée
	float maxFallSpeed = 500.0f;      // Ajustez la valeur en fonction de la vitesse maximale de chute souhaitée
	float maxHorizontalSpeed = 200.0f; // Ajustez la valeur en fonction de la vitesse horizontale maximale souhaitée
};
