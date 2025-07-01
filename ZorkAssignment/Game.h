#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <conio.h>  // for _kbhit and _getch
#include "Creature.h"
#include "Room.h"
#include "Player.h"
#include "Door.h"
#include "Item.h"


class Game
{
private:
	// Global private variables (Attributes) to use in different member functions
	bool isRunning;
	std::vector<Entity*> entities;

	std::chrono::steady_clock::time_point startTime;

public:
	// Constructor/Destructor
	Game();
	~Game();

	// Member Functions
	void Initialize();
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Output();
	void GetTime();
	void Stop();
	void ConnectRooms(Room* from, Room* to, Direction dir, bool bidirectional = true);

};

