#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Itembox
{
public:
	Itembox(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float high,int key);
	~Itembox();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& winndow);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape body;
	int point;
	int key;
private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int maxcol;
	sf::Vector2f velocity;
};


