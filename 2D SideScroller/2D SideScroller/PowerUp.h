#pragma once
#include "stdafx.h"
#include "GUI.h"
class PowerUp
{
	
	private:
		sf::Sprite powerUp;
		sf::Texture texture;
		sf::Event event;
		sf::IntRect currentFrame;
		sf::Clock stateTimer;
		sf::Vector2f velocity;

		GUI* gui;

		float randY;
		float Speed;		//speed
		float minSpeed;		//Lowest movement speed needs powerup
		float maxSpeed;
		short animState;	//what state the character is in
		bool animationDiff;	//Changes rocket size

		void initGUI();
		void initVariables();
		void initTexture();
		void initSprite();
		void initPhysics();

	public:
		PowerUp();
		virtual ~PowerUp();

		const sf::Vector2f getPosition() const;
		const sf::FloatRect windowBounds() const;

		void positionSet(const float x, const float y);
		int rocketNumber;
		float randYfloat();
		void resetAnimTimer();
		void updateAnimation();
		void updateRocketPhysics();
		void update();
		void render(sf::RenderTarget& rTarget);
};

