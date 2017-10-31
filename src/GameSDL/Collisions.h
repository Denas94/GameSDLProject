#pragma once
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>  //Fons de pantalla-personatge-moviment
#include <SDL_ttf.h>    //Fonts de text
#include <SDL_mixer.h>
#include <iostream>
#include <time.h>
#include <vector>

bool Collision(SDL_Rect origen, SDL_Rect target); //Funcio per veure si colisionen dos SDL_Rects

bool CollisionWalls(SDL_Rect iniside, SDL_Rect container); //Funcio per veure la colisio dins de pantalla