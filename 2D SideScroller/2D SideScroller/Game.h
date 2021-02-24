#pragma once
#include "Player.h"
#include "Enemy.h"
#include "GUI.h"
#include "stdafx.h"

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

	//Objects
	Player* player;
	Enemy*  enemy;
	GUI* gui;

	//Extras
	int selectedItem;
	bool endGame;
	int musicStageInt;
	int musicActionInt;

	//functions
	void initwindow();
	void initPlayer();
	void initEnemy();
	void initGUI();


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

	//Game functions
	void update();
	void render();
	void initMusic();
	const sf::RenderWindow& getWindow() const;
	

};

