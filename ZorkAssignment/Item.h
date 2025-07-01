#pragma once
#include "Entity.h"
class Item : public Entity
{
public:

	Item(const std::string& name, const std::string& description)
		: Entity(EntityType::ITEM, name, description) {}

	void Update() override {}
	

};

