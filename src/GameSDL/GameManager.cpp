#include "GameManager.h"



GameManager::GameManager(GameState m_gameState, Scene * m_currentScene){

	m_gameState = GameState::MENU;


	while (m_gameState != GameState::EXITGAME) {


		switch (m_currentScene->GetState())
		{
		case SceneState::RUNNING:
			m_currentScene->EventHandle();
			m_currentScene->Update();
			m_currentScene->Draw();
			break;

		case SceneState::EXIT:
			switch (m_gameState)
			{
			case GameState::MENU:
				delete m_currentScene;
				m_currentScene = nullptr;
				m_gameState = GameState::EXITGAME;
				break;
			case GameState::PLAY:
				delete m_currentScene;
				m_currentScene = new Menu();
				break;
			default:
				break;
			}
			break;

		case SceneState::GOTO:
			switch (m_gameState)
			{
			case GameState::MENU:
				delete m_currentScene;
				m_currentScene = new Play();
				m_gameState = GameState::PLAY;
				break;
			case GameState::PLAY:
				delete m_currentScene;
				m_currentScene = new Menu();
				m_gameState = GameState::MENU;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}



	}
}

GameManager::~GameManager()
{
}
