#pragma once
#include "Entity.h"
#include "Door.h"


class Room : public Entity
{
public:

	Room(EntityType t, const std::string& n, const std::string& d);

	~Room();

	void Update() override;

	std::vector<Door*> doors;
};

