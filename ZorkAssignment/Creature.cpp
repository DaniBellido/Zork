#include "Creature.h"


Creature::Creature(EntityType t, const std::string& n, const std::string& d, const std::vector<Entity*>& items, int health, int power, int defense, int luck) : Entity(t, n, d, items) 
{
	type = t;
	name = n;
	description = d;
	inventory = items;

	stats.health = health;
	stats.power = power;
	stats.defense = defense;
	stats.luck = luck;
}

Creature::~Creature()
{
	//std::cout << "Creature Destructor called!\n";
}

void Creature::TakeDamage(int amount) 
{
	stats.health -= amount;
	std::cout << name << " took " << amount << " damage. Health now " << stats.health << "\n";

	if (stats.health <= 0) {
		OnDeath();
	}
}

void Creature::Heal(int amount)
{
	stats.health += amount;
}

void Creature::DropInventory()
{
	if (location) {
		std::cout << name << " dropped items:\n";
		for (Entity* item : inventory) {
			std::cout << " - " << item->name << "\n";
			location->AddToInventory(item);
		}
		inventory.clear();
	}
}

void Creature::OnDeath()
{
	std::cout << name << " has died.\n";
	DropInventory();

	if (location) {
		location->RemoveFromInventory(this); // remove the creature from the room
	}


	
}

void Creature::Update()
{

}
