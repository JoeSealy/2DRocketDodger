#include "GUI.h"
#include "stdafx.h"



void GUI::initVariables()					// initialise variables
{
	this->powerTime = 0;
	this->countUp = 0;
	this->score = 0;
	this->scoreUp = 5;
	this->lives = 5;
	this->invincibility = false;
	this->addLivesBool = false;
	this->addScoreBool = false;
	this->slowedRocketBool = false;
	this->platMessage = true;
}

void GUI::initFont()						// initialise font
{
	if (!Font.loadFromFile("Fonts/Bebas-Regular.ttf")) {
		std::cerr << "No font file found!" << std::endl;
	}
}

void GUI::initClock()						// initialise clock	text
{
	this->timerText.setFont(this->Font);
	this->timerText.setPosition(10, 0);
	this->timerText.setCharacterSize(30);
}

void GUI::initScore()						//initialise score	text
{
	this->scoreText.setFont(this->Font);
	this->scoreText.setPosition(500, 0);
	this->scoreText.setCharacterSize(30);
}

void GUI::initLives()						//initialise lives text
{
	this->livesText.setFont(this->Font);
	this->livesText.setPosition(250, 0);
	this->livesText.setCharacterSize(30);
}

void GUI::initPlat()						//initialise lives text
{
	this->platText.setFont(this->Font);
	this->platText.setPosition(100, 100);
	this->platText.setFillColor(sf::Color::Red);
	this->platText.setCharacterSize(50);
}

void GUI::initEndGame()						//initialise end game text
{
	this->endGameText.setFont(this->Font);
	this->endGameText.setPosition(220, 180);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setString("YOU DIED");
}

void GUI::initpowerUp()						//initialise power up text
{
	this->PowerUpText.setFont(this->Font);
	this->PowerUpText.setPosition(200, 60);
	this->PowerUpText.setFillColor(sf::Color::Yellow);
	this->PowerUpText.setCharacterSize(30);
}

float GUI::clockUpdate()					//return clock number
{
	return countUp = clock.getElapsedTime().asSeconds();
}

int GUI::scoreUpdate()						//updates score 
{
	if (this->countUp > this->scoreUp) {
		this->scoreUp += 5;
		this->score += 20;
		return this->score;
	}
}



int GUI::livesUpdate()						//returns lives
{
	return this->lives;	
}

int GUI::platUpdate()
{
		plat = 10 - this->countUp;
		return plat;
	
}

void GUI::powerUpdate()						//updates power up text and dissapear overtime
{
	if (this->invincibility)				//invincibility text
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


	if (this->addLivesBool)						//add lives text
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


	if (this->addScoreBool)						//added score text
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


	if (this->slowedRocketBool)					//slowed rockets text
	{
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


GUI::GUI()				//constuctor
{
	this->initVariables();
	this->initFont();
	this->initClock();
	this->initScore();
	this->initLives();
	this->initpowerUp();
	this->initEndGame();
	this->initPlat();
}

GUI::~GUI()				//deconstructor
{
}

void GUI::toClockString()												//turns the clock number to string to show on screen
{
	std::ostringstream covertClock;
	covertClock << std::setprecision(2) << std::fixed << this->countUp;
	this->countUpStr = covertClock.str();
	timerText.setString("Timer: " + this->countUpStr);
}

void GUI::toScoreString()												//turns the score number to string to show on screen
{
	std::ostringstream covertScore;
	covertScore << this->score;
	this->scoreUpStr = covertScore.str();
	scoreText.setString("Score: " + this->scoreUpStr);
}

void GUI::toLivesString()												//turns the lives number to string to show on screen
{
	std::ostringstream covertlives;
	covertlives << this->lives;
	this->livesStr = covertlives.str();
	livesText.setString("lives: " + this->livesStr);
}

void GUI::toPlatString()
{
	std::ostringstream covertPlat;
	covertPlat << this->plat;
	this->platStr = covertPlat.str();
	platText.setString("Get to a platform: " + this->platStr);
}


void GUI::update()							//update function
{
	this->clockUpdate();
	this->toClockString();
	this->scoreUpdate();
	this->toScoreString();
	this->livesUpdate();
	this->toLivesString();
	this->powerUpdate();

	this->platUpdate();
	this->toPlatString();
}

void GUI::render(sf::RenderTarget & rTarget)		//render targets
{	
	if (this->clockUpdate() <= 10)
	{
		rTarget.draw(platText);
	}
	rTarget.draw(timerText);
	rTarget.draw(scoreText);
	rTarget.draw(livesText);
	rTarget.draw(PowerUpText);
}
