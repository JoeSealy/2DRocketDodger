#include "Enemy.h"
#include "stdafx.h"
#include "GUI.h"

void Enemy::initVariables()
{
	this->animState = SHORT;
}

void Enemy::initTexture()
{
	if (!this->texture.loadFromFile("Textures/enemy_sprite_sheet.png"))
	{
		std::cout << "Error::Player::Could not load player texture" << "\n";
	}
}
void Enemy::initSprite()
{
	this->rocket.setTexture(this->texture);
	this->currentFrame = sf::IntRect(2, 270, 32, 70);
	this->rocket.setTextureRect(this->currentFrame);
	this->rocket.setScale(1.f, 1.f);
	this->rocket.setRotation(-90.f);
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
		this->rocket.setPosition(640.f, this->randYfloat());
		this->rocket_list.push_back(rocket);
	}
}

void Enemy::initPhysics()
{
	this->shortArrayInt = 0;
	this->minSpeed = -0.5f;
	this->maxSpeed = -3.f;
	this->Speed = -0.5f;
	this->accel = 0.2f;
}

void Enemy::initGUI()
{
	this->gui = new GUI();
}

Enemy::Enemy()
	:animShortArray{ 30.f,30.f,32.f,34.f,35.f,34.f,34.f,30.f,30.f,30.f,29.f,29.f }
{
	this->initSprite();
	this->initVariables();
	this->initTexture();
	this->initPhysics();
	this->initGUI();
}

Enemy::~Enemy()
{
	delete this->gui;
}

const sf::Vector2f Enemy::getPosition() const
{
	switch (rocketNumber)
	{
		case 1:
			return this->rocket_list[0].getPosition();
			break;
		case 2:
			return this->rocket_list[1].getPosition();
			break;
		case 3:
			return this->rocket_list[2].getPosition();
			break;
		case 4:
			return this->rocket_list[3].getPosition();
			break;
		case 5:
			return this->rocket_list[4].getPosition();
			break;
		case 6:
			return this->rocket_list[5].getPosition();
			break;

	}
	
}

const sf::FloatRect Enemy::windowBounds() const
{
	for (int i = 0.f; i < rocket_list.size(); i++) {
		return this->rocket_list[i].getGlobalBounds();
	}
} 

void Enemy::positionSet(const float x, const float y)
{
	switch (rocketNumber)
	{
	case 0:
		this->randYfloat();
		return this->rocket_list[0].setPosition(x, this->randYfloat());
		break;
	case 1:
		this->randYfloat();
		return this->rocket_list[1].setPosition(x, this->randYfloat());
		break;
	case 2:
		this->randYfloat();
		return this->rocket_list[2].setPosition(x, this->randYfloat());
		break;
	case 3:
		this->randYfloat();
		return this->rocket_list[3].setPosition(x, this->randYfloat());
		break;
	case 4:
		this->randYfloat();
		return this->rocket_list[4].setPosition(x, this->randYfloat());
		break;
	case 5:
		this->randYfloat();
		return this->rocket_list[5].setPosition(x, this->randYfloat());
		break;

	}
}

float Enemy::randYfloat()
{
	randY = std::rand() % 480 + 80;
	return randY;
}

void Enemy::updateAnimation()
{
	if (this->animState == ENEMY_ANIMATION_STATES::SHORT)
	{
		if (this->stateTimer.getElapsedTime().asSeconds() >= 0.05f)
		{
			this->currentFrame.top = 270.f;
			this->currentFrame.left += animShortArray[this->shortArrayInt];
			//{ 30.f,30.f,32.f,34.f,35.f,34.f,34.f,30.f,30.f,30.f,29.f,29.f }
			shortArrayInt++;
			if (this->shortArrayInt == 12) {
				this->currentFrame.left = 2.f;
				this->shortArrayInt = 0;
			}
			this->stateTimer.restart();
			for (int i = 0.f; i < rocket_list.size(); i++) {
				this->rocket_list[i].setTextureRect(this->currentFrame);
			}
			
		}
	}
}
void Enemy::updateRocketPhysics()
{
	this->gui->clockUpdate();
	this->velocity.x = minSpeed;
	if (this->gui->clockUpdate() > 30.f) {
		this->velocity.x = minSpeed + 0.5;
	}

	 const int amountRocket(1.f + fmod(this->gui->countUp, 500.f));
	 for (int i = 0.f; i < ((amountRocket < rocket_list.size() + 1.f) ? amountRocket : rocket_list.size()); i++) {
		 this->rocket_list[i].move(this->velocity);
	 }

}

void Enemy::update()
{
	this->updateAnimation();
	this->updateRocketPhysics();
}

void Enemy::render(sf::RenderTarget & rTarget)
{
	for (int i = 0.f; i < rocket_list.size(); i++) {
		rTarget.draw(this->rocket_list[i]);
	}
}
