#pragma once
#include "stdafx.h"

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
private:
	sf::Font menuFont;
	sf::Text menuText;

	int selectedItemIndex;

public:
	Menu();
	virtual ~Menu();

	void moveUp();
	void moveDown();
};

