#pragma once
#include "stdafx.h"
#include "GUI.h"
enum ENEMY_ANIMATION_STATES{SHORT = 0, LONG};
class Enemy
{
private:
	sf::Sprite rocket;
	sf::Texture texture;
	sf::Event event;
	sf::IntRect currentFrame;
	sf::Clock stateTimer;
	sf::Vector2f velocity;

	GUI* gui;

	float randY;
	int shortArrayInt;
	float animShortArray [12];
	float accel;		//Acceleration
	float decel;		//Deceleration
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
	Enemy();
	virtual ~Enemy();

	std::vector<sf::Sprite> rocket_list;

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

