#pragma once
#include <string>
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <time.h>
#include "Scene.h"
#include "Play.h"
#include "Menu.h"
#include "Renderer.h"

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

// --- TIME ---
float frameTime = 0;
clock_t lastTime = clock();
float timeDown = 10;
float deltaTime = 0;

bool in_rect(int x, int y, struct SDL_Rect *r) {
	return (x >= r->x) && (y >= r->y) &&
		(x < r->x + r->w) && (y < r->y + r->h);
}

enum class SceneState {
	RUNNING, GOTO, EXIT
};

enum class GameState
{
	PLAY, EXITGAME, MENU
};

	using Rect = struct  Rect{ int  x; int y; int w; int h; };

	using Color = struct Color { Uint8 r; Uint8 g; Uint8 b; Uint8 a; };
	
	struct Vector2 { int x; int y; };

	using Font = struct {
		std::string id;
		std::string path;
		int size;
	};

	using Text = struct {
		std::string id;
		std::string text;
		Color color;
		int w;
		int h;
	};

	enum class Key {UP, DOWN, LEFT, RIGHT, NONE};

	


