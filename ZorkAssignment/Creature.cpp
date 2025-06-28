#include "Creature.h"


Creature::Creature(EntityType t, const std::string& n, const std::string& d,
	const std::vector<Entity*>& items, int health, int power) : Entity(t, n, d, items) 
{
	type = t;
	name = n;
	description = d;
	inventory = items;

	stats.health = health;
	stats.power = power;
}

Creature::~Creature()
{
	std::cout << "Creature Destructor called!\n";
}

void Creature::TakeDamage(int amount) 
{
	stats.health -= amount;
}

void Creature::Heal(int amount)
{
	stats.health += amount;
}

void Creature::DropInventory()
{

}

void Creature::OnDeath()
{
	
}

void Creature::Update()
{

}
