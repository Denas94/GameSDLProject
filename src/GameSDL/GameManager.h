#pragma once
#include "Types.h"
class GameManager
{
	GameState m_gameState;
	Scene *m_currentScene;

public:
	GameManager();
	~GameManager();
	void Run();
};

