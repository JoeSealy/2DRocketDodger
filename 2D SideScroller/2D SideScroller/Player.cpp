#include "Player.h"
#include "stdafx.h"



void Player::initVariables()
{
	this->animState = IDLE;
}

//Private//
void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/player_sheet.png"))
	{
		std::cout << "Error::Player::Could not load player texture" << "\n";
	}
}
void Player::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 40, 50);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.5f, 1.5f);
	this->sprite.setPosition(280.f, 400.f);
}

void Player::initAnimation()
{
	this->animationDiff = true;
	this->stateTimer.restart();
}

void Player::initPhysics()
{
	this->jumpHeight = 30.f;
	this->gravity = 2.f;
	this->minSpeed = 1.f;
	this->maxSpeed = 5.f;
	this->accel = 5.f;
	this->decel = 0.85f;
}

void Player::initMusic()
{
	this->music = false;

	this->Running.openFromFile("Music/Running.wav");
	this->Running.setVolume(60);

	this->Jumping.openFromFile("Music/Jumping.wav");
	this->Jumping.setVolume(60);
}

////////////////////////Public//////////////////


//constructor
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
	this->initMusic();
}
//deconstructor
Player::~Player()
{

}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const bool & Player::animSwitch()
{
	bool tempAnimSwitch = this->animationDiff;
	if (this->animationDiff)
	{
		this->animationDiff = false;
	}
	return tempAnimSwitch;
}

const sf::FloatRect Player::windowBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::velocityReset()
{
	this->velocity.y = 0.f;
	this->canJump = true;
}

void Player::positionSet(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetAnimTimer()
{
	this->stateTimer.restart();
	this->animationDiff = true;
}

void Player::valMove(const float dir_x, const float dir_y)
{
	this->velocity.x += dir_x * this->accel;


	if (std::abs(this->velocity.x) > this->maxSpeed)
	{
		this->velocity.x = this->maxSpeed * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}

	if (std::abs(this->velocity.y) == 0.f)
	{
		this->velocity.y = dir_y;
	}

}

void Player::updatePhysics()
{
	
	this->velocity.y += 1.f * this->gravity;
	this->velocity.x *= this->decel;

	if (std::abs(this->velocity.x) < this->minSpeed)
	{
		this->velocity.x = 0.f;
	}

	if (std::abs(this->velocity.y) < this->minSpeed)
	{
		this->velocity.y = 0.f;
	}

	this->sprite.move(this->velocity);
}

void Player::updateAnimation()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE) 
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.2f || this->animSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 160.f)
			{
				this->currentFrame.left = 0;
			}

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.1f || this->animSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;
			

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(1.5f, 1.5f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.1f || this->animSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;
			

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.5f, 1.5f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.5f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.01f || this->animSwitch())
		{

			this->currentFrame.top = 150;
			this->currentFrame.left = 0.f;

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 20.f || this->animSwitch())
		{

			this->currentFrame.top = 200;
			this->currentFrame.left = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 40.f)
				this->currentFrame.left = 0.f;

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::CROUCH)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 1.f || this->animSwitch())
		{
			//this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(1.5, 0.75);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().height / 1.5f, 1.f);
		this->stateTimer.restart();
	}
	else
		this->stateTimer.restart();
}
void Player::keyPress()
{
	///////////Movement///////////
	this->animState = PLAYER_ANIMATION_STATES::IDLE;										//IDLE

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))									//LEFT KEY
	{
		this->valMove(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))								//RIGHT KEY
	{
		this->valMove(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->canJump == true)		//JUMPING KEY
	{
		this->canJump = false;
		this->valMove(0.f, -30.f);
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;									
	}
	else if (std::abs(this->velocity.y) != 0.f)												//FALLING
	{
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))								//CROUCHING KEY	
	{
		this->animState = PLAYER_ANIMATION_STATES::CROUCH;
	}
}
void Player::update()
{
	this->keyPress();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget & rTarget)
{
	rTarget.draw(this->sprite);
}