#include "Itembox.h"

Itembox::Itembox(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float high,int key) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = false;
	maxcol = imageCount.x;
	body.setSize(sf::Vector2f(70.0f, 70.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(1100.0f, 338.0f + high);
	body.setTexture(texture);
	this->point = point;
	this->key = key;
}

Itembox::~Itembox()
{

}

void Itembox::Update(float deltaTime)
{
	//sf::Vector2f movement(0.0f, 0.0f);
	velocity.x = -speed;


	animation.Update(0, maxcol, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Itembox::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Itembox::OnCollision(sf::Vector2f direction)
{
	//printf("%d %d\n", direction.x ,direction.y);
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;
	}
	else if (direction.y >= 0.0f)
	{
		velocity.y = 0.0f;
	}
}