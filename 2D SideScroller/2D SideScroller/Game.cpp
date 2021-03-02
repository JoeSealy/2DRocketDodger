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

void Game::initMenu()
{
	this->menu = new Menu();
}

void Game::initPowerUp()
{
	this->powerup= new PowerUp();
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

	this->musicStageInt = 0;
}

void Game::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Textures/background_InGame.png"))
	{
		std::cerr << "No font file found!" << std::endl;
	}
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->backgroundSprite.setScale(.5f, .9f);

}
///////////////////Public////////////////////

//conscructor
Game::Game()
{
	this->initwindow();
	this->initBackground();
	this->initMenu();
	this->initPlayer();
	this->initEnemy();
	this->initGUI();
	this->initPowerUp();
	this->initMusic();
}

//deconstructor
Game::~Game()
{
	delete this->menu;
	delete this->enemy;
	delete this->player;
	delete this->gui;
	delete this->powerup;
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

	if (this->gui->lives <= 0)
	{
		this->endGame = true;
	}
}

void Game::guiRender()
{
	this->gui->render(this->window);
}

void Game::MenuUpdate()
{
	this->menu->update();
}

void Game::MenuRender()
{
	this->menu->render(this->window);
}

void Game::powerUpUpdate()
{
	this->powerup->update();
}

void Game::powerUpRender()
{
	this->powerup->render(this->window);
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
	//-------------------------------------------------POWERUP COLLISION WITH WINDOW------------------------------------------------------------
	if (this->powerup->getPosition().y + this->powerup->windowBounds().height < this->window.getSize().y)
	{
		this->powerup->positionSet(this->powerup->getPosition().x, -100.f);
		this->powerup->powerUpDrop = true;
	}
}
	

bool Game::collisionCheck()
{
	if (this->gui->invincibility == false)
	{
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
	}

	powerUpDeltaX = this->player->getPosition().x - this->powerup->getPosition().x;
	powerUpDeltaY = this->player->getPosition().y - this->powerup->getPosition().y;
	powerUpIntersectX = abs(powerUpDeltaX) - ((this->powerup->windowBounds().width / 2.f) + (this->player->windowBounds().width / 2.f));
	powerUpIntersectY = abs(powerUpDeltaY) - ((this->powerup->windowBounds().height / 2.f) + (this->player->windowBounds().height / 2.f));

	if (powerUpIntersectX < 0.f && powerUpIntersectY < 0.f)
	{
		this->powerups();
		this->powerup->positionSet(this->powerup->getPosition().x, -100.f);
		this->powerup->powerUpDrop = true;
		return true;
	}

	return false;
}

void Game::powerups()
{
	switch (this->powerup->randPowerUp())
	{
	case 0:
		this->gui->addScoreBool = true;
		this->gui->score += 200;
		break;
	case 1:
		this->gui->invincibility = true;
		break;
	case 2:
		this->gui->slowedRocketBool = true;
		this->enemy->slowSpeed;
		break;
	case 3:
		this->gui->addLivesBool = true;
		this->gui->lives += 5;
		break;
	}
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
				{
					this->window.close();
				}

				if (this->event.key.code == sf::Keyboard::W && !this->menu->startGame)
				{
					this->menu->moveUp();
				}

				if (this->event.key.code == sf::Keyboard::S & !this->menu->startGame)
				{
					this->menu->moveDown();
				}
				break;


			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::W || sf::Keyboard::A || sf::Keyboard::S || sf::Keyboard::D :
					
						this->player->resetAnimTimer();
					
						break;

					case sf::Keyboard::Return:

						switch (this->menu->getPressedItem())
						{
						case 1:
							this->menu->startGame = true;
							break;
						case 2:
							//options
							break;
						case 3:
							window.close();
							break;
						}
				}
		}

	}
	
	if (!this->endGame)
	{
		if (this->menu->startGame == false) 
		{
			this->MenuUpdate();
			if (this->musicStageInt == 0)
			{
					this->musicMenu.play();
					this->musicStageInt = 1;
			}
		}
		else
		{
			this->guiUpdate();
			this->powerUpUpdate();
			this->enemyUpdate();
			this->playerUpdate();
			this->collisionCheck();
			this->collisionUpdate();
			if (this->musicStageInt == 1)
			{
				this->musicInGame.play();
				this->musicMenu.pause();
				this->musicStageInt = 2;
			}
		}
	}
	
}

void Game::render()
{
	this->window.clear(sf::Color(47, 79, 79, 255));
	if (this->menu->startGame == false) {
		this->MenuRender();
	}
	else{
		this->window.draw(backgroundSprite);

		this->powerUpRender();

		this->enemyRender();

		this->playerRender();

		this->guiRender();

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
	}
	this->window.display();
}


const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

