#include "Player.h"

Player::Player(const std::string& name, const std::string& description, Room* startRoom, const Stats& playerStats)
	: Creature(EntityType::PLAYER, name, description, {},
		playerStats.health, playerStats.power, playerStats.defense, playerStats.luck),
	currentRoom(startRoom)
{
}

void Player::Update() 
{

}

void Player::ParseCommand(const std::string& input)
{
	std::istringstream iss(input);
	std::string command, argument;
	iss >> command >> argument;

	if (command == "go") {
		Direction dir;

		if (argument == "north") dir = Direction::NORTH;
		else if (argument == "south") dir = Direction::SOUTH;
		else if (argument == "east") dir = Direction::EAST;
		else if (argument == "west") dir = Direction::WEST;
		else {
			std::cout << "Unknown direction.\n";
			return;
		}

		bool moved = false;
		for (Door* door : currentRoom->doors) {
			if (door->GetDirection() == dir) {
				MoveTo(door->GetDestination());
				std::cout << "You move " << argument << ".\n";
				currentRoom->PrintDescription();
				moved = true;
				break;
			}
		}

		if (!moved)
			std::cout << "You can't go that way.\n";
	}
	else if (command == "look") {
		Look(currentRoom);
	}
	else if (command == "inventory") {
		ListInventory();
	}
	else if (command == "map") {
		PrintMap();
	}
	else if (command == "stats") {
		PrintStats();
	}
	else {
		std::cout << "I don't understand that command.\n";
	}
}

void Player::Look(Room* currentRoom) 
{
	std::cout << "You are in the " << currentRoom->name << "\n";
	currentRoom->ListInventory();
}

void Player::PrintMap() 
{
	std::cout << R"(
+---------+
|  Patio  |
+----+----+
     |     
     |     
+----+----+
|  Castle |
+---------+
)" << std::endl;
}

void Player::PrintStats() 
{
	std::cout << "Health: " << stats.health << "\n";
	std::cout << "Power: " << stats.power << "\n";
	std::cout << "Defense: " << stats.defense << "\n";
	std::cout << "Luck: " << stats.luck << "\n";
}

void Player::Loot() 
{

}

void Player::MoveTo(Room* destination) 
{
	currentRoom = destination;
}