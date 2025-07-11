#include "Game.h"
#include <windows.h>
#include "GameInstance.h"
#include "Scene/TitleScene.h"


void Game::Run()
{
	Init();

	while (1)
	{
		DWORD frameStart = GetTickCount();

		if (m_textPrompt.IsRunning() == false)
		{
			m_input.InputProcess();
		}

		Update();
		Render();

		DWORD frameEnd = GetTickCount();
		DWORD elapsed = frameEnd - frameStart;

		if (elapsed < FRAME_TIME_MS)
		{
			Sleep(FRAME_TIME_MS - elapsed);
		}
	}
}

void Game::Init()
{
	Scene* titleScene = new TitleScene(m_screen, m_input, m_textPrompt);
	GameInstance::GetInstance().GetSceneManager().ChangeScene(*titleScene);
}

void Game::Update()
{
	m_textPrompt.Update();
	GameInstance::GetInstance().GetSceneManager().GetCurrentScene().Update();
}

void Game::Render()
{
	m_screen.Clear();

	m_textPrompt.Render(m_screen);
	GameInstance::GetInstance().GetSceneManager().GetCurrentScene().Render();

	m_screen.Render();
}
