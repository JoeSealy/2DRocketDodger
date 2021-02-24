#include "Game.h"

//////////////Private//////////////



void Game::initwindow()
{
	
	this->window.create(sf::VideoMode(640, 480), "Rocket Dodge", sf::Style::Titlebar | sf::Style::Close);

	this->window.setFramerateLimit(64);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemy()
{
	this->enemy = new Enemy();
}

void Game::initGUI()
{
	this->gui = new GUI();
}

void Game::initMusic()
{
	musicMenu.openFromFile("Music/MusicMenu.wav");
	musicMenu.setLoop(true);
	musicMenu.setVolume(10);

	musicInGame.openFromFile("Music/MusicInGame.wav");
	musicInGame.setLoop(true);
	musicInGame.setVolume(10);

	musicDeath.openFromFile("Music/MusicDeath.wav");
	musicDeath.setVolume(10);

	musicRunning.openFromFile("Music/MusicRunning.wav");
	musicRunning.setVolume(10);

	musicJumping.openFromFile("Music/MusicJumping.wav");
	musicJumping.setVolume(10);

	this->musicStageInt = 1;
}
///////////////////Public////////////////////

//conscructor
Game::Game()
{
	this->initwindow();
	this->initPlayer();
	this->initEnemy();
	this->initGUI();
	this->initMusic();
}

//deconstructor
Game::~Game()
{
	delete this->enemy;
	delete this->player;
	delete this->gui;
}

//accessors

const bool Game::getWindowIsOpen() const
{
	return this->window.isOpen() /*&& this->endGame == false*/;
}

const bool & Game::getEndGame() const
{
	return this->endGame;
}

//Game functions
void Game::playerUpdate()
{
	this->player->update();
}

void Game::playerRender()
{
	this->player->render(this->window);
}

void Game::enemyUpdate()
{
	this->enemy->update();
}

void Game::enemyRender()
{
	this->enemy->render(this->window);
}

void Game::guiUpdate()
{
	this->gui->update();

}

void Game::guiRender()
{
	this->gui->render(this->window);

	if (this->gui->lives <= 0)
	{
		this->endGame = true;
	}
}

void Game::collisionUpdate()
{
	//------------------------------------------PLAYER COLLISION WITH WINDOW---------------------------------------------------


	//bottom of screen collision
	if (this->player->getPosition().y + this->player->windowBounds().height > this->window.getSize().y)
	{
		this->player->velocityReset();
		this->player->positionSet(
			this->player->getPosition().x,
			this->window.getSize().y -
			this->player->windowBounds().height);
	}
	//top side screen collision
	if (this->player->getPosition().y + this->player->windowBounds().height < this->player->windowBounds().height)
	{
		this->player->velocityReset();
		this->player->positionSet(
			this->player->getPosition().x,
			0.f);
	}

	//right side screen collision
	if (this->player->getPosition().x + this->player->windowBounds().width > this->window.getSize().x)
	{
		this->player->velocityReset();
		this->player->positionSet(
			this->window.getSize().x -
			this->player->windowBounds().width,
			this->player->getPosition().y);
	}
	//left side screen collision
	if (this->player->getPosition().x + this->player->windowBounds().width < this->player->windowBounds().width)
	{
		this->player->velocityReset();
		this->player->positionSet(
			0.f, this->player->getPosition().y);
	}



	//----------------------------------------------ENEMY COLLISION WITH WINDOW---------------------------------------------------------------------

	for (int i(0); i < 6; i++) {
		if (this->enemy->rocket_list[i].getPosition().x + this->enemy->windowBounds().width < this->enemy->windowBounds().width)
		{
			this->enemy->rocketNumber = i;
			this->enemy->positionSet(
				this->window.getSize().x, this->enemy->rocket_list[i].getPosition().y);
		}
	}
}
	

bool Game::collisionCheck()
{
	float deltaX[6], deltaY[6], intersectX[6], intersectY[6];

	for (int i(0); i < 6; i++) {
		deltaX[i] = this->player->getPosition().x - this->enemy->rocket_list[i].getPosition().x;
		deltaY[i] = this->player->getPosition().y - this->enemy->rocket_list[i].getPosition().y;
		intersectX[i] = abs(deltaX[i]) - ((this->enemy->windowBounds().width / 2.f) + (this->player->windowBounds().width / 2.f));
		intersectY[i] = abs(deltaY[i]) - ((this->enemy->windowBounds().height / 2.f) + (this->player->windowBounds().height / 2.f));

		if (intersectX[i] < 0.f && intersectY[i] < 0.f)
		{
			this->gui->lives -= 1;
			this->enemy->rocketNumber = i;
			this->enemy->positionSet(this->window.getSize().x, this->enemy->rocket_list[i].getPosition().y);

			return true;
		}
	}
	return false;
}


void Game::update()
{
	while (this->window.pollEvent(this->event))
	{
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window.close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window.close();
			break;
		case sf::Event::KeyReleased:
			if (
				this->event.key.code == sf::Keyboard::W ||
				this->event.key.code == sf::Keyboard::A ||
				this->event.key.code == sf::Keyboard::S ||
				this->event.key.code == sf::Keyboard::D
				)
			{
				this->player->resetAnimTimer();
			}
			break;
		}

	}



	if (!this->endGame)
	{
		this->guiUpdate();
		this->enemyUpdate();
		this->playerUpdate();
		this->collisionCheck();
		this->collisionUpdate();
		if (this->musicStageInt == 1)
		{
			this->musicInGame.play();
			this->musicStageInt = 2;
		}
	}
}

void Game::render()
{
	//Game Objects rendered from here
	 
	this->window.clear(sf::Color(47, 79, 79, 255));
	//Draws

	this->guiRender();

	this->enemyRender();

	this->playerRender();

	if (this->endGame) 
	{
		if (musicStageInt == 2) {
			this->musicInGame.pause();
			this->musicDeath.play();
			this->musicStageInt = 3;
		}

		this->window.clear(sf::Color::Black);
		this->window.draw(this->gui->endGameText);
	}

	this->window.display();


}



const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

