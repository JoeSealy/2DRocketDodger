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
		this->platformShort.setPosition(this->randX(), -50);
		this->platform_List.push_back(platformShort);
	}

	this->platformMedium.setTexture(this->texture);
	this->currentMedium = sf::IntRect(45, 215, 180, 25);
	this->platformMedium.setTextureRect(this->currentMedium);
	this->platformMedium.setScale(1.3, 1);

	for (int i = 0; i < 6; i++) {
		this->platformMedium.setPosition(this->randX(), -50);
		this->platform_List.push_back(platformMedium);
	}

	this->platformLong.setTexture(this->texture);
	this->currentLong = sf::IntRect(30, 362, 520, 38);
	this->platformLong.setTextureRect(this->currentLong);
	this->platformLong.setScale(0.7, 1);

	for (int i = 0; i < 6; i++) {
		this->platformLong.setPosition(this->randX(), -50);
		this->platform_List.push_back(platformLong);
	}
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
}

Platform::~Platform()
{
	delete this->gui;
}

int Platform::randX()
{
	randXint = std::rand() % 400;
	return randXint;
}

const sf::Vector2f Platform::getPosition() const
{
	return this->platform_List[platformNumber].getPosition();
}

const sf::FloatRect Platform::windowBounds() const
{
	for (int i = 0; i < platform_List.size(); i++) {
		return this->platform_List[i].getGlobalBounds();
	}
}

void Platform::positionSet(const float x, const float y)
{
		this->randX();
		return this->platform_List[platformNumber].setPosition(this->randX() , y);
}

void Platform::updatePlatformPhysics()
{
	(this->velocity.y) = 1;

	this->platformStart.move(this->velocity);

	if (this->gui->clockUpdate() > 5.f) {
		for (int i = 0; i <= 0; i++)
		{
			this->platform_List[i].move(this->velocity);
		}
	}

}

void Platform::update()
{
	this->updatePlatformPhysics();
}

void Platform::render(sf::RenderTarget & rTarget)
{
	rTarget.draw(this->platformStart);

	for (int i = 0; i < platform_List.size(); i++) {
		rTarget.draw(this->platform_List[i]);
	}
}
