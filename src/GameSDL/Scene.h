#pragma once
#include "Renderer.h"
using namespace std;

class Scene 
{

protected:
	
	SceneState sceneState; //Estat del escena, únic que interessa
public:
	

	Scene();

	~Scene();
	SceneState GetState();
	virtual void EventHandle();
	virtual void Update();
	virtual void Draw();
};

