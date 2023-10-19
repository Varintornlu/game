#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed , float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;
	maxcol = 0;
	body.setSize(sf::Vector2f(120.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(356.0f, 240.0f);
	body.setTexture(texture);
	time = 0;
}

Player::~Player()
{

}

void Player::Update(float deltaTime)
{
	if (canSlide== false)
	{
		//printf("%f\n", time);
		this->time += deltaTime;
		if (this->time > 0.1)
		{
			canSlide = true;
			time = 0;
			this->body.setPosition(this->body.getPosition().x, 356.0f);
		}
	}
	//sf::Vector2f movement(0.0f, 0.0f);
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && body.getPosition().x>= 63)
		velocity.x -= speed ;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && body.getPosition().x <= 960)
		velocity.x += speed ;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& canJump&& canSlide)
	{
		canJump = false;
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
		//square root (2.0f * gravity * jumpHeight);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && canJump&& canSlide)
	{
		canSlide = false;
		this->body.setPosition( this->body.getPosition().x,5000);
		//square root (2.0f * gravity * jumpHeight);
	}
	

	velocity.y += 981.0f * deltaTime;

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
	if (canJump == false)
	{
		if (velocity.y > 0.0f)
		{
			row = 0;
		}
		else
		{
			row = 0;
		}
		maxcol = 2;
	}
	animation.Update(row, maxcol, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
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