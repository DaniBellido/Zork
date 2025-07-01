#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

enum EntityType
{
	ROOM,
	DOOR,
	ITEM,
	ENEMY,
	NPC,
	PLAYER
};

class Entity
{
public:
	//Atributes
	EntityType type;
	std::string name;
	std::string description;
	std::vector<Entity*> inventory;



	//Constructor 1: Type, name. For entities with no inventory
	Entity(EntityType t, const std::string& n, const std::string& d);
	// Constructor 2: Type, name, and initial inventory
	Entity(EntityType t, const std::string& n, const std::string& d, const std::vector<Entity*>& items);

	///Destructor
	virtual ~Entity();



	//Methods

	virtual void Update() = 0;

	void AddToInventory(Entity* e);

	void RemoveFromInventory(Entity* e);

	void ListInventory();

	void PrintDescription();

};

