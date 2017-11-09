#include "Menu.h"

Menu::Menu()
{
	//Image BG
	Renderer::Instance()->LoadTexture(MENU_BG,"../../res/img/bg.jpg");
	bgRect = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };


	//Font Titles
	Font bgFont;
	bgFont.id = SAIYAN_80;
	bgFont.path = "../../res/ttf/saiyan.ttf";
	bgFont.size = 60;

	//Text Play Game
	Text textPlayGame;
	textPlayGame.text = "Play Game";
	textPlayGame.id = MENU_TEXT_BUTTON_PLAY;
	
	Renderer::Instance()->LoadFont(bgFont);
	Renderer::Instance()->LoadTextureText(SAIYAN_80, textPlayGame);
	playGameRect = { 280,200,textPlayGame.w,textPlayGame.h };

	Text textExitGame;
	textExitGame.text = "Exit Game";
	textExitGame.id = MENU_TEXT_BUTTON_EXIT;

	Renderer::Instance()->LoadTextureText(SAIYAN_80, textExitGame);
	exitGameRect = { 280,275,textExitGame.w,textExitGame.h };

	
}

Menu::~Menu()
{
	
	posX = posY = nullptr;
	click = nullptr;
}

void Menu::EventHandle()
{
	*click = false;
	SDL_Event *event;

	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_QUIT:		sceneStatus = SceneState::EXIT;  break;
		case SDL_KEYDOWN:	if (event->key.keysym.sym == SDLK_ESCAPE) sceneStatus = SceneState::EXIT; break;
		case SDL_MOUSEMOTION: *posX = event->motion.x; *posY = event->motion.y;	break;
		case SDL_MOUSEBUTTONDOWN: if (event->button.button == SDL_BUTTON_LEFT) *click = true;  break; //Pregunta si ha clickado con el boton izquierdo del mouse
		default: break;
		}
	}
}

void Menu::Update() {


	//Mouse Click Event Update
	if (*click) {
		//Music Buttons
		

		if (in_rect(*posX, *posY, &playGameRect)) {
			sceneStatus = SceneState::GOTO;
		}

		if (in_rect(*posX, *posY, &exitGameRect)) {
			sceneStatus = SceneState::EXIT;
		}


	}
}

void Menu::Draw()
{
	//Clear render
	Renderer::Instance()->Clear(); 

	//BG render
	Renderer::Instance()->PushImage(MENU_BG, bgRect);
	
	//Buttons Render
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_PLAY, playGameRect);
	Renderer::Instance()->PushImage(MENU_TEXT_BUTTON_EXIT, exitGameRect);

	//RenderPresent
	Renderer::Instance()->Render();


}
