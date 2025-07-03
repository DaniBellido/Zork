#include "Room.h"



Room::Room(EntityType t, const std::string& n, const std::string& d) : Entity(t, n, d)
{
	type = t;
	name = n;
	description = d;
}

Room::~Room()
{
    //std::cout << "Entity Destructor called!\n";
}


void Room::Update() {}