#include "Slide.h"

Slide::Slide(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	canSlide = true;
	time = 0;
	row = 0;
	faceRight = true;
	maxcol = 2;
	body.setSize(sf::Vector2f(150.0f, 120.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(356.0f, 1000.0f);
	body.setTexture(texture);
}



void Slide::Update(float deltaTime,bool slidein)
{
	//sf::Vector2f movement(0.0f, 0.0f);
	if (canSlide == false)
	{
		this->time += deltaTime;
		if (this->time > 0.1)
		{
			canSlide = true;
			time = 0;
			this->body.setPosition(this->body.getPosition().x, 5000);
		}
	}

	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && body.getPosition().x >= 80)
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && body.getPosition().x <= 944)
		velocity.x += speed;
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		velocity.y -= speed ;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		velocity.y += speed ;*/
	if (velocity.x == 0.0f)
	{
		row = 0;
		maxcol = 2;
	}
	else
	{
		row = 0;
		maxcol = 2;
		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}
	if (!slidein && canSlide)
	{
		canSlide = false;
		this->body.setPosition(this->body.getPosition().x, 342.0f);
		//square root (2.0f * gravity * jumpHeight);
	}

	animation.Update(row, maxcol, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Slide::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Slide::OnCollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y >= 0.0f)
	{
		velocity.y = 0.0f;
	}
}