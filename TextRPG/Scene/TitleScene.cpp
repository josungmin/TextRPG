#include "TitleScene.h"
#include <string>
#include <memory>
#include <cassert>

#include "../GameInstance.h"
#include "../Screen.h"
#include "../Input.h"
#include "SceneManager.h"
#include "MainScene.h"


TitleScene::TitleScene(Screen& screen, Input& input)
	:Scene(screen, input)
{
}

void TitleScene::OnEnter()
{
	m_screen.Clear();
}

void TitleScene::OnExit()
{
	m_screen.Clear();
}

void TitleScene::Update()
{
	if (m_input.HasCommand())
	{
		std::wstring cmd = m_input.GetCommand();
		if (cmd == L"시작" || cmd == L"1" || cmd == L"1.시작" || cmd == L"1시작")
		{
			Scene* mainScene = new MainScene(m_screen, m_input);
			GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
		}
	}
}

void TitleScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"│");
		m_screen.Write(126, y, L"│");
	}
	m_screen.Write(0, 27, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	m_screen.Write(0, 29, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	m_screen.Write(0, 30, L"│");
	m_screen.Write(126, 30, L"│");
	m_screen.Write(0, 31, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");

	// Title
	const short titlePosX = 22;
	m_screen.Write(titlePosX, 5, L"::::::::::: :::::::::: :::    ::: :::::::::::  :::::::::  :::::::::   ::::::::  ");
	m_screen.Write(titlePosX, 6, L"    :+:     :+:        :+:    :+:     :+:      :+:    :+: :+:    :+: :+:    :+:  ");
	m_screen.Write(titlePosX, 7, L"    +:+     +:+         +:+  +:+      +:+      +:+    +:+ +:+    +:+ +:+        ");
	m_screen.Write(titlePosX, 8, L"    +#+     +#++:++#     +#++:+       +#+      +#++:++#:  +#++:++#+  :#:        ");
	m_screen.Write(titlePosX, 9, L"    +#+     +#+         +#+  +#+      +#+      +#+    +#+ +#+        +#+   +#+# ");
	m_screen.Write(titlePosX, 10, L"    #+#     #+#        #+#    #+#     #+#      #+#    #+# #+#        #+#    #+# ");
	m_screen.Write(titlePosX, 11, L"    ###     ########## ###    ###     ###      ###    ### ###         ########  ");

	// Command List
	m_screen.Write(2, 28, L"명령 목록 : 1.시작, 2.종료");
	m_screen.Write(2, 30, L"명령 > " + m_input.GetInputBuffer());
}