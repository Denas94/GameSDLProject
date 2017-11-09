#include "Play.h"



Play::Play()
{

	//Image BG
	Renderer::Instance()->LoadTexture(PLAY_BG, "../../res/img/bgCastle.jpg");
	bgRect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	//Font inPlayScene
	Font playFont;
	playFont.id = LUIGI_40;
	playFont.size = 40;
	playFont.path = "../../res/ttf/luigi.ttf";

	Text p1Score;
	p1Score.id = PLAY_TEXT_SCORE_PLAYER1;
	p1Score.text = "P1:";


	Renderer::Instance()->LoadFont(playFont);
	Renderer::Instance()->LoadTextureText(LUIGI_40, p1Score);
	p1ScoreRect = { 50, 50, p1Score.w, p1Score.h };


	Renderer::Instance()->LoadTexture(PLAY_GOLD, "../../res/img/gold.png");
	goldBagRect = { 300, 300, 75, 60 };

	Renderer::Instance()->LoadTexture(PLAYER_SPRITE, "../../res/img/spCastle.png");
	textP1Width = textP1Height = frameP1Width = frameP1Height = 0;
	Renderer::Instance()->GetTextureSize(PLAYER_SPRITE);
	frameP1Width = textP1Width / 12; 
	frameP1Height = textP1Height / 8;
	playerP1Position.x = 300; playerP1Position.y = 400;
	playerP1Rect.x = playerP1Rect.y = 0;
	playerP1Position.h = playerP1Rect.h = frameP1Height;
	playerP1Position.w = playerP1Rect.w = frameP1Width;
	playerP1Position.h += 10;
	playerP1Position.w += 10;





}


Play::~Play()
{
}

void Play::EventHandle()
{

	SDL_Event *event;

	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_QUIT:		sceneStatus = SceneState::EXIT;  break;
		case SDL_KEYDOWN:	if (event->key.keysym.sym == SDLK_ESCAPE) sceneStatus = SceneState::EXIT;
			if (event->key.keysym.sym == SDLK_a) pressed = Key::LEFT;
			if (event->key.keysym.sym == SDLK_w) pressed = Key::UP;
			if (event->key.keysym.sym == SDLK_s) pressed = Key::DOWN;
			if (event->key.keysym.sym == SDLK_d) pressed = Key::RIGHT;
			break;
		case SDL_MOUSEMOTION: *posX = event->motion.x; *posY = event->motion.y;	break;
		case SDL_MOUSEBUTTONDOWN: if (event->button.button == SDL_BUTTON_LEFT) *click = true;  break; //Pregunta si ha clickado con el boton izquierdo del mouse

		default: break;
		}
	}
}

void Play::Update()
{
	frameTime++;




	if (FPS / frameTime <= 9) {
		frameTime = 0;
		playerP1Rect.x += frameP1Width;
		if (playerP1Rect.x >= (frameP1Width * 3)) {
			playerP1Rect.x = 0;
		}
	}
	if (*click) {
		if (in_rect(*posX, *posY, &goldBagRect)) {
			cout << "Destroy" << endl;
		}
	}

	if (pressed == Key::LEFT) {
		playerP1Rect.y = frameP1Height * 2;
		playerP1Position.x -= 10;

	}

	if (pressed == Key::UP) {
		playerP1Rect.y = frameP1Height * 4;
		playerP1Position.y -= 10;
	}

	if (pressed == Key::RIGHT) {
		playerP1Rect.y = frameP1Height * 3;
		playerP1Position.x += 10;
	}

	if (pressed == Key::DOWN) {
		playerP1Rect.y = frameP1Height;
		playerP1Position.y += 10;

	}


}

void Play::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->PushImage(PLAY_BG, bgRect);

	Renderer::Instance()->PushImage(PLAY_TEXT_SCORE_PLAYER1, p1ScoreRect);

	Renderer::Instance()->PushImage(PLAY_GOLD, goldBagRect);
	Renderer::Instance()->PushSprite(PLAYER_SPRITE, playerP1Rect, playerP1Position);

	Renderer::Instance()->Render();

}
