#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float high, float sizex, float sizey, int point);
	~Enemy();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& winndow);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape body;
	int point;
private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int maxcol;
	sf::Vector2f velocity;
};


