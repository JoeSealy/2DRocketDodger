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
		this->platformShort.setPosition(this->randXfloatSmall(), -30);
		this->platform_List.push_back(platformShort);
	}

	this->platformMedium.setTexture(this->texture);
	this->currentMedium = sf::IntRect(45, 215, 180, 25);
	this->platformMedium.setTextureRect(this->currentMedium);
	this->platformMedium.setScale(1.3, 1);
	for (int i = 0; i < 6; i++) {
		this->platformMedium.setPosition(this->randXfloatMedium(), -30);
		this->platform_List.push_back(platformMedium);
	}

	this->platformLong.setTexture(this->texture);
	this->currentLong = sf::IntRect(30, 362, 520, 38);
	this->platformLong.setTextureRect(this->currentLong);
	this->platformLong.setScale(0.7, 1);
	for (int i = 0; i < 6; i++) {
		this->platformLong.setPosition(this->randXfloatLarge(), -30);
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

int Platform::randXfloatSmall()
{
	randXSmall = std::rand() % 400 + 80;
	return randXSmall;
}

int Platform::randXfloatMedium()
{
	randXMedium = std::rand() % 400 + 80;
	return randXMedium;
}

int Platform::randXfloatLarge()
{
	randXLarge = std::rand() % 400 + 80;
	return randXLarge;
}

const sf::Vector2f Platform::getPosition() const
{
	switch (platformNumber)
	{
	case 0:
		return this->platform_List[0].getPosition();
		break;
	case 1:
		return this->platform_List[1].getPosition();
		break;
	case 2:
		return this->platform_List[2].getPosition();
		break;
	case 3:
		return this->platform_List[3].getPosition();
		break;
	case 4:
		return this->platform_List[4].getPosition();
		break;
	case 5:
		return this->platform_List[5].getPosition();
		break;
	case 6:
		return this->platform_List[6].getPosition();
		break;
	case 7:
		return this->platform_List[7].getPosition();
		break;
	case 8:
		return this->platform_List[8].getPosition();
		break;
	case 9:
		return this->platform_List[9].getPosition();
		break;
	case 10:
		return this->platform_List[10].getPosition();
		break;
	case 11:
		return this->platform_List[11].getPosition();
		break;
	case 12:
		return this->platform_List[12].getPosition();
		break;
	case 13:
		return this->platform_List[13].getPosition();
		break;
	case 14:
		return this->platform_List[14].getPosition();
		break;
	case 15:
		return this->platform_List[15].getPosition();
		break;
	case 16:
		return this->platform_List[16].getPosition();
		break;
	case 17:
		return this->platform_List[17].getPosition();
		break;

	}
}

const sf::FloatRect Platform::windowBounds() const
{
	for (int i = 0; i < platform_List.size(); i++) {
		return this->platform_List[i].getGlobalBounds();
	}
}

void Platform::positionSet(const float x, const float y)
{
	switch (platformNumber)
	{
	case 0:
		this->randXfloatSmall();
		return this->platform_List[0].setPosition(this->randXfloatSmall() , y);
		break;
	case 1:
		this->randXfloatSmall();
		return this->platform_List[1].setPosition(this->randXfloatSmall(), y);
		break;
	case 2:
		this->randXfloatSmall();
		return this->platform_List[2].setPosition(this->randXfloatSmall(), y);
		break;
	case 3:
		this->randXfloatSmall();
		return this->platform_List[3].setPosition(this->randXfloatSmall(), y);
		break;
	case 4:
		this->randXfloatSmall();
		return this->platform_List[4].setPosition(this->randXfloatSmall(), y);
		break;
	case 5:
		this->randXfloatSmall();
		return this->platform_List[5].setPosition(this->randXfloatSmall(), y);
		break;
	case 6:
		this->randXfloatMedium();
		return this->platform_List[6].setPosition(this->randXfloatMedium(), y);
		break;
	case 7:
		this->randXfloatMedium();
		return this->platform_List[7].setPosition(this->randXfloatMedium(), y);
		break;
	case 8:
		this->randXfloatMedium();
		return this->platform_List[8].setPosition(this->randXfloatMedium(), y);
		break;
	case 9:
		this->randXfloatMedium();
		return this->platform_List[9].setPosition(this->randXfloatMedium(), y);
		break;
	case 10:
		this->randXfloatMedium();
		return this->platform_List[10].setPosition(this->randXfloatMedium(), y);
		break;
	case 11:
		this->randXfloatMedium();
		return this->platform_List[11].setPosition(this->randXfloatMedium(), y);
		break;
	case 12:
		this->randXfloatLarge();
		return this->platform_List[12].setPosition(this->randXfloatLarge(), y);
		break;
	case 13:
		this->randXfloatLarge();
		return this->platform_List[13].setPosition(this->randXfloatLarge(), y);
		break;
	case 14:
		this->randXfloatLarge();
		return this->platform_List[14].setPosition(this->randXfloatLarge(), y);
		break;
	case 15:
		this->randXfloatLarge();
		return this->platform_List[15].setPosition(this->randXfloatLarge(), y);
		break;
	case 16:
		this->randXfloatLarge();
		return this->platform_List[16].setPosition(this->randXfloatLarge(), y);
		break;
	case 17:
		this->randXfloatLarge();
		return this->platform_List[17].setPosition(this->randXfloatLarge(), y);
		break;

	}
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
