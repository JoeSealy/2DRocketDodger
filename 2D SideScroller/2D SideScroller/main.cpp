#include "Game.h"

int main()
{
	Game game;


	while (game.getWindowIsOpen())
	{
		//Updates Game			
		game.update();

		//Renders Game
		game.render();

	}

	return 0;
}