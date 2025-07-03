#pragma once
#include "Creature.h"
#include "Room.h"
#include "Game.h"
#include <sstream>

class Game;

class Player : public Creature
{
public:

	Game* game;
	Room* currentRoom;
	Player(const std::string& name, const std::string& description, Room* startRoom, const Stats& playerStats);


	//all the actions player can do
	void PrintMap();
	void PrintStats();
	void Look(Room* currentRoom);
	void Movement(std::string argument);
	void Check(std::string argument);
	void Pick(std::string argument);
	void Drop(std::string argument);
	void Open(std::string argument);
	void Store(std::string argument);
	void Take(std::string argument);
	void Attack(const std::string& targetName);
	void MoveTo(Room* destination);

	void Update(const std::string& input);
	
	void ParseCommand(const std::string& input);



};

