#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float high,float sizex, float sizey,int point) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = false;
	maxcol = imageCount.x;
	body.setSize(sf::Vector2f(sizex,sizey));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(1100.0f, 338.0f+high);
	body.setTexture(texture);
	this->point = point;
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	//sf::Vector2f movement(0.0f, 0.0f);
	velocity.x = -speed;

	
	animation.Update(0, maxcol, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemy::OnCollision(sf::Vector2f direction)
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