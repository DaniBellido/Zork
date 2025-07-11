#pragma once
#include "Entity.h"

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

class Room;

class Door : public Entity
{
public:
    // Constructor
    Door(Direction dir, Room* sourceRoom, Room* destinationRoom, bool bidirectional = true)
        : Entity(EntityType::DOOR, "Door", "A wooden door leading to somewhere"),
        direction(dir), source(sourceRoom), destination(destinationRoom), bidirectional(bidirectional)
    {
    }

    // Getters
    Direction GetDirection() const { return direction; }
    Room* GetSource() const { return source; }
    Room* GetDestination() const { return destination; }

    // Setters (opcionales)
    void SetDirection(Direction dir) { direction = dir; }
    void SetSource(Room* room) { source = room; }
    void SetDestination(Room* room) { destination = room; }

    void Update() override {};

public:
    Direction direction;
    Room* source;
    Room* destination;
    bool bidirectional;
};

