#include "Game.h"
#include "Room.h"
#include "Player.h"
#include "Door.h"

std::vector<Room*> pRooms;
std::vector<Door*> pDoors;
Player* pPlayer;

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
	
	pRooms.push_back(new Room(EntityType::ROOM, "Castle", "a huge old castle with a massive gate."));
	pRooms.push_back(new Room(EntityType::ROOM, "Patio", "a wide patio surrounded by high walls and some doors."));

	// Crear puerta entre Castle y Patio
	Door* door = new Door(Direction::NORTH, pRooms[0], pRooms[1], true);
	pDoors.push_back(door);
	pRooms[0]->doors.push_back(door);

	// Si es bidireccional, crear la inversa
	if (door->bidirectional) {
		Door* reverseDoor = new Door(Direction::SOUTH, pRooms[1], pRooms[0], true);
		pDoors.push_back(reverseDoor);
		pRooms[1]->doors.push_back(reverseDoor);
	}

	pRooms[0]->PrintDescription();

	Stats playerStats = { 100, 10, 5, 3 };
	pPlayer = new Player("Hero", "The brave adventurer", pRooms[0], playerStats);
	pPlayer->PrintStats();

	
}

void Game::ProcessInput()
{
	std::string input;
	std::cout << "\n> ";
	std::getline(std::cin, input);

	if (input == "exit" || input == "quit") {
		std::cout << "Exiting game.\n";
		GetTime();
		Stop();
		return;
	}

	pPlayer->ParseCommand(input);
}


void Game::Update()
{
	ProcessInput(); //This must be PlayerInput implemented in Player's class
	//delete some entities
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
	//delete entities
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
