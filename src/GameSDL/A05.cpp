#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>  //Fons de pantalla-personatge-moviment
#include <SDL_ttf.h>    //Fonts de text
#include <SDL_mixer.h>
#include <iostream>
#include <time.h>
using namespace std;

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60


enum class GameState
{
	PLAY, EXIT, MENU
};

bool in_rect(int x, int y, struct SDL_Rect *r) {
	return (x >= r->x) && (y >= r->y) &&
		(x < r->x + r->w) && (y < r->y + r->h);
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

	//BG -- (Fons de pantalla)
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer,"../../res/img/bg.jpg") };
	if (bgTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
	

	//	//Player
	

	// --- Animated Sprite --- (DIJOUS)

	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer,"../../res/img/sp01.png") };
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 6;												//Depende del numero de subdivisiones del sprite (en este caso es de 6x1)
	frameHeight = textHeight / 1;
	playerPosition.x = playerPosition.y = 0;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;


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

	int posX = 0;
	int posY = 0;
	bool click = false;


	// --- TIME ---
	clock_t lastTime = clock();
	float timeDown = 10;
	float deltaTime = 0;


	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	GameState gameStatus = GameState::MENU;
	while (gameStatus != GameState::EXIT) {

		switch (gameStatus)
		{
			case GameState::PLAY: break;
			case GameState::EXIT: break;
			case GameState::MENU: break;
		default:
			break;
		}

		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		gameStatus = GameState::EXIT; break;
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
			case SDL_MOUSEMOTION: posX = event.motion.x; posY = event.motion.y;	break;
			case SDL_MOUSEBUTTONDOWN: if (event.button.button == SDL_BUTTON_LEFT) click = true;  break; //Pregunta si ha clickado con el boton izquierdo del mouse
			default:;
			}
		}

		// UPDATE
		frameTime++;
		if (FPS / frameTime <= 9) {
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textWidth) {
				playerRect.x = 0;
			}
		}

		//TIME
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//cout << timeDown << endl;

		

		//Mouse Click Event Update
		if (click) {
			//Music Buttons

			if (in_rect(posX, posY, &textPlayMusicRect)) { //Encima del boton Play Music
				Mix_PlayMusic(soundtrack, -1);
			}
			if (in_rect(posX, posY, &textStopMusicRect)) { //Encima del boton Stop Music

				Mix_HaltMusic();
			}

			if (in_rect(posX, posY, &exitGameRect)) {
				gameStatus = GameState::EXIT;
			}

		}


		// DRAW
		SDL_RenderClear(renderer);

		//BG + Titol
		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	
		
		//If mouse over PlayGame Button
		if (in_rect(posX, posY, &playGameRect)) {
			SDL_RenderCopy(renderer, playGameTexture2, nullptr, &playGameRect2);
		}
		else {
			SDL_RenderCopy(renderer, playGameTexture, nullptr, &playGameRect);
		}

		//If mouse over ExitGame Button
		if (in_rect(posX, posY, &exitGameRect)) {
			SDL_RenderCopy(renderer, exitGameTexture2, nullptr, &exitGameRect2);
		}
		else {
			SDL_RenderCopy(renderer, exitGameTexture, nullptr, &exitGameRect);
		}

		//If mouse over PlayMusic Button
		if (in_rect(posX, posY, &textPlayMusicRect)) {
			
			SDL_RenderCopy(renderer, playMusicTexture2, nullptr, &textPlayMusicRect2);
		}
		else {
			
			SDL_RenderCopy(renderer, playMusicTexture, nullptr, &textPlayMusicRect);
		}

		//If mouse over StopMusic Button
		if (in_rect(posX, posY, &textStopMusicRect)) {
			
			SDL_RenderCopy(renderer, stopMusicTexture2, nullptr, &textStopMusicRect2);
		}
		else {
			
			SDL_RenderCopy(renderer, stopMusicTexture, nullptr, &textStopMusicRect);
		}




		//Animated Sprite


		//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
		SDL_RenderPresent(renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
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

	//SDL_DestroyTexture(playerTexture);	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();

	// --- QUIT ---
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	return 0;
}