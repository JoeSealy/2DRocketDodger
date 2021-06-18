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
	srand(time(NULL));
	this->platformStart.setTexture(this->texture);
	this->currentStart = sf::IntRect(30, 0, 700, 30);
	this->platformStart.setTextureRect(this->currentStart);

	this->platformShort.setTexture(this->texture);
	this->currentShort = sf::IntRect(45, 215, 180, 25);
	this->platformShort.setTextureRect(this->currentShort);
	this->platformShort.setScale(0.7, 1);
	for (int i = 0; i < 6; i++) {
		this->platformShort.setPosition(randXfloat(), -30);
		this->platform_List.push_back(platformShort);
	}

	this->platformMedium.setTexture(this->texture);
	this->currentMedium = sf::IntRect(45, 215, 180, 25);
	this->platformMedium.setTextureRect(this->currentMedium);
	this->platformMedium.setScale(1.3, 1);
	for (int i = 0; i < 6; i++) {
		this->platformMedium.setPosition(randXfloat(), -30);
		this->platform_List.push_back(platformMedium);
	}

	this->platformLong.setTexture(this->texture);
	this->currentLong = sf::IntRect(30, 362, 520, 38);
	this->platformLong.setTextureRect(this->currentLong);
	this->platformLong.setScale(0.7, 1);
	for (int i = 0; i < 6; i++) {
		this->platformLong.setPosition(randXfloat(), -30);
		this->platform_List.push_back(platformLong);
	}
}

void Platform::initPosition() 
{
	this->platformStart.setPosition(0, -30);
	this->platformShort.setPosition(200, 50);
	this->platformMedium.setPosition(200, 100);
	this->platformLong.setPosition(200, 150);
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
	randX = std::rand() % 400 + 80;
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
	rTarget.draw(this->platformShort);
	rTarget.draw(this->platformMedium);
	rTarget.draw(this->platformLong);
}
