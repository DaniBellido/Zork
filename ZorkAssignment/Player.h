#pragma once
#include "Creature.h"
#include "Room.h"
#include <sstream>

class Player : public Creature
{
public:
	Room* currentRoom;

	Player(const std::string& name, const std::string& description, Room* startRoom, const Stats& playerStats);


	//all the actions player can do
	void Loot();
	void PrintMap();
	void PrintStats();
	void Look(Room* currentRoom);

	void MoveTo(Room* destination);

	void Update() override;
	
	void ParseCommand(const std::string& input);


};

