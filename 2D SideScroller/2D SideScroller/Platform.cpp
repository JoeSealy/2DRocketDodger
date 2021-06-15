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
	this->platform.setTexture(this->texture);
	this->currentFrame = sf::IntRect(2, 270, 32, 70);
	this->platform.setTextureRect(this->currentFrame);
	this->platform.setScale(1, 1);
	this->platform.setRotation(-90);
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
		this->platform.setPosition(this->randXfloat(), 0);
		//this->platform.push_back(platform);
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

int Platform::randXfloat()
{
	randX = std::rand() % 480 + 80;
	return randX;
}

const sf::Vector2f Platform::getPosition() const
{
	return sf::Vector2f();
}

const sf::FloatRect Platform::windowBounds() const
{
	return sf::FloatRect();
}

void Platform::positionSet(const float x, const float y)
{
}

void Platform::update()
{
}

void Platform::render(sf::RenderTarget & rTarget)
{
}
