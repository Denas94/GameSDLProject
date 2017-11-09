#pragma once
#include "Scene.h"
class Play : public Scene
{
	SceneState sceneStatus;
	Key pressed;


	int *posX, *posY;
	bool *click;
	SDL_Rect bgRect, p1ScoreRect, playerP1Rect, playerP1Position, goldBagRect;
	int textP1Width, textP1Height, frameP1Width, frameP1Height;
public:
	Play();
	~Play();
	void EventHandle();
	void Update();
	void Draw();

	
};

