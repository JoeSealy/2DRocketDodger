#pragma once
#include "stdafx.h"
class GUI
{
private:

	sf::Text timerText;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text PowerUpText;

	sf::Font Font;

	sf::Clock clock;
	sf::Clock powerClock;
	
	std::string countUpStr;
	std::string scoreUpStr;
	std::string livesStr;

	int scoreUp;
	int powerTime;

	void initVariables();
	void initFont();
	void initClock();
	void initScore();
	void initLives();
	void initEndGame();
	void initpowerUp();



public:
	GUI();
	virtual ~GUI();

	sf::Text endGameText;

	void toClockString();
	void toScoreString();
	void toLivesString();


	bool invincibility;
	bool addLivesBool;
	bool addScoreBool;
	bool slowedRocketBool;

	float countUp;
	int lives;
	int score;
	
	void powerUpdate();
	float clockUpdate();
	int scoreUpdate();
	int livesUpdate();

	void update();
	void render(sf::RenderTarget& rTarget);

};

