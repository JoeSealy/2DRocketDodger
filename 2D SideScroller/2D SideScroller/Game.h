#pragma once
#include "Menu.h"
#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "stdafx.h"
#include "PowerUp.h"
#include "Platform.h"
#include "Background.h"

class Game
{
private:
	//variables
	sf::RenderWindow window;
	sf::Event event;
	sf::VideoMode videomode;

	//Music/Sound Effects
	sf::Music musicMenu;
	sf::Music musicInGame;
	sf::Music musicDeath;

	//Objects
	Player* player;
	Enemy*  enemy;
	GUI* gui;
	Menu* menu;
	PowerUp* powerup;
	Platform* platform;
	Background* background;

	//Extras
	int musicStageInt;	//Music for each game state
	bool endGame;		//checks if end game


	float deltaX[6], deltaY[6], intersectX[6], intersectY[6];					//check collision for each rocket
	float powerUpDeltaX, powerUpDeltaY, powerUpIntersectX, powerUpIntersectY;	//collision for power up

	//functions
	void initwindow();
	void initPlayer();
	void initEnemy();
	void initGUI();
	void initPowerUp();
	void initPlatform();
	void initMenu();
	void initMusic();
	void initBackground();

public:

	//constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool getWindowIsOpen() const;
	const bool & getEndGame() const;

	//Fuctions
	void collisionUpdate();
	bool collisionCheck();

	//Enemy functions
	void enemyUpdate();
	void enemyRender();

	//Player functions
	void playerUpdate();
	void playerRender();

	//GUI functions
	void guiUpdate();
	void guiRender();

	//Menu functions
	void MenuUpdate();
	void MenuRender();

	//Powerup functions
	void powerUpUpdate();
	void powerUpRender();

	//Platform functions
	void platformUpdate();
	void platformRender();

	void BackgroundUpdate();

	void backgroundRender();

	//Game functions
	void powerups();
	void update();
	void render();
	const sf::RenderWindow& getWindow() const;
	

};

