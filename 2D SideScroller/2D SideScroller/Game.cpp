#include "Game.h"

//////////////Private//////////////

void Game::initwindow()				//initialise window
{
	
	this->window.create(sf::VideoMode(640, 480), "Rocket Dodge", sf::Style::Titlebar | sf::Style::Close);

	this->window.setFramerateLimit(64);
}

void Game::initPlayer()				//initialise player
{
	this->player = new Player();
}

void Game::initEnemy()				//initialise enemy
{
	this->enemy = new Enemy();
}

void Game::initGUI()				//initialise GUI
{
	this->gui = new GUI();
}

void Game::initMenu()				//initialise menu
{	
	this->menu = new Menu();
}

void Game::initPowerUp()			//initialise power up
{
	this->powerup= new PowerUp();
}

void Game::initPlatform()			//initialise power up
{
	this->platform = new Platform();
}

void Game::initBackground()
{
	this->background = new Background();
}

void Game::initMusic()				//initialise music
{
	this->musicMenu.openFromFile("Music/MusicMenu.wav");
	this->musicMenu.setLoop(true);
	this->musicMenu.setVolume(10);

	this->musicInGame.openFromFile("Music/MusicInGame.wav");
	this->musicInGame.setLoop(true);
	this->musicInGame.setVolume(10);

	this->musicDeath.openFromFile("Music/MusicDeath.wav");
	this->musicDeath.setVolume(10);

	this->musicStageInt = 0;
}

///////////////////Public////////////////////

//conscructor
Game::Game()	
{
	this->initwindow();
	this->initMenu();
	this->initPlayer();
	this->initEnemy();
	this->initGUI();
	this->initPowerUp();
	this->initMusic();
	this->initPlatform();
	this->initBackground();
}

//deconstructor
Game::~Game()
{
	delete this->menu;
	delete this->enemy;
	delete this->player;
	delete this->gui;
	delete this->powerup;
	delete this->platform;
	delete this->background;
}

//accessors

const bool Game::getWindowIsOpen() const
{
	return this->window.isOpen() /*&& this->endGame == false*/;
}

const bool & Game::getEndGame() const			//end game true and false
{
	return this->endGame;
}

//Game functions

void Game::playerUpdate()						//update player
{
	this->player->update();
}

void Game::playerRender()						//render player
{
	this->player->render(this->window);
}

void Game::enemyUpdate()						//update enemy
{
	this->enemy->update();
}

void Game::enemyRender()						//render enemy
{
	this->enemy->render(this->window);
}

void Game::guiUpdate()							//update GUI
{
	this->gui->update();

	if (this->gui->lives <= 0)				//die at 0 lives
	{
		this->endGame = true;
	}
}

void Game::guiRender()							//render GUI
{
	this->gui->render(this->window);
}

void Game::MenuUpdate()							//update menu
{
	this->menu->update();
}

void Game::MenuRender()							//render menu
{
	this->menu->render(this->window);
}

void Game::powerUpUpdate()						//update power
{
	this->powerup->update();
}

void Game::powerUpRender()						//render power up
{
	this->powerup->render(this->window);
}

void Game::platformUpdate()						//update platform
{
	this->platform->update();
}

void Game::platformRender()						//render platform
{
	this->platform->render(this->window);
}

void Game::BackgroundUpdate()						//update background
{
	this->background->update();
}

void Game::backgroundRender()						//render background
{
	this->background->render(this->window);
}

void Game::collisionUpdate()
{
	//------------------------------------------PLAYER COLLISION WITH WINDOW---------------------------------------------------


	//bottom of screen collision

	if (this->player->getPosition().y + this->player->windowBounds().height > this->window.getSize().y)
	{
		if (this->gui->clockUpdate() > 10.f)
		{
			this->endGame = true;
		}
		else
		{
			this->player->velocityReset();
			this->player->positionSet(
				this->player->getPosition().x,
				this->window.getSize().y -
				this->player->windowBounds().height);
		}
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

	for (int i(0); i < 6; i++) {	//rockets hit left side of screen reset position
		if (this->enemy->rocket_list[i].getPosition().x + this->enemy->windowBounds().width < this->enemy->windowBounds().width)
		{
			this->enemy->rocketNumber = i;
			this->enemy->positionSet(600, this->enemy->rocket_list[i].getPosition().y);
		}
	}

	//-------------------------------------------------POWERUP COLLISION WITH WINDOW------------------------------------------------------------
	//power up hits bottom of screen and resets y coordinate
	if (this->powerup->getPosition().y + this->powerup->windowBounds().height > this->window.getSize().y)
	{
		this->powerup->positionSet(this->powerup->getPosition().x, -100.f);
		this->powerup->powerUpDrop = true;
	}

	//------------------------------------------------------PLATFORM COLLISION WITH WINDOW AND PLAYER-----------------------------------------------------
	for (int i(0); i < platform->platform_List.size(); i++)
	{								//platform hit bottom side of screen reset position
		if (this->platform->platform_List[i].getPosition().y > this->window.getSize().y)
		{
			this->platform->platformNumber = i;
			this->platform->positionSet(this->platform->platform_List[i].getPosition().x, -100.f);
		}
	}

	if(!this->player->dropDown)
	{
		for (int i(0); i < this->platform->platform_List.size(); i++)
		{
			if (this->platform->platform_List[i].getPosition().y > 0)
			{
				if (this->player->getPosition().y < this->platform->platform_List[i].getPosition().y - this->platform->platform_List[i].getGlobalBounds().height)
				{
					if ((this->player->getPosition().y + this->player->windowBounds().height > this->platform->platform_List[i].getPosition().y))
					{
						if (!(this->player->getPosition().x > this->platform->platform_List[i].getPosition().x + this->platform->platform_List[i].getGlobalBounds().width)
							&& !(this->player->getPosition().x + this->player->windowBounds().width < this->platform->platform_List[i].getPosition().x))
						{
							this->player->velocityReset();
							this->platform->platformNumber = i;
							this->player->positionSet(this->player->getPosition().x, this->platform->platform_List[i].getPosition().y - this->player->windowBounds().height);
						}
					}
				}
			}
		}
	}
}
	

bool Game::collisionCheck()
{
	if (this->gui->invincibility == false)						//enemy and player collide then reset rocket to right side of screen
	{
		for (int i(0); i < 6; i++) {
			this->deltaX[i] = this->player->getPosition().x - this->enemy->rocket_list[i].getPosition().x;
			this->deltaY[i] = this->player->getPosition().y - this->enemy->rocket_list[i].getPosition().y;
			this->intersectX[i] = abs(deltaX[i]) - ((this->enemy->windowBounds().width / 2.f) + (this->player->windowBounds().width / 2.f));
			this->intersectY[i] = abs(deltaY[i]) - ((this->enemy->windowBounds().height / 4.f) + (this->player->windowBounds().height / 4.f));

			if (intersectX[i] < 0.f && intersectY[i] < 0.f)
			{
				this->gui->lives -= 1;
				this->enemy->rocketNumber = i;
				this->enemy->positionSet(this->window.getSize().x, this->enemy->rocket_list[i].getPosition().y);

				return true;
			}
		}
	}
	//power up hits player and resets power up

	this->powerUpDeltaX = this->player->getPosition().x - this->powerup->getPosition().x;
	this->powerUpDeltaY = this->player->getPosition().y - this->powerup->getPosition().y;
	this->powerUpIntersectX = abs(powerUpDeltaX) - ((this->powerup->windowBounds().width / 2.f) + (this->player->windowBounds().width / 2.f));
	this->powerUpIntersectY = abs(powerUpDeltaY) - ((this->powerup->windowBounds().height / 2.f) + (this->player->windowBounds().height / 2.f));

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
	switch (this->powerup->randPowerUp())		//random power for power up
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

		break;
	case 3:
		this->gui->addLivesBool = true;
		this->gui->lives += 5;
		break;
	}
}

void Game::update()
{
	while (this->window.pollEvent(this->event))		//update keys 
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

			if (this->event.key.code == sf::Keyboard::S && !this->menu->startGame)
			{
				this->menu->moveDown();
			}
			break;
		case sf::Event::KeyReleased:

			if (this->event.key.code == sf::Keyboard::W) {
				this->player->resetAnimTimer();
				this->player->jumpSound = false;
				this->player->musicJumping.stop();
			}

			if (this->event.key.code == sf::Keyboard::A)
			{
				this->player->resetAnimTimer();
				this->player->runSound = false;
				this->player->musicRunning.pause();
			}

			if (this->event.key.code == sf::Keyboard::D)
			{
				this->player->resetAnimTimer();
				this->player->runSound = false;
				this->player->musicRunning.pause();
			}

			if (this->event.key.code == sf::Keyboard::S)
			{
				this->player->resetAnimTimer();
			}

			if (this->event.key.code == sf::Keyboard::Return) //menu
			{
				switch (this->menu->getPressedItem())
				{
				case 1:
					this->menu->startGame = true;
					break;
				case 2:
					//options
					break;
				case 3:
					this->window.close();
					break;
				}
			}

		}
	}
	
	if (!this->endGame)						//if end game is true death screen
	{
		if (this->menu->startGame == false)  //if start game is true start game if not menu screen
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
			this->enemyUpdate();
			this->platformUpdate();
			this->playerUpdate();
			this->BackgroundUpdate();
			this->powerUpUpdate();
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

	if (this->menu->startGame == false)				//menu screen
	{
		this->MenuRender();
	}
	else{

		this->backgroundRender();

		this->platformRender();

		this->powerUpRender();

		this->guiRender();
												//game screen
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
			this->window.draw(this->gui->endGameText);  //death screen
			this->window.draw(this->gui->scoreText);
		}
	}
	this->window.display();
	this->window.clear();
}


const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

