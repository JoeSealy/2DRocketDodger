#include "Player.h"
#include "stdafx.h"



void Player::initVariables()			//initialise variables
{
	this->animState = IDLE;
}

//Private//
void Player::initTexture()				//initialise texture
{
	if (!this->texture.loadFromFile("Textures/player_sprite_sheet.png"))   //error handler
	{
		std::cout << "Error::Player::Could not load player texture" << "\n";
	}
}
void Player::initSprite()							//initialise sprite
{
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 30, 40, 50);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.5f, 1.5f);
	this->sprite.setPosition(280.f, 400.f);
}

void Player::initAnimation()			//initialise animation
{
	this->animationDiff = true;
	this->stateTimer.restart();
}

void Player::initPhysics()				//initialise physics
{
	this->jumpHeight = 30.f;
	this->gravity = 2.f;
	this->minSpeed = 1.f;
	this->maxSpeed = 5.f;
	this->accel = 5.f;
	this->decel = 0.85f;
}

void Player::initMusic()				//initialise music
{

	this->musicRunning.openFromFile("Music/MusicRunning.wav");
	this->musicRunning.setVolume(50);
	this->musicRunning.setLoop(true);
	this->runSound = false;

	this->musicJumping.openFromFile("Music/MusicJumping.wav");
	this->musicJumping.setVolume(50);
	this->jumpSound = false;
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

const sf::Vector2f Player::getPosition() const    // get position for sprite
{
	return this->sprite.getPosition();
}

const bool & Player::animSwitch()					//switches animation when key press is switch
{
	bool tempAnimSwitch = this->animationDiff;
	if (this->animationDiff)
	{
		this->animationDiff = false;
	}
	return tempAnimSwitch;
}

const sf::FloatRect Player::windowBounds() const	// bounderies of the sprite
{
	return this->sprite.getGlobalBounds();
}

void Player::velocityReset()						//velocity resets
{
	this->velocity.y = 0.f;
	this->canJump = true;
}

void Player::positionSet(const float x, const float y)			//sets position
{
	this->sprite.setPosition(x, y);
}

void Player::resetAnimTimer()							//reset animation timer to the start
{
	this->stateTimer.restart();
	this->animationDiff = true;
}

void Player::valMove(const float dir_x, const float dir_y)  //value moves player in either direction
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

void Player::updatePhysics()									//update physics of player
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

void Player::updateAnimation()									//update animations
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
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.1 || this->animSwitch())
		{
			this->currentFrame.top = 50;
			this->currentFrame.left += 40;
			if (this->currentFrame.left >= 360)
				this->currentFrame.left = 0;
			

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(1.5, 1.5);
		this->sprite.setOrigin(0, 0);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.1f || this->animSwitch())
		{
			this->currentFrame.top = 50;
			this->currentFrame.left += 40;
			if (this->currentFrame.left >= 360)
				this->currentFrame.left = 0;
			

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.5, 1.5);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.5, 0.);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.01 || this->animSwitch())
		{

			this->currentFrame.top = 150;
			this->currentFrame.left = 0;

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 20 || this->animSwitch())
		{

			this->currentFrame.top = 200;
			this->currentFrame.left = 0;
			this->currentFrame.left += 40;
			if (this->currentFrame.left >= 40)
				this->currentFrame.left = 0;

			this->stateTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->stateTimer.restart();
}
void Player::keyPress()																//key press activates animation music for actions 
{
	///////////Movement///////////
	this->animState = PLAYER_ANIMATION_STATES::IDLE;										//IDLE

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))									//LEFT KEY
	{
		if (!this->runSound && this->canJump)
		{
			this->runSound = true;
			this->musicPlay();
		}
		this->valMove(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))								//RIGHT KEY
	{
		if (!this->runSound && this->canJump)
		{
			this->runSound = true;
			this->musicPlay();
		}
		this->valMove(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;

	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->canJump == true)		//JUMPING KEY
	{
		this->canJump = false;

		if (!this->jumpSound)
		{
			this->jumpSound = true;
			this->musicPlay();
		}
		this->valMove(0.f, -30.f);
		this->animState = PLAYER_ANIMATION_STATES::JUMPING;									
	}
	
	if (std::abs(this->velocity.y) != 0.f)												//FALLING
	{
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}

}

void Player::musicPlay()													//plays music for running and jumping
{
	if (this->jumpSound)
	{
		this->musicJumping.play();
	}

	if (this->runSound)
	{
		this->musicRunning.play();
	}
}
void Player::update()														//update functions
{
	this->keyPress();
	this->updateAnimation();
	this->updatePhysics();
}

void Player::render(sf::RenderTarget & rTarget)								//renders target
{
	rTarget.draw(this->sprite);
}