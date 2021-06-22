#pragma once
#include "stdafx.h"
#include "GUI.h"

class Platform
{
private:

	//SFML Variables
	sf::Sprite platformStart;
	sf::Sprite platformShort;
	sf::Sprite platformMedium;
	sf::Sprite platformLong;
	sf::IntRect currentStart;
	sf::IntRect currentShort;
	sf::IntRect currentMedium;
	sf::IntRect currentLong;

	sf::Texture texture;
	sf::Vector2f velocity;
	sf::Event event;

	//clock
	sf::Clock platformClock;

	//Object
	GUI* gui;

	//variables
	int shortArrayInt;  //number of the rocket
	int randXint;		//rand Y value each time
	int clockNumber;
	int platformClockInt;


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

public:
	//constructor/deconstuctor
	Platform();
	virtual ~Platform();

	//vector array
	std::vector<sf::Sprite> platform_List;

	//variables
	float slowSpeed; //PowerUp slows platform speed
	int platformNumber;

	//Functions
	int randX();

	const sf::Vector2f getPosition() const;
	const sf::FloatRect windowBounds() const;
	void positionSet(const float x, const float y);
	void updatePlatformPhysics();
	void update();
	void render(sf::RenderTarget& rTarget);
};

