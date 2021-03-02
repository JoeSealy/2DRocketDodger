#pragma once
#include "Menu.h"
#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "stdafx.h"
#include "PowerUp.h"

class Game
{
private:
	//variables
	sf::RenderWindow window;
	sf::Event event;
	sf::VideoMode videomode;

	//Music/soundeffects
	sf::Music musicMenu;
	sf::Music musicInGame;
	sf::Music musicDeath;

	//background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Objects
	Player* player;
	Enemy*  enemy;
	GUI* gui;
	Menu* menu;
	PowerUp* powerup;

	//Extras
	int selectedItem;
	int musicStageInt;
	int musicActionInt;
	bool endGame;


	float deltaX[6], deltaY[6], intersectX[6], intersectY[6];
	float powerUpDeltaX, powerUpDeltaY, powerUpIntersectX, powerUpIntersectY;

	//functions
	void initwindow();
	void initBackground();
	void initPlayer();
	void initEnemy();
	void initGUI();
	void initPowerUp();
	void initMenu();


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

	//Game functions
	void powerups();
	void update();
	void render();
	void initMusic();
	const sf::RenderWindow& getWindow() const;
	

};

