#include "Entity.h"

Entity::Entity(EntityType t, const std::string& n, const std::string& d) : type(t), name(n), description(d) {}

Entity::Entity(EntityType t, const std::string& n, const std::string& d, const std::vector<Entity*>& items) : type(t), name(n), description(d), inventory(items) {}

Entity::~Entity() 
{
    std::cout << "Entity Destructor called!\n";
}

void Entity::AddToInventory(Entity* e) 
{ 
    inventory.push_back(e); 
}

void Entity::RemoveFromInventory(Entity* e) 
{

	// std::remove moves all elements equal to 'e' to the end of the vector
	// and returns an iterator to the "new end" of the range.
	auto it = std::remove(inventory.begin(), inventory.end(), e);

	// If 'e' was found and moved, 'it' will not be equal to inventory.end()
	if (it != inventory.end()) {
		// Actually erase the removed elements from the vector.
		// This call shortens the vector by removing all elements from 'it' to the end.
		inventory.erase(it, inventory.end());
	}

}

void Entity::ListInventory()
{
	if (inventory.empty()) {
		std::cout << "There is nothing here." << std::endl;
		return;
	}

	for (Entity* e : inventory) {
		std::cout << "- " << e->name << std::endl;
	}
}

void Entity::PrintDescription() 
{
	std::cout << "It's a " << name << ": " << description << std::endl;
}