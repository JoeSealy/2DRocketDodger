#pragma once
#include "stdafx.h"
#include "GUI.h"

enum PLATFORM_ANIMATION_STATES { SMALL = 0, MEDIUM, MEDIUM2, LONG };

class Platform
{
private:

	//SFML Variables
	sf::Sprite platform;
	sf::Texture texture;
	sf::Vector2f velocity;
	sf::Event event;
	sf::IntRect currentFrame;

	//Object
	GUI* gui;

	//variables
	int shortArrayInt;  //number of the rocket

	float randX;		//rand Y value each time
	float accel;		//Acceleration
	float Speed;		//Speed
	float minSpeed;		//Minimum Speed
	float maxSpeed;		//Max Speed

	short animState;	//what state the character is in

	bool animationDiff;	//Changes rocket 

	//Functions
	void initGUI();
	void initVariables();
	void initTexture();
	void initSprite();
	void initPhysics();

public:
	//constructor/deconstuctor
	Platform();
	virtual ~Platform();

	//vector array
	std::vector<sf::Sprite> rocket_list;

	//variables
	float slowSpeed; //PowerUp slows platform speed

	//Functions
	int randXfloat();

	const sf::Vector2f getPosition() const;
	const sf::FloatRect windowBounds() const;
	void positionSet(const float x, const float y);
	void updateAnimation();
	void updateRocketPhysics();
	void update();
	void render(sf::RenderTarget& rTarget);
};

