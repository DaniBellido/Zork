#include "Game.h"
#include <iostream>
#include <conio.h>  // for _kbhit and _getch




Game::Game()
{
	isRunning = false;
	std::cout << "Game Constructor called!\n";
}

Game::~Game()
{
	std::cout << "Game Destructor called!\n";
}


void Game::Initialize()
{
	// init game 
	isRunning = true;
	std::cout << "Initializing the game!\n";
}

void Game::Setup()
{
	//TODO: Create entities here

}

void Game::ProcessInput()
{
	if (_kbhit()) {
		int key = _getch();
		if (key == 27) { // ESC key
			std::cout << "ESC pressed. Exiting game loop.\n";
			Stop();  // Exits the loop
		}
	}
}


void Game::Update()
{

}

void Game::Output()
{
	

}

void Game::Run()
{
	Setup();

	// Game Loop
	while (isRunning)
	{
		ProcessInput();
		Update();
		Output();

	}
}

void Game::Stop()
{
	isRunning = false;
}
