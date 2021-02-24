#pragma once
#include "stdafx.h"
class GUI
{
private:

	sf::Text timerText;
	sf::Text scoreText;
	sf::Text livesText;

	sf::Font Font;

	sf::Clock clock;
	
	std::string countUpStr;
	std::string scoreUpStr;
	std::string livesStr;

	int score;
	int scoreUp;

	void initVariables();
	void initFont();
	void initClock();
	void initScore();
	void initLives();
	void initEndGame();



public:
	GUI();
	virtual ~GUI();

	sf::Text endGameText;

	void toClockString();
	void toScoreString();
	void toLivesString();

	float countUp;
	int lives;
	
	float clockUpdate();
	int scoreUpdate();
	int livesUpdate();

	void update();
	void render(sf::RenderTarget& rTarget);

};

