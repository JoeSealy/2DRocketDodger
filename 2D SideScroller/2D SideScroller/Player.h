#pragma once
#include "stdafx.h"
enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_RIGHT, MOVING_LEFT, JUMPING, FALLING, CROUCH};
class Player
{
private:
	//SFML Variables
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Event event;
	sf::IntRect currentFrame;
	sf::Vector2f velocity;

	sf::Clock stateTimer;

	//variables
	float maxGravSpeed;	//max Garvity
	float gravity;		//gravity speed
	float jumpHeight;	//max height jumping	
	float accel;		//Acceleration
	float decel;		//Deceleration
	float maxSpeed;		//Top movement speed
	float minSpeed;		//Lowest movement speed

	bool animationDiff;	//Swap animation
	bool canJump;			//jump if on floor
	bool canPlatformJump; //platform jump

	short animState;	//what state the character is in


	//Functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();
	void initMusic();

public:
	//Constructor/Deconstuctor
	Player();
	virtual ~Player();

	//SFML Variables
	sf::Music musicRunning;		
	sf::Music musicJumping;

	//Variables
	bool jumpSound;			//do jumping sound when jumping
	bool runSound;			//do running sound when runnning

	//functions
	const sf::Vector2f getPosition()const;
	const sf::FloatRect windowBounds() const;
	const bool& animSwitch();

	void positionSet(const float x, const float y);
	void valMove(const float dir_x, const float dir_y);

	void platformJumpReset();
	void velocityReset();
	void resetAnimTimer();

	void musicPlay();
	
	void updatePhysics();
	void updateAnimation();
	void keyPress();
	void update();
	void render(sf::RenderTarget& rTarget);
};

