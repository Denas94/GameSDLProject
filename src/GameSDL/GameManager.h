#pragma once
#include "Types.h"
class GameManager
{
	GameState gameState;
	Scene *currentScene;
public:
	GameManager(GameState gameState, Scene *currentScene);
	~GameManager();
};

