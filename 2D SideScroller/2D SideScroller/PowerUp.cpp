#include "PowerUp.h"

void PowerUp::initVariables()				//initiailise varibales
{
	this->powerUpDrop = false;
}

void PowerUp::initTexture()					//initialise texture
{
	if (!this->texture.loadFromFile("Textures/powerup_sprite_sheet.png"))
	{
		std::cout << "Error::Player::Could not load player texture" << "\n";
	}
}

void PowerUp::initSprite()					//intialise sprite
{
	this->powerUp.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 640, 550);
	this->powerUp.setTextureRect(this->currentFrame);
	this->powerUp.setScale(0.1f, 0.1f);
	this->powerUp.setPosition(this->randXint(), -100.f);

}

PowerUp::PowerUp()							//constructor
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

PowerUp::~PowerUp()							//deconstuctor
{
}

const sf::Vector2f PowerUp::getPosition() const			//gets position of power up
{
	return this->powerUp.getPosition();
}

const sf::FloatRect PowerUp::windowBounds() const		//boundaries of power up
{
	return this->powerUp.getGlobalBounds();
}

void PowerUp::positionSet(const float x, const float y)	// sets the position with rand int for the x coordinate
{
	this->randXint();
	return this->powerUp.setPosition(randX, y);
}

int PowerUp::randXint()					// produces a random int for the x coordinate
{
	randX = std::rand() % 480;
	return randX;
}

int PowerUp::randPowerUp()				//produces integer for the rand power up
{
	randPowerUpInt = std::rand() % 4;
	return randPowerUpInt;
}

int PowerUp::randClockInt()				//produces rand number between 10 and 20 
{
	randDropClockInt = std::rand() % (20 - 10) + 10;
	return randDropClockInt;
}

void PowerUp::updatePowerUpPhysics()	//power up physics once power up taken reset velocity and wait 10-20 seconds randomly for it to drop again
{		
	if (!this->powerUpDrop)
	{
		this->velocity.y = 1.f;
	}

	if (this->powerUpDrop){
		std::srand(time(0));
		this->velocity.y = 0.f;

		this->dropClockInt = dropClock.getElapsedTime().asSeconds();
		this->randClockInt();

		if (this->dropClockInt >= this->randDropClockInt)
		{
			dropClock.restart();
			this->powerUpDrop = false;
		}
	}


	this->powerUp.move(this->velocity);
}

void PowerUp::update()				//update function
{
	this->updatePowerUpPhysics();
}

void PowerUp::render(sf::RenderTarget & rTarget)		//render target
{
	rTarget.draw(this->powerUp);
}
