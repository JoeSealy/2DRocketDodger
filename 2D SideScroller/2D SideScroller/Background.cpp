#include "Background.h"


void Background::initBackground()				//initialise background
{
	if (!this->groundBackgroundTexture.loadFromFile("Textures/Ground_Background_inGame.png"))
	{
		std::cerr << "No font file found!" << std::endl;
	}
	this->groundBackgroundSprite.setTexture(this->groundBackgroundTexture);
	this->groundBackgroundSprite.setScale(1.3, 1);
	this->groundBackgroundSprite.setPosition(0, -500);

	if (!this->spaceBackgroundTexture.loadFromFile("Textures/Space_Background_inGame.jpg"))
	{
		std::cerr << "No font file found!" << std::endl;
	}
	this->spaceBackgroundSprite.setTexture(this->spaceBackgroundTexture);
	this->spaceBackgroundSprite.setScale(1, 2);
	this->spaceBackgroundSprite.setPosition(0, -2200);

	if (!this->deepSpaceBackgroundTexture.loadFromFile("Textures/Deep_Space_Background_inGame.jpg"))
	{
		std::cerr << "No font file found!" << std::endl;
	}
	this->deepSpaceBackgroundSprite.setTexture(this->deepSpaceBackgroundTexture);
	this->deepSpaceBackgroundSprite.setScale(1, 2);
	this->deepSpaceBackgroundSprite.setPosition(0, -4000);

	//Ground_Background_inGame
	//Space_Background_inGame
	//Deep_Space_Background_inGame
}

Background::Background()				//constuctor
{
	this->initBackground();
}

Background::~Background()				//deconstructor
{
}

void Background::BackgroundUpdate()
{
	this->backgroundVelocity.y = 0.1;
	this->groundBackgroundSprite.move(this->backgroundVelocity);
	this->spaceBackgroundSprite.move(this->backgroundVelocity);
	this->deepSpaceBackgroundSprite.move(this->backgroundVelocity);
}


void Background::update()							//update function
{
	this->BackgroundUpdate();
}

void Background::render(sf::RenderTarget & rTarget)		//render targets
{
	rTarget.draw(deepSpaceBackgroundSprite);
	rTarget.draw(spaceBackgroundSprite);
	rTarget.draw(groundBackgroundSprite);
}