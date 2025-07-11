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
public:
	// Global private variables (Attributes) to use in different member functions
	bool isRunning;
	bool isGameOver = false;
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
	void Update();
	void GetTime();
	void Stop();
	void ConnectRooms(Room* from, Room* to, Direction dir, bool bidirectional = true);
	void GameOver();
	void CleanUp();

};

