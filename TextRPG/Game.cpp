#include "Game.h"
#include <windows.h>

#include "GameInstance.h"
#include "Scene/TitleScene.h"

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

		input.InputProcess();
		Update();
		Render();

		DWORD frameEnd = GetTickCount();
		DWORD elapsed = frameEnd - frameStart;

		if (elapsed < (DWORD)frameTimeMS)
			Sleep(frameTimeMS - elapsed);
	}
}

void Game::Init()
{
	GameInstance::Instance().GetSceneManager().ChangeScene(std::make_unique<TitleScene>(screen, input));
}

void Game::Update()
{
	GameInstance::Instance().GetSceneManager().GetCurrentScene()->Update();
}

void Game::Render()
{
	screen.Clear();

	GameInstance::Instance().GetSceneManager().GetCurrentScene()->Render();

	screen.Render();
}
