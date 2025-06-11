#include "Game.h"
#include <windows.h>

#include "GameInstance.h"
#include "Scene/TitleScene.h"
#include "Scene/DungeonScene.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Run()
{
	Init();

	while (1)
	{
		DWORD frameStart = GetTickCount();

		m_input.InputProcess();
		Update();
		Render();

		DWORD frameEnd = GetTickCount();
		DWORD elapsed = frameEnd - frameStart;

		if (elapsed < (DWORD)FRAME_TIME_MS)
			Sleep(FRAME_TIME_MS - elapsed);
	}
}

void Game::Init()
{
	Scene* titleScene = new TitleScene(m_screen, m_input);
	GameInstance::Instance().GetSceneManager().ChangeScene(*titleScene);

	//Scene* dungeonScene = new DungeonScene(m_screen, m_input);
	//GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
}

void Game::Update()
{
	GameInstance::Instance().GetSceneManager().GetCurrentScene().Update();
}

void Game::Render()
{
	m_screen.Clear();

	GameInstance::Instance().GetSceneManager().GetCurrentScene().Render();

	m_screen.Render();
}
