#pragma once
#include "Entity.h"
class Item : public Entity
{
public:
	bool isContainer = false;   
	bool isOpen = true;          
	bool isLocked = false;       
    bool isPortable = true;  

	Item(const std::string& name, const std::string& description, bool container = false, bool portable = true)
		: Entity(EntityType::ITEM, name, description), isContainer(container), isOpen(true), isLocked(false), isPortable(portable) {}

    void Open() {
        if (!isContainer) {
            std::cout << name << " can't be opened.\n";
            return;
        }
        if (isLocked) {
            std::cout << name << " is locked.\n";
            return;
        }
        if (isOpen) {
            std::cout << name << " is already open.\n";
            return;
        }
        isOpen = true;
        std::cout << "You open the " << name << ".\n";
    }

    void Close() {
        if (!isContainer) {
            std::cout << name << " can't be closed.\n";
            return;
        }
        if (!isOpen) {
            std::cout << name << " is already closed.\n";
            return;
        }
        isOpen = false;
        std::cout << "You close the " << name << ".\n";
    }

	void Update() override {}
	

};

