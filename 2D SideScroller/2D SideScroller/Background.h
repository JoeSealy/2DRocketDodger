#pragma once
#include "stdafx.h"
class Background
{
private:
	sf::Texture groundBackgroundTexture;
	sf::Texture spaceBackgroundTexture;
	sf::Texture deepSpaceBackgroundTexture;
	sf::Sprite groundBackgroundSprite;
	sf::Sprite spaceBackgroundSprite;
	sf::Sprite deepSpaceBackgroundSprite;
	sf::Vector2f backgroundVelocity;

	void initBackground();

	

	

public:

	Background();
	virtual ~Background();

	void BackgroundUpdate();

	void update();
	void render(sf::RenderTarget & rTarget);

};

