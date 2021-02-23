#pragma once
#include "stdafx.h"
enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_RIGHT, MOVING_LEFT, JUMPING, FALLING, CROUCH};
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Event event;
	sf::IntRect currentFrame;
	sf::Clock stateTimer;
	sf::Vector2f velocity;
	sf::Music Running;
	sf::Music Jumping;

	float maxGravSpeed;	
	float gravity;		//gravity speed
	float jumpHeight;	//max height jumping	
	float accel;		//Acceleration
	float decel;		//Deceleration
	float maxSpeed;		//Top movement speed
	float minSpeed;		//Lowest movement speed
	bool animationDiff;	//Swap animation
	bool canJump;
	bool music;
	short animState;	//what state the character is in

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();
	void initMusic();

public:
	Player();
	virtual ~Player();

	const sf::Vector2f getPosition()const;
	const bool& animSwitch();
	const sf::FloatRect windowBounds() const;

	void velocityReset();
	void positionSet(const float x, const float y);

	//functions
	void resetAnimTimer();
	void valMove(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateAnimation();
	void keyPress();
	void update();
	void render(sf::RenderTarget& rTarget);
};

