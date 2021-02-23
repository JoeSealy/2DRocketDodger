#include "GUI.h"
#include "stdafx.h"



void GUI::initVariables()
{
	this->countUp = 0.f;
	this->score = 0.f;
	this->scoreUp = 5.f;
	this->lives = 5.f;
}

void GUI::initFont()
{
	if (!timerFont.loadFromFile("Fonts/Bebas-Regular.ttf")) {
		std::cerr << "No font file found!" << std::endl;
	}

	if (!scoreFont.loadFromFile("Fonts/Bebas-Regular.ttf")) {
		std::cerr << "No font file found!" << std::endl;
	}

	if (!livesFont.loadFromFile("Fonts/Bebas-Regular.ttf")) {
		std::cerr << "No font file found!" << std::endl;
	}
}

void GUI::initClock()
{
	this->timerText.setFont(timerFont);
	this->timerText.setPosition(10, 0);
	this->timerText.setCharacterSize(30);

}

void GUI::initScore()
{
	this->scoreText.setFont(scoreFont);
	this->scoreText.setPosition(600, 0);
	this->scoreText.setCharacterSize(30);
}

void GUI::initLives()
{
	this->livesText.setFont(livesFont);
	this->livesText.setPosition(300, 0);
	this->livesText.setCharacterSize(30);
}

float GUI::clockUpdate()
{
	return countUp = clock.getElapsedTime().asSeconds();
}
int GUI::scoreUpdate()
{
	this->clockUpdate();
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


GUI::GUI()
{
	this->initVariables();
	this->initFont();
	this->initClock();
	this->initScore();
	this->initLives();
}

GUI::~GUI()
{
}

void GUI::toClockString()
{
	std::ostringstream covertClock;
	covertClock << std::setprecision(2) << std::fixed << this->countUp;
	this->countUpStr = covertClock.str();
	timerText.setString(this->countUpStr);
}

void GUI::toScoreString()
{
	std::ostringstream covertScore;
	covertScore << this->score;
	this->scoreUpStr = covertScore.str();
	scoreText.setString(this->scoreUpStr);
}

void GUI::toLivesString()
{
	std::ostringstream covertlives;
	covertlives << this->lives;
	this->livesStr = covertlives.str();
	livesText.setString(this->livesStr);
}


void GUI::update()
{
	this->clockUpdate();
	this->toClockString();
	this->scoreUpdate();
	this->toScoreString();
	this->livesUpdate();
	this->toLivesString();
}

void GUI::render(sf::RenderTarget & rTarget)
{
	rTarget.draw(timerText);
	rTarget.draw(scoreText);
	rTarget.draw(livesText);
}
