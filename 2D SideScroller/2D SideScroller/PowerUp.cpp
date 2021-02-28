#include "PowerUp.h"

void PowerUp::initGUI()
{
	this->gui = new GUI();
}

void PowerUp::initVariables()
{
}

void PowerUp::initTexture()
{
	if (!this->texture.loadFromFile("Textures/powerup_sprite_sheet.png"))
	{
		std::cout << "Error::Player::Could not load player texture" << "\n";
	}
}

void PowerUp::initSprite()
{
	this->powerUp.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 640, 550);
	this->powerUp.setTextureRect(this->currentFrame);
	this->powerUp.setScale(0.1f, 0.1f);
	this->powerUp.setPosition(this->randXfloat(), 0.f);

}

void PowerUp::initPhysics()
{
	this->Speed = 0.5f;
}

PowerUp::PowerUp()
{
	this->initGUI();
	this->initTexture();
	this->initSprite();
	this->initPhysics();
}

PowerUp::~PowerUp()
{
	delete this->gui;
}

const sf::Vector2f PowerUp::getPosition() const
{
	return this->powerUp.getPosition();
}

const sf::FloatRect PowerUp::windowBounds() const
{
	return this->powerUp.getGlobalBounds();
}

void PowerUp::positionSet(const float x, const float y)
{
	return this->powerUp.setPosition(this->randXfloat(), y);
}

float PowerUp::randXfloat()
{
	randX = std::rand() % 480 + 80;
	return randX;
}

void PowerUp::updatePowerUpPhysics()
{
	this->gui->clockUpdate();
}

void PowerUp::update()
{
	this->updateAnimation();
	this->updatePowerUpPhysics();
}

void PowerUp::render(sf::RenderTarget & rTarget)
{
	rTarget.draw(this->powerUp);
}
