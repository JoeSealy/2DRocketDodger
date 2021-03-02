#include "GUI.h"
#include "stdafx.h"



void GUI::initVariables()
{
	this->powerTime = 0;
	this->countUp = 0.f;
	this->score = 0;
	this->scoreUp = 5.f;
	this->lives = 5.f;
	this->invincibility = false;
	this->addLivesBool = false;
	this->addScoreBool = false;
	this->slowedRocketBool = false;
}

void GUI::initFont()
{
	if (!Font.loadFromFile("Fonts/Bebas-Regular.ttf")) {
		std::cerr << "No font file found!" << std::endl;
	}
}

void GUI::initClock()
{
	this->timerText.setFont(this->Font);
	this->timerText.setPosition(10, 0);
	this->timerText.setCharacterSize(30);
}

void GUI::initScore()
{
	this->scoreText.setFont(this->Font);
	this->scoreText.setPosition(500, 0);
	this->scoreText.setCharacterSize(30);
}

void GUI::initLives()
{
	this->livesText.setFont(this->Font);
	this->livesText.setPosition(250, 0);
	this->livesText.setCharacterSize(30);
}

void GUI::initEndGame()
{
	this->endGameText.setFont(this->Font);
	this->endGameText.setPosition(220, 180);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setString("YOU DIED");
}

void GUI::initpowerUp()
{
	this->PowerUpText.setFont(this->Font);
	this->PowerUpText.setPosition(200, 60);
	this->PowerUpText.setFillColor(sf::Color::Yellow);
	this->PowerUpText.setCharacterSize(30);
}

float GUI::clockUpdate()
{
	return countUp = clock.getElapsedTime().asSeconds();
}

int GUI::scoreUpdate()
{
	if (this->countUp > this->scoreUp) {
		this->scoreUp += 5.f;
		this->score += 20.f;
		return this->score;
	}
}

int GUI::livesUpdate()
{
	return this->lives;	
}

void GUI::powerUpdate()
{
	if (this->invincibility)
	{
		std::srand(time(0));
		this->powerTime = this->powerClock.getElapsedTime().asSeconds();
		this->PowerUpText.setString("Invincibilty ON ");

		if (this->powerTime  >= 15)
		{
			this->PowerUpText.setString("");
			this->powerClock.restart();
			this->invincibility = false;
		}
	}

	if (this->addLivesBool) 
	{
		std::srand(time(0));
		this->powerTime = this->powerClock.getElapsedTime().asSeconds();
		this->PowerUpText.setString("Lives Added!");
		if (this->powerTime >= 3)
		{
			this->PowerUpText.setString("");
			this->powerClock.restart();
			this->addLivesBool = false;
		}
	}

	if (this->addScoreBool) 
	{
		std::srand(time(0));
		this->powerTime = this->powerClock.getElapsedTime().asSeconds();
		this->PowerUpText.setString("Plus 200 Score");
		if (this->powerTime >= 3)
		{
			this->PowerUpText.setString("");
			this->powerClock.restart();
			this->addScoreBool = false;
		}
	}

	if (this->slowedRocketBool)
	{
		std::srand(time(0));
		this->powerTime = this->powerClock.getElapsedTime().asSeconds();
		this->PowerUpText.setString("Rockets Slowed");
		if (this->powerTime >= 10)
		{
			this->PowerUpText.setString("");
			this->powerClock.restart();
			this->slowedRocketBool = false;
		}
	}


}

GUI::GUI()
{
	this->initVariables();
	this->initFont();
	this->initClock();
	this->initScore();
	this->initLives();
	this->initpowerUp();
	this->initEndGame();
}

GUI::~GUI()
{
}

void GUI::toClockString()
{
	std::ostringstream covertClock;
	covertClock << std::setprecision(2) << std::fixed << this->countUp;
	this->countUpStr = covertClock.str();
	timerText.setString("Timer: " + this->countUpStr);
}

void GUI::toScoreString()
{
	std::ostringstream covertScore;
	covertScore << this->score;
	this->scoreUpStr = covertScore.str();
	scoreText.setString("Score: " + this->scoreUpStr);
}

void GUI::toLivesString()
{
	std::ostringstream covertlives;
	covertlives << this->lives;
	this->livesStr = covertlives.str();
	livesText.setString("lives: " + this->livesStr);
}

void GUI::update()
{
	this->clockUpdate();
	this->toClockString();
	this->scoreUpdate();
	this->toScoreString();
	this->livesUpdate();
	this->toLivesString();
	this->powerUpdate();
}

void GUI::render(sf::RenderTarget & rTarget)
{
	rTarget.draw(timerText);
	rTarget.draw(scoreText);
	rTarget.draw(livesText);
	rTarget.draw(PowerUpText);
	
}
