#pragma once
#include <memory>
#include "Scene.h"
#include "../Screen.h"

class SceneManager
{
public:
	SceneManager() 
		:m_currentScene(nullptr)
	{
		
	}

	virtual ~SceneManager() 
	{
		delete m_currentScene;
	}

public:
	inline Scene& GetCurrentScene() const { return *m_currentScene; }
	
	void ChangeScene(Scene& newScene)
	{
		if (m_currentScene != nullptr)
		{
			m_currentScene->OnExit();

			delete m_currentScene;
			m_currentScene = nullptr;
		}

		m_currentScene = &newScene;
		m_currentScene->OnEnter();
	}

private:
	Scene* m_currentScene = nullptr;
};

