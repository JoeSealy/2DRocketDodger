#pragma once
#include "stdafx.h"

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
private:
	//SFML Variables
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font Font;
	sf::Text menuText[MAX_NUMBER_OF_ITEMS];
	sf::Text titleText;

	//Variables
	int selectedItemIndex; //selects which option

	//Functions
	void initBackground();
	void initVariable();
	void initMenuText();
	void initMenuFont();

public:
	//Constructor/Deconstructor
	Menu();
	virtual ~Menu();

	//Varibales
	bool startGame;		//start game when true

	//Functions
	int getPressedItem();

	void moveUp();
	void moveDown();
	void update();
	void render(sf::RenderTarget& rTarget);
};

