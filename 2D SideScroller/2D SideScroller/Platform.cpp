#include "Platform.h"


void Platform::initGUI()
{
	this->gui = new GUI();
}

void Platform::initVariables()
{

}

void Platform::initTexture()
{
	if (!this->texture.loadFromFile("Textures/platform_InGame.jpg"))
	{
		std::cout << "ERROR Platform file is not available";
	}
}

void Platform::initSprite()
{
	this->platformStart.setTexture(this->texture);
	this->currentStart = sf::IntRect(30, 0, 700, 30);
	this->platformStart.setTextureRect(this->currentStart);

	this->platformShort.setTexture(this->texture);
	this->currentShort = sf::IntRect(2, 270, 32, 70);
	this->platformShort.setTextureRect(this->currentShort);

	this->platformMedium.setTexture(this->texture);
	this->currentMedium = sf::IntRect(2, 270, 32, 70);
	this->platformMedium.setTextureRect(this->currentMedium);

	this->platformLong.setTexture(this->texture);
	this->currentLong = sf::IntRect(2, 270, 32, 70);
	this->platformLong.setTextureRect(this->currentLong);

}

void Platform::initPosition() 
{
	this->platformStart.setPosition(0, -30);
	/*this->platformShort.setPosition();
	this->platformMedium.setPosition();
	this->platformLong.setPosition();*/
}

void Platform::initPhysics()
{

}

//public

Platform::Platform()
{
	this->initSprite();
	this->initVariables();
	this->initTexture();
	this->initPhysics();
	this->initGUI();
	this->initPosition();
}

Platform::~Platform()
{
	delete this->gui;
}

int Platform::randXfloat()
{
	randX = std::rand() % 480 + 80;
	return randX;
}

const sf::Vector2f Platform::getPosition() const
{
	return this->platformStart.getPosition();
	return this->platformShort.getPosition();
	return this->platformMedium.getPosition();
	return this->platformLong.getPosition();
}

const sf::FloatRect Platform::windowBounds() const
{
	return this->platformStart.getGlobalBounds();
	return this->platformShort.getGlobalBounds();
	return this->platformMedium.getGlobalBounds();
	return this->platformLong.getGlobalBounds();
}

void Platform::positionSet(const float x, const float y)
{
	return this->platformStart.setPosition(x, y);
	return this->platformShort.setPosition(x, y);
	return this->platformMedium.setPosition(x, y);
	return this->platformLong.setPosition(x, y);
}

void Platform::updatePlatformSize()
{
}

void Platform::updatePlatformPhysics()
{
	this->velocity.y = 1;
	this->platformStart.move(this->velocity);
}

void Platform::update()
{
	this->updatePlatformSize();
	this->updatePlatformPhysics();
}

void Platform::render(sf::RenderTarget & rTarget)
{
	rTarget.draw(this->platformStart);
	/*rTarget.draw(this->platformShort);
	rTarget.draw(this->platformMedium);
	rTarget.draw(this->platformLong);*/
}
