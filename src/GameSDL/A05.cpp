#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>  //Fons de pantalla-personatge-moviment
#include <SDL_ttf.h>    //Fonts de text
#include <SDL_mixer.h>
#include <iostream>
#include <time.h>
#include <vector>
#include "Collisions.h"
using namespace std;

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

float frameTime = 0;

enum class GameState
{
	PLAY, EXIT, MENU
};

bool in_rect(int x, int y, struct SDL_Rect *r) {
	return (x >= r->x) && (y >= r->y) &&
		(x < r->x + r->w) && (y < r->y + r->h);
}

void destroyTexture(SDL_Texture *texture) {
	SDL_DestroyTexture(texture);
}

//vector<SDL_Rect> randomBag() {
//
//	
//	vector<SDL_Rect> randomBagRect;
//	randomBagRect
//	randomBagRect.x = rand()%800;
//	randomBagRect->y = rand()%400+200;
//	randomBagRect->w = 75;
//	randomBagRect->h = 60;
//	
//
//	return randomBagRect;
//}


void EventHandleMenu(SDL_Event* event, GameState* gameStatus, int* posX, int* posY, bool* click) {
	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_QUIT:		*gameStatus = GameState::EXIT;  break;
		case SDL_KEYDOWN:	if (event->key.keysym.sym == SDLK_ESCAPE) *gameStatus = GameState::EXIT; break;
		case SDL_MOUSEMOTION: *posX = event->motion.x; *posY = event->motion.y;	break;
		case SDL_MOUSEBUTTONDOWN: if (event->button.button == SDL_BUTTON_LEFT) *click = true;  break; //Pregunta si ha clickado con el boton izquierdo del mouse
		default: break;
		}
	}

}

void UpdateMenu( bool* click, int* posX, int* posY,
	SDL_Rect* playerRect, SDL_Rect textPlayMusicRect, SDL_Rect textStopMusicRect,SDL_Rect playGameRect, SDL_Rect exitGameRect,
	int frameWidth, int textWidth, Mix_Music *soundtrack, GameState* gameStatus) {

	
	// UPDATE
	frameTime++;
	if (FPS / frameTime <= 9) {
		frameTime = 0;
		playerRect->x += frameWidth;
		if (playerRect->x >= textWidth) {
			playerRect->x = 0;
		}
	}




	//Mouse Click Event Update
	if (*click) {
		//Music Buttons

		if (in_rect(*posX, *posY, &textPlayMusicRect)) { //Encima del boton Play Music
			Mix_PlayMusic(soundtrack, -1);
		}
		if (in_rect(*posX, *posY, &textStopMusicRect)) { //Encima del boton Stop Music

			Mix_HaltMusic();
		}

		if (in_rect(*posX, *posY, &playGameRect)) {
			*gameStatus = GameState::PLAY;
		}

		if (in_rect(*posX, *posY, &exitGameRect)) {
			*gameStatus = GameState::EXIT;
		}


	}
}

void DrawMenu(SDL_Renderer *renderer, SDL_Texture *bgTexture, SDL_Texture *textTexture, SDL_Texture *playGameTexture, SDL_Texture *playGameTexture2,
	SDL_Texture *exitGameTexture, SDL_Texture *exitGameTexture2, SDL_Texture *playMusicTexture, SDL_Texture *playMusicTexture2, SDL_Texture *stopMusicTexture,
	SDL_Texture * stopMusicTexture2, SDL_Texture *playerTexture, SDL_Rect bgRect, SDL_Rect textRect, SDL_Rect playGameRect, SDL_Rect playGameRect2, SDL_Rect exitGameRect,
	SDL_Rect exitGameRect2, SDL_Rect textPlayMusicRect, SDL_Rect textPlayMusicRect2, SDL_Rect textStopMusicRect, SDL_Rect textStopMusicRect2, SDL_Rect* playerRect,
	SDL_Rect* playerPosition, int* posX, int* posY) {

	// DRAW
	SDL_RenderClear(renderer);

	//BG + Titol
	SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

	

	//If mouse over PlayGame Button
	if (in_rect(*posX, *posY, &playGameRect)) {
		SDL_RenderCopy(renderer, playGameTexture2, nullptr, &playGameRect2);
	}
	else {
		SDL_RenderCopy(renderer, playGameTexture, nullptr, &playGameRect);
	}

	//If mouse over ExitGame Button
	if (in_rect(*posX, *posY, &exitGameRect)) {
		SDL_RenderCopy(renderer, exitGameTexture2, nullptr, &exitGameRect2);
	}
	else {
		SDL_RenderCopy(renderer, exitGameTexture, nullptr, &exitGameRect);
	}

	//If mouse over PlayMusic Button
	if (in_rect(*posX, *posY, &textPlayMusicRect)) {

		SDL_RenderCopy(renderer, playMusicTexture2, nullptr, &textPlayMusicRect2);
	}
	else {

		SDL_RenderCopy(renderer, playMusicTexture, nullptr, &textPlayMusicRect);
	}

	//If mouse over StopMusic Button
	if (in_rect(*posX, *posY, &textStopMusicRect)) {

		SDL_RenderCopy(renderer, stopMusicTexture2, nullptr, &textStopMusicRect2);
	}
	else {

		SDL_RenderCopy(renderer, stopMusicTexture, nullptr, &textStopMusicRect);
	}




	//Animated Sprite


	//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
	SDL_RenderCopy(renderer, playerTexture, playerRect, playerPosition);
	SDL_RenderPresent(renderer);

}


void Destroy(SDL_Texture *bgTexture, SDL_Texture *textTexture, SDL_Texture *playGameTexture, SDL_Texture *playGameTexture2, SDL_Texture *exitGameTexture, SDL_Texture *exitGameTexture2,
	SDL_Texture *playMusicTexture, SDL_Texture *playMusicTexture2, SDL_Texture *stopMusicTexture, SDL_Texture *stopMusicTexture2, SDL_Texture *bgPlayTexture) {

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	//SDL_DestroyTexture(bgPlayTexture);
	SDL_DestroyTexture(textTexture);

	//Buttons
	SDL_DestroyTexture(playGameTexture);
	SDL_DestroyTexture(playGameTexture2);
	SDL_DestroyTexture(exitGameTexture);
	SDL_DestroyTexture(exitGameTexture2);
	SDL_DestroyTexture(playMusicTexture);
	SDL_DestroyTexture(playMusicTexture2);
	SDL_DestroyTexture(stopMusicTexture);
	SDL_DestroyTexture(stopMusicTexture2);

	
	
	
	

}

void EventHandlePlay(SDL_Event* event, GameState* gameStatus, int* posX, int* posY, bool* click, bool* a, bool *w, bool *s, bool *d) {
	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_QUIT:		*gameStatus = GameState::EXIT;  break;
		case SDL_KEYDOWN:	if (event->key.keysym.sym == SDLK_ESCAPE) *gameStatus = GameState::EXIT;
							if (event->key.keysym.sym == SDLK_a) *a = true;
							if (event->key.keysym.sym == SDLK_w) *w = true;
							if (event->key.keysym.sym == SDLK_s) *s = true;
							if (event->key.keysym.sym == SDLK_d) *d = true;
							break;
		case SDL_MOUSEMOTION: *posX = event->motion.x; *posY = event->motion.y;	break;
		case SDL_MOUSEBUTTONDOWN: if (event->button.button == SDL_BUTTON_LEFT) *click = true;  break; //Pregunta si ha clickado con el boton izquierdo del mouse
		
		default: break;
		}
	}
}

void updatePlay(SDL_Renderer *renderer, bool* click, int* posX, int* posY, GameState* gameStatus, SDL_Rect* playerP1Rect,SDL_Rect* playerP1Position, vector <SDL_Rect> goldBagPositions, SDL_Texture* goldBagTexture, int frameP1Width, int frameP1Height, bool *a, bool *w, bool *s, bool *d) {
	frameTime++;
	

	if (FPS / frameTime <= 9) {
		frameTime = 0;
		playerP1Rect->x += frameP1Width;
		if (playerP1Rect->x >= (frameP1Width*3)) {
			playerP1Rect->x = 0;
		}
	}
	if (*click) {
		if (in_rect(*posX, *posY, &goldBagPositions[0])) {
			//destroyTexture(goldBagTexture);
			//goldBagPosition = randomBag();
			
			//cout << "lmao" << endl;
			//randomBagTexture(renderer, goldBagTexture, goldBagPosition);
			//cout << goldBagPosition->x << endl;
		}
	}

	if (*a) {
		playerP1Rect->y = frameP1Height*2;
		playerP1Position->x -= 10;
		
	}

	if (*w) {
		playerP1Rect->y = frameP1Height *4;
		playerP1Position->y += 10;
	}

	if (*d) {
		playerP1Rect->y = frameP1Height*3;
		playerP1Position->x += 10;
	}

	if (*s) {
		playerP1Rect->y = frameP1Height;
		playerP1Position->y -= 10;
		
	}

	
	
	/*if (FPS / frameTime <= 9) {
		frameTime = 0;
		playerRect->x += frameWidth;
		if (playerRect->x >= textWidth) {
			playerRect->x = 0;
		}
	}*/
	
}

void drawPlay(SDL_Renderer *renderer, SDL_Texture *bgPlayTexture, SDL_Rect bgPlayRect, SDL_Texture *playerP1Texture, SDL_Rect *playerP1Rect, SDL_Rect playerP1Position,
				SDL_Texture *goldBagTexture, vector <SDL_Rect> goldBagPositions, bool *a) {

	
	// DRAW
	SDL_RenderClear(renderer);

	//BG + Titol
	SDL_RenderCopy(renderer, bgPlayTexture, nullptr, &bgPlayRect);

	//P1 Character
	//SDL_RenderCopy(renderer, playerTexture, playerRect, playerPosition);
	SDL_RenderCopy(renderer, playerP1Texture, playerP1Rect, &playerP1Position);
	
	//SDL_RenderCopy(renderer, goldBagTexture, nullptr, goldBagRect);
	//cout << goldBagRect->x << endl;
	for (int i = 0; i < 5; i++) {
		//SDL_RenderCopy(renderer, goldBagTexture, nullptr, &goldBagPositions[i]); //aquí està el problema
		//cout << (goldBagRect+i)->x << endl; 
	}


	if (*a) {
		cout << "a" << endl;
	}

	/*if (*w) {
		cout << "w" << endl;
	}

	if (*s) {
		cout << "s" << endl;
	}

	if (*d) {
		cout << "d" << endl;
	}*/

	SDL_RenderPresent(renderer);
}



int main(int, char*[]) {

	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags)& imgFlags)) throw "Error: SDL_image init";

	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";

	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)& mixFlags)) throw "Error: SDL_mixer init";



	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	// --- SPRITES --- (Textures)

	//BG -- (Fons de pantalla) MENU
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer,"../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//BG -- (Fons de pantalla) PLAY
	SDL_Texture *bgPlayTexture{ IMG_LoadTexture(renderer,"../../res/img/bgCastle.jpg") };
	if (bgPlayTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgPlayRect{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//	//Player


	// --- Animated Sprite --- (DIJOUS) - MENU

	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer,"../../res/img/sp01.png") };
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 6;												//Depende del numero de subdivisiones del sprite (en este caso es de 6x1)
	frameHeight = textHeight / 1;
	playerPosition.x = 0; playerPosition.y = 100;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;

	SDL_Texture *playerP1Texture{ IMG_LoadTexture(renderer, "../../res/img/spCastle.png") };
	SDL_Rect playerP1Rect, playerP1Position;
	int textP1Width, textP1Height, frameP1Width, frameP1Height;
	textP1Width = textP1Height = frameP1Width = frameP1Height = 0;
	SDL_QueryTexture(playerP1Texture, NULL, NULL, &textP1Width, &textP1Height);
	frameP1Width = textP1Width / 12;
	frameP1Height = textP1Height / 8;
	playerP1Position.x = 300; playerP1Position.y = 300;
	playerP1Rect.x = playerP1Rect.y = 0;
	playerP1Position.h = playerP1Rect.h = frameP1Height;
	playerP1Position.w = playerP1Rect.w = frameP1Width;
	playerP1Position.h += 10;
	playerP1Position.w += 10;
	
	//Bossa d'or
	SDL_Texture *goldBagTexture{ IMG_LoadTexture(renderer, "../../res/img/gold.png") };
	//SDL_Rect goldBagPosition{ 300, 300, 75, 60 };

	
	
	vector <SDL_Rect> goldBagPositions[5];
	//goldBagPositions->push_back(SDL_Rect());

	/*for (int i = 0; i < 5; i++) {
		goldBagPositions[i] = randomBag();
	}*/
	

	// --- TEXT ---

	//Game Title
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,"My first SDL game", SDL_Color{ 255,150,0,255 }) };
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer,tmpSurf) };
	SDL_Rect textRect{ 100,50,tmpSurf->w, tmpSurf->h };

	TTF_CloseFont(font);

	//Play Game
	TTF_Font *font2{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 60) };
	if (font == nullptr) throw "No es pot inicialitzar the TTF_Font";
	tmpSurf = TTF_RenderText_Blended(font2, "Play Game", SDL_Color{ 35,250,0,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *playGameTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect playGameRect{ 280,200,tmpSurf->w, tmpSurf->h };

	//Play Game2
	tmpSurf = TTF_RenderText_Blended(font2, "Play Game", SDL_Color{ 0,0,255,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *playGameTexture2{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect playGameRect2{ 280,200,tmpSurf->w, tmpSurf->h };

	//Exit Game
	tmpSurf = TTF_RenderText_Blended(font2, "Exit Game", SDL_Color{ 255,15,0,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *exitGameTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect exitGameRect{ 280,275,tmpSurf->w, tmpSurf->h };

	//Exit Game 2
	tmpSurf = TTF_RenderText_Blended(font2, "Exit Game", SDL_Color{ 255,69,0,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *exitGameTexture2{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect exitGameRect2{ 280,275,tmpSurf->w, tmpSurf->h };

	//PlayMusic
	tmpSurf = TTF_RenderText_Blended(font2, "Play Music", SDL_Color{ 255,255,0,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *playMusicTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textPlayMusicRect{ 500,460,tmpSurf->w, tmpSurf->h };

	//PlayMusic2
	tmpSurf = TTF_RenderText_Blended(font2, "Play Music", SDL_Color{ 0,0,0,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *playMusicTexture2{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textPlayMusicRect2{ 500,460,tmpSurf->w, tmpSurf->h };

	//Stop Music
	tmpSurf = TTF_RenderText_Blended(font2, "Stop Music", SDL_Color{ 255,0,255,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *stopMusicTexture{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textStopMusicRect{ 500,510,tmpSurf->w, tmpSurf->h };

	//Stop Music2
	tmpSurf = TTF_RenderText_Blended(font2, "Stop Music", SDL_Color{ 0,0,0,255 });
	if (tmpSurf == nullptr) throw "Unable to create the SDL text surface";
	SDL_Texture *stopMusicTexture2{ SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	SDL_Rect textStopMusicRect2{ 500,510,tmpSurf->w, tmpSurf->h };


	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font2);

	// --- AUDIO --- //Mix_HaltMusic

	if (
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable to initialize SDL_mixer audio system";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 10;
	float deltaTime = 0;


	int posX = 0;
	int posY = 0;
	bool click = false;
	bool a = false;
	bool w = false;
	bool s = false;
	bool d = false;
	bool first = true;
	//srand(time(NULL));
	// --- GAME LOOP ---
	SDL_Event event;

	GameState gameStatus = GameState::MENU;
	while (gameStatus != GameState::EXIT) {

		click = false;
		a = false;
		w = false;
		s = false;
		d = false;
		//TIME
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//
		switch (gameStatus)
		{
		case GameState::PLAY: EventHandlePlay(&event, &gameStatus, &posX, &posY, &click, &a, &w, &s, &d);
							  updatePlay(renderer, &click, &posX, &posY, &gameStatus, &playerP1Rect, &playerP1Position, *goldBagPositions, goldBagTexture, frameP1Width, frameP1Height, &a, &w, &s, &d);
							  drawPlay(renderer, bgPlayTexture, bgPlayRect, playerP1Texture, &playerP1Rect, playerP1Position, goldBagTexture, *goldBagPositions, &a);
							 

		case GameState::EXIT: Destroy(bgTexture, textTexture, playGameTexture, playGameTexture2, exitGameTexture, exitGameTexture2,
							  playMusicTexture, playMusicTexture2, stopMusicTexture, stopMusicTexture2, bgPlayTexture);
							 
							  break;
		case GameState::MENU: //InitMenu();
			
			
							  EventHandleMenu(&event, &gameStatus, &posX, &posY, &click);
								
							  UpdateMenu(&click, &posX, &posY, &playerRect, textPlayMusicRect, textStopMusicRect, playGameRect, exitGameRect,
									frameWidth, textWidth, soundtrack, &gameStatus);
						      DrawMenu(renderer, bgTexture, textTexture, playGameTexture, playGameTexture2, exitGameTexture, exitGameTexture2, playMusicTexture,
									playMusicTexture2, stopMusicTexture, stopMusicTexture2, playerTexture, bgRect, textRect, playGameRect, playGameRect2, exitGameRect,
									exitGameRect2, textPlayMusicRect, textPlayMusicRect2, textStopMusicRect, textStopMusicRect2, &playerRect, &playerPosition, &posX, &posY); break;
		default:
			break;
		}

		
		
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();

	// --- QUIT ---
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}