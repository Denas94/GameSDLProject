#pragma once
#include "Scene.h"
class Menu : public Scene
{
	//GameState *gameStatus;
	SceneState sceneStatus;


	int *posX, *posY;
	bool *click;
	SDL_Rect bgRect,playGameRect, exitGameRect;
public:
	Menu();
	~Menu();
	void Update();
	void EventHandle();
	void Draw();

};

