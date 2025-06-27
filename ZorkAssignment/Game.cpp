#include "Game.h"

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
	startTime = std::chrono::steady_clock::now();
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
			GetTime();
			Stop();  // Exits the loop
		}
	}
}


void Game::Update()
{
	ProcessInput();
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
		Update();
		Output();

	}
}

void Game::Stop()
{
	isRunning = false;
}

void Game::GetTime() 
{
	auto endTime = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

	int hours = elapsed / 3600;
	int minutes = (elapsed % 3600) / 60;
	int seconds = elapsed % 60;

	std::cout << "Played time: "
		<< hours << "h "
		<< minutes << "m "
		<< seconds << "s\n";
}
