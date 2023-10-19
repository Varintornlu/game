#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Slide
{
public:
	Slide(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	void Update(float deltaTime, bool slide);
	void Draw(sf::RenderWindow& winndow);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	sf::RectangleShape body;
private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int maxcol;
	sf::Vector2f velocity;
	bool canJump;
	bool canSlide;
	float jumpHeight;
	float time;
};



