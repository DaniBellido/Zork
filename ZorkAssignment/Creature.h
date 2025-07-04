#pragma once
#include "Entity.h"
#include "Room.h"

struct Stats {
	int health;
	int power;
	int defense;
	int luck;
	bool isAlive() const { return health > 0; }
};

class Creature : public Entity
{
public:
	Stats stats;
	Room* location;
	Creature(EntityType t, const std::string& n, const std::string& d, const std::vector<Entity*>& items, int health, int power, int armor, int luck);

	~Creature();

	//Methods
	void TakeDamage(int amount);
	void Heal(int amount);
	void DropInventory();
	void OnDeath();
	void Update() override; 
};

