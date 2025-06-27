#pragma once

#include <string>

class Game
{
private:
	// Global private variables (Attributes) to use in different member functions
	bool isRunning;

	//add timer?

public:
	// Constructor/Destructor
	Game();
	~Game();

	// Member Functions
	void Initialize();
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Output();
	void Stop();

};

