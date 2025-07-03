#include "Game.h"


std::vector<Room*> pRooms;
std::vector<Door*> pDoors;
std::vector<Creature*> pEnemy;
Player* pPlayer;

//const std::string RESET = "\033[0m";
//const std::string RED = "\033[31m";
//const std::string GREEN = "\033[32m";
//const std::string YELLOW = "\033[33m";
//const std::string BLUE = "\033[34m";
//const std::string WHITE = "\033[37m";

Game::Game()
{
	isRunning = false;
	//std::cout << "Game Constructor called!\n";
}

Game::~Game()
{
	//std::cout << "Game Destructor called!\n";
}


void Game::Initialize()
{
	// init game 
	isRunning = true;
	std::cout << "Initializing the game!\n";
	startTime = std::chrono::steady_clock::now();
}

void Game::Setup()
{
	//Creating the rooms
	pRooms.push_back(new Room(EntityType::ROOM, "The Castle Gate", "a huge old castle with a massive gate.")); // 0
	pRooms.push_back(new Room(EntityType::ROOM, "the Patio", "a wide patio surrounded by high walls and some doors.")); // 1
	pRooms.push_back(new Room(EntityType::ROOM, "the Stable", "a stable full of horses.")); // 2
	pRooms.push_back(new Room(EntityType::ROOM, "the Garden", "a peaceful garden with flowers.")); // 3
	pRooms.push_back(new Room(EntityType::ROOM, "the Armory", "a room filled with weapons.")); // 4
	pRooms.push_back(new Room(EntityType::ROOM, "the Barracks", "a room filled with beds and clothes.")); // 5
	pRooms.push_back(new Room(EntityType::ROOM, "the Latrines", "This room stinks so bad!.")); // 6

	//Connecting the rooms
	ConnectRooms(pRooms[0], pRooms[1], Direction::NORTH);  // Castle - Patio
	ConnectRooms(pRooms[1], pRooms[2], Direction::WEST);   // Patio - Stable
	ConnectRooms(pRooms[1], pRooms[3], Direction::NORTH);  // Patio - Garden
	ConnectRooms(pRooms[1], pRooms[4], Direction::EAST);   // Patio - Armory
	ConnectRooms(pRooms[4], pRooms[5], Direction::NORTH);   // Armory - Barracks
	ConnectRooms(pRooms[5], pRooms[6], Direction::EAST);   // Barracks - Latrines


	//Creating Items
	Item* sword = new Item("sword", "An old rusty sword. Might still be useful.", false, true);
	Item* stone = new Item("stone", "A tiny stone. Might still be useful.", false, true);
	Item* chest = new Item("chest", "A wooden chest to store items.", true, false);


	//Populate the rooms with items
	pRooms[0]->AddToInventory(sword);
	//pRooms[0]->AddToInventory(stone);
	pRooms[0]->AddToInventory(chest);

	//TODO: Populate the rooms with creatures

	pEnemy.push_back(new Creature(EntityType::ENEMY,"soldier","a weak soldier.",{stone}, 25, 7, 1, 1));
	
	pRooms[0]->AddToInventory(pEnemy[0]);
	pEnemy[0]->location = pRooms[0];

	//Introduction to the adventure
	pRooms[0]->PrintDescription();

	//Player Start Point
	Stats playerStats = { 100, 10, 5, 3 };
	pPlayer = new Player("Hero", "The brave adventurer", pRooms[0], playerStats);
	
}

void Game::Update()
{
	std::string input;
	std::cout << "\n> ";
	std::getline(std::cin, input);

	if (input == "exit" || input == "quit") {
		std::cout << "Exiting game.\n";
		GetTime();
		Stop();
		return;
	}

	pPlayer->Update(input);
}

void Game::Run()
{
	Setup();

	// Game Loop
	while (isRunning)
	{
		Update();

	}
}

void Game::Stop()
{
	isRunning = false;
	//delete entities
}

void Game::GetTime() 
{
	auto endTime = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

	int hours = elapsed / 3600;
	int minutes = (elapsed % 3600) / 60;
	int seconds = elapsed % 60;

	std::cout << "Played time: "
		<< hours << "h "
		<< minutes << "m "
		<< seconds << "s\n";
}

void Game::ConnectRooms(Room* from, Room* to, Direction dir, bool bidirectional)
{
    // Connect the door "from" to "to"
    Door* door = new Door(dir, from, to, bidirectional);
    pDoors.push_back(door);
    from->doors.push_back(door);

    // bidirectional doors
    if (bidirectional) {
        Direction reverseDir;
        switch (dir) {
        case Direction::NORTH: reverseDir = Direction::SOUTH; break;
        case Direction::SOUTH: reverseDir = Direction::NORTH; break;
        case Direction::EAST:  reverseDir = Direction::WEST;  break;
        case Direction::WEST:  reverseDir = Direction::EAST;  break;
        default: break;
        }
        Door* reverseDoor = new Door(reverseDir, to, from, bidirectional);
        pDoors.push_back(reverseDoor);
        to->doors.push_back(reverseDoor);
    }
}
