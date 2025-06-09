#pragma once
#include <memory>
#include "Scene.h"
#include "../Screen.h"

class SceneManager
{
public:
	SceneManager() :currentScene(nullptr) { }
	~SceneManager() {}

public:
	inline std::unique_ptr<Scene>& GetCurrentScene()
	{
		return currentScene;
	}

	void ChangeScene(std::unique_ptr<Scene> newScene)
	{
		if (currentScene)
		{
			currentScene->OnExit();
		}
		currentScene = std::move(newScene);
		currentScene->OnEnter();
	}

private:
	std::unique_ptr<Scene> currentScene = nullptr;
};

