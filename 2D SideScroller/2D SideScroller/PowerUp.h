#pragma once
#include "stdafx.h"
#include "GUI.h"
class PowerUp
{
	private:
		sf::Sprite powerUp;
		sf::Texture texture;
		sf::Event event;
		sf::Vector2f velocity;

		GUI* gui;

		float randX;
		float Speed;		//speed
		float minSpeed;		//Lowest movement speed needs powerup
		float maxSpeed;

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
		float randXfloat();
		void updatePowerUpPhysics();
		void update();
		void render(sf::RenderTarget& rTarget);
};

