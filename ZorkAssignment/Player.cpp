#include "Player.h"
#include "Item.h"

Player::Player(const std::string& name, const std::string& description, Room* startRoom, const Stats& playerStats)
	: Creature(EntityType::PLAYER, name, description, {},
		playerStats.health, playerStats.power, playerStats.defense, playerStats.luck),
	currentRoom(startRoom)
{
}

void Player::Update(const std::string& input) 
{
	ParseCommand(input);
}

void Player::ParseCommand(const std::string& input)
{
	std::istringstream iss(input);
	std::string command, argument;
	iss >> command >> argument;

	if (command == "go") {
		Movement(argument);
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
	else if (command == "check") {
		Check(argument);
	}
	else if (command == "pick") {
		Pick(argument);
	}
	else if (command == "drop") {
		Drop(argument);
	}
	else if (command == "open") {
		
		Open(argument);
	}
	else if (command == "store") {
		Store(argument);
	}
	else if (command == "take") {
		Take(argument);
	
	}
	else if (command == "attack") {
		Attack(argument);
	}
	else 
	{
		std::cout << "I don't understand that command.\n";
	}
}

void Player::Look(Room* currentRoom) 
{
	std::cout << "You are in " << currentRoom->name << "\n";
	currentRoom->ListInventory();

	if (currentRoom->name == "The Castle Gate") 
	{
		std::cout << "YAHOO!\n";
	}
}

void Player::PrintMap() 
{
	std::cout << R"(
             +--------+    +---+----+ +---+----+
             | Garden |    |Barracks|-|Latrines|
             +---+----+    +---+----+ +---+----+
                 |             |
+----------+ +----------+ +----------+
|  Stable  |-|  Patio   |-|  Armory  |
+----------+ +----------+ +----------+
                  |
             +----+----+
             |Cstl Gate|
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

void Player::MoveTo(Room* destination) 
{
	currentRoom = destination;
}

void Player::Movement(std::string argument)
{
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
			std::cout << "You moved to " << argument << ".\n";
			currentRoom->PrintDescription();
			moved = true;
			break;
		}
	}

	if (!moved)
		std::cout << "You can't go that way.\n";

}

void Player::Check(std::string argument) 
{
	if (argument.empty()) {
		std::cout << "Check what?\n";
		return;
	}

	// Search player's inventory first
	for (Entity* e : inventory) {
		if (e->name == argument) {
			std::cout << e->description << std::endl;
			return;
		}
	}

	// Search current room inventory
	for (Entity* e : currentRoom->inventory) {
		if (e->name == argument) {
			std::cout << e->description << std::endl;
			return;
		}
	}

	std::cout << "There is no " << argument << " here or in your inventory.\n";
}

void Player::Pick(std::string argument)
{
	for (Entity* e : currentRoom->inventory) {
		if (e->type == EntityType::ITEM && e->name == argument) {
			Item* item = dynamic_cast<Item*>(e);
			if (item)
			{
				if (!item->isPortable) {
					std::cout << "You can't carry the " << item->name << ".\n";
					return;
				}
			}
			AddToInventory(e);
			currentRoom->RemoveFromInventory(e);
			std::cout << "You picked up the " << e->name << ".\n";
			return;
		}
	}
	std::cout << "There is no such item here.\n";
}

void Player::Drop(std::string argument) 
{
	for (Entity* e : inventory) {
		if (e->type == EntityType::ITEM && e->name == argument) {
			RemoveFromInventory(e);
			currentRoom->AddToInventory(e);
			std::cout << "You dropped the " << e->name << ".\n";
			return;
		}
	}
	std::cout << "You don't have that item.\n";

}

void Player::Open(std::string argument)
{
	if (argument == "chest") {
		for (Entity* e : currentRoom->inventory) {
			if (e->type == EntityType::ITEM && e->name == "chest") {
				if (e->inventory.empty()) {
					std::cout << "The chest is empty.\n";
				}
				else {
					std::cout << "The chest contains:\n";
					for (Entity* item : e->inventory) {
						std::cout << "- " << item->name << std::endl;
					}
				}
				return;
			}
		}
		std::cout << "There is no chest here.\n";
	}
	else {
		std::cout << "You can't open that.\n";
	}
}

void Player::Store(std::string argument)
{
	if (argument.empty()) {
		std::cout << "Store what?\n";
		return;
	}

	// Look for the item in the player's inventory
	Entity* itemToStore = nullptr;
	for (Entity* e : inventory) {
		if (e->name == argument && e->type == EntityType::ITEM) {
			itemToStore = e;
			break;
		}
	}

	if (!itemToStore) {
		std::cout << "You don't have that item.\n";
		return;
	}

	// Look for the chest in the room
	for (Entity* e : currentRoom->inventory) {
		if (e->name == "chest" && e->type == EntityType::ITEM) {
			e->inventory.push_back(itemToStore);
			RemoveFromInventory(itemToStore);
			std::cout << "You stored the " << argument << " in the chest.\n";
			return;
		}
	}

	std::cout << "There is no chest here.\n";
}

void Player::Take(std::string argument) 
{
	for (Entity* e : currentRoom->inventory) {
		if (e->type == EntityType::ITEM && e->name == "chest") {
			// Found chest
			for (Entity* item : e->inventory) {
				if (item->name == argument) {
					e->RemoveFromInventory(item);
					AddToInventory(item);
					std::cout << "You took the " << item->name << " from the chest.\n";
					return;
				}
			}
			std::cout << "The chest doesn't contain that item.\n";
			return;
		}
	}
	std::cout << "There is no chest here.\n";
}

void Player::Attack(const std::string& targetName)
{
	for (Entity* e : currentRoom->inventory) {
		if (e->type == EntityType::ENEMY) {
			Creature* enemy = dynamic_cast<Creature*>(e);
			if (enemy && (enemy->name == targetName || targetName.empty())) {
				int damage = stats.power - enemy->stats.defense;
				if (damage < 0) damage = 0;

				std::cout << "You attack the " << enemy->name << " doing " << damage << " damage!\n";
				enemy->TakeDamage(damage);


				if (enemy->stats.health > 0) {
					std::cout << "The " << enemy->name << " has " << enemy->stats.health << " HP left.\n";

					int retaliation = enemy->stats.power - stats.defense;
					if (retaliation < 0) retaliation = 0;
					stats.health -= retaliation;

					std::cout << "The " << enemy->name << " strikes back doing " << retaliation << " damage!\n";
					if (stats.health > 0)
						std::cout << "You have " << stats.health << " HP left.\n";
					else
						std::cout << "You have died...\n";
				}
				if (!enemy->stats.isAlive()) {
					std::cout << "You have defeated the " << enemy->name << "!\n";

					delete enemy;
				}
				return;
			}
		}
	}
	std::cout << "There's no such enemy here.\n";
}
