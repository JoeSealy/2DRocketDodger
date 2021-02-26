#pragma once
#include "stdafx.h"

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
private:


	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font Font;
	sf::Text menuText[MAX_NUMBER_OF_ITEMS];
	sf::Text titleText;

	int selectedItemIndex;

	void initBackground();
	void initVariable();
	void initMenuText();
	void initMenuFont();

public:
	Menu();
	virtual ~Menu();

	bool startGame;

	int getPressedItem();
	void moveUp();
	void moveDown();

	void update();
	void render(sf::RenderTarget& rTarget);
};

