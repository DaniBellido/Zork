#include "Game.h"


std::vector<Room*> pRooms;
std::vector<Door*> pDoors;
std::vector<Item*> pItems;
std::vector<Creature*> pEnemy;
Player* pPlayer;

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string WHITE = "\033[37m";

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
	pRooms.push_back(new Room(EntityType::ROOM, "the Chapel", "A religious room filled with ancient ornaments.")); // 7
	pRooms.push_back(new Room(EntityType::ROOM, "the Kin's Room", "A luxury room covered with gold.")); // 8

	//Connecting the rooms
	ConnectRooms(pRooms[0], pRooms[1], Direction::NORTH);  // Castle - Patio
	ConnectRooms(pRooms[1], pRooms[2], Direction::WEST);   // Patio - Stable
	ConnectRooms(pRooms[1], pRooms[3], Direction::NORTH);  // Patio - Garden
	ConnectRooms(pRooms[1], pRooms[4], Direction::EAST);   // Patio - Armory
	ConnectRooms(pRooms[4], pRooms[5], Direction::NORTH);   // Armory - Barracks
	ConnectRooms(pRooms[5], pRooms[6], Direction::EAST);   // Barracks - Latrines
	ConnectRooms(pRooms[3], pRooms[7], Direction::NORTH);  // Garden - Chapel
	ConnectRooms(pRooms[3], pRooms[8], Direction::WEST);  // Garden - King's Room


	//Creating Items
	pItems.push_back(new Item("knife", "An old rusty knife. It won't slice anything.", false, true)); // 0
	pItems.push_back(new Item("stone", "A tiny stone. Not very useful.", false, true)); // 1
	pItems.push_back(new Item("chest", "A wooden chest to store items.", true, false)); // 2
	pItems.push_back(new Item("sword", "A powerful sword. For the win!", false, true)); // 3 
	pItems[2]->AddToInventory(pItems[3]); //placing the sword within the chest
	pItems.push_back(new Item("key", "A golden key with a weird incription. What would it open?", false, true)); // 4
	pItems.push_back(new Item("big chest", "A large locked chest. You might need a key.", true, false)); // 5
	pItems[5]->isLocked = true; //locking the big chest
	pItems.push_back(new Item("coin", "A coin with the King's face.", false, true)); // 6

	//Populate the rooms with items
	pRooms[0]->AddToInventory(pItems[0]);
	pRooms[1]->AddToInventory(pItems[1]);
	pRooms[4]->AddToInventory(pItems[2]);
	pRooms[7]->AddToInventory(pItems[5]);
	
	//Creating enemies
	pEnemy.push_back(new Creature(EntityType::ENEMY,"soldier","a weak soldier.",{}, 20, 7, 1, 1)); //0
	pEnemy.push_back(new Creature(EntityType::ENEMY, "soldier", "a casual soldier.", {pItems[6]}, 30, 10, 2, 1)); //1
	pEnemy.push_back(new Creature(EntityType::ENEMY, "soldier", "a weak soldier.", {}, 20, 7, 1, 1)); //2
	pEnemy.push_back(new Creature(EntityType::ENEMY, "commander", "a high rank soldier. Looks very dangerous!", { pItems[4] }, 100, 18, 5, 1)); //3
	pEnemy.push_back(new Creature(EntityType::ENEMY, "soldier", "a casual soldier.", {}, 30, 10, 2, 1)); //4
	pEnemy.push_back(new Creature(EntityType::ENEMY, "soldier", "a strong soldier.", {}, 50, 11, 3, 1)); //5
	
	//Populate the rooms with enemies
	pRooms[1]->AddToInventory(pEnemy[0]); pEnemy[0]->location = pRooms[0];
	pRooms[4]->AddToInventory(pEnemy[1]); pEnemy[1]->location = pRooms[4];
	pRooms[5]->AddToInventory(pEnemy[2]); pEnemy[2]->location = pRooms[5];
	pRooms[5]->AddToInventory(pEnemy[3]); pEnemy[3]->location = pRooms[5];
	pRooms[8]->AddToInventory(pEnemy[4]); pEnemy[4]->location = pRooms[8];
	pRooms[7]->AddToInventory(pEnemy[5]); pEnemy[5]->location = pRooms[7];



	//Introduction to the adventure

	std::cout << "Welcome to the Kingdom of Velmortih. The soldiers of the evil Sir Psycho have looted your village.\n";
	std::cout << "You have been sent to Sir Psycho's Castle in order to get back your ancient treasure and claim justice!\n.";
	std::cout << "Type 'info' to see what actions you can take. Sir Psycho's Castle stands in front of you. \n\n";
	pRooms[0]->PrintDescription();

	//Player Start Point
	Stats playerStats = { 100, 25, 5, 3 };
	pPlayer = new Player("Hero", "The brave adventurer", pRooms[0], playerStats);
	pPlayer->game = this; 
	
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

		if (isGameOver) 
		{
			CleanUp();
			GameOver();
		}
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

	std::cout << ""
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

void Game::CleanUp() 
{

	for (Room* room : pRooms)
		delete room;
	pRooms.clear();

	
	for (Door* door : pDoors)
		delete door;
	pDoors.clear();

	
	for (Creature* enemy : pEnemy)
		//delete enemy;
	pEnemy.clear();


	delete pPlayer;
	pPlayer = nullptr;

	isRunning = false;

}

void Game::GameOver()
{
	system("cls");

	std::cout << RED << "You unlocked the chest and found the stolen treasure.\n" << YELLOW;

	std::cout << R"(
  _____                         ____                 
 / ____|                       / __ \                
| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
| | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
| |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
 \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   

                                                                                  
)" << std::endl;

	std::cout << GREEN << "GAME COMPLETED IN: ";
	GetTime();
	std::cout << WHITE;
}
