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
	sf::Music musicJumping;
	sf::Music musicRunning;

	//background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Objects
	Player* player;
	Enemy*  enemy;
	GUI* gui;
	Menu* menu;

	//Extras
	int selectedItem;
	int musicStageInt;
	int musicActionInt;
	bool endGame;

	//functions
	void initwindow();
	void initBackground();
	void initPlayer();
	void initEnemy();
	void initGUI();
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

	//Game functions
	void update();
	void render();
	void initMusic();
	const sf::RenderWindow& getWindow() const;
	

};

