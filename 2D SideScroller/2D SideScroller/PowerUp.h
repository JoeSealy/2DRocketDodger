#pragma once
#include "stdafx.h"
#include "GUI.h"
class PowerUp
{
	private:
		//SFML Variables
		sf::Sprite powerUp;
		sf::Texture texture;
		sf::Event event;
		sf::Vector2f velocity;
		sf::IntRect currentFrame;

		sf::Clock dropClock;

		//Object
		GUI* gui;
		
		//Variables
		int randX;
		float Speed;		//speed
		float minSpeed;		//Lowest movement speed needs powerup
		float maxSpeed;
		//Functions
		void initGUI();
		void initVariables();
		void initTexture();
		void initSprite();
		void initPhysics();

	public:
		//Contructor/destructor
		PowerUp();
		virtual ~PowerUp();

		//Variables
		int randPowerUpInt;
		bool powerUpDrop;

		//Functions
		int randXint();
		const sf::Vector2f getPosition() const;
		const sf::FloatRect windowBounds() const;
		void positionSet(const float x, const float y);
		int randPowerUp();
		void updatePowerUpPhysics();
		void update();
		void render(sf::RenderTarget& rTarget);
};

