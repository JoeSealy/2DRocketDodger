#pragma once
#include "stdafx.h"
#include "GUI.h"
enum ENEMY_ANIMATION_STATES{SHORT = 0, LONG};
class Enemy
{
private:

	//SFML Variables
	sf::Sprite rocket;
	sf::Texture texture;
	sf::Event event;
	sf::IntRect currentFrame;
	sf::Clock stateTimer;
	sf::Vector2f velocity;

	//Object
	GUI* gui;

	//variables
	int shortArrayInt;  //number of the rocket

	float randY;		//rand Y value each time
	float animShortArray [12]; //animation array
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
	Enemy();		
	virtual ~Enemy();	

	//vector array
	std::vector<sf::Sprite> rocket_list;		

	//variables
	float slowSpeed; //PowerUp slows rocket
	int rocketNumber; //Number of which rocket

	//Functions
	float randYfloat();

	const sf::Vector2f getPosition() const;		
	const sf::FloatRect windowBounds() const;	
	void positionSet(const float x, const float y); 
	void updateAnimation();
	void updateRocketPhysics();
	void update();
	void render(sf::RenderTarget& rTarget);
};

