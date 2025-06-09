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

TitleScene::~TitleScene()
{
}

void TitleScene::OnEnter()
{
	screen.Clear();
}

void TitleScene::OnExit()
{
	screen.Clear();
}

void TitleScene::Update()
{
	if (input.HasCommand())
	{
		std::wstring cmd = input.GetCommand();
		if (cmd == L"Start")
		{
			GameInstance::Instance().GetSceneManager().ChangeScene(std::make_unique<MainScene>(screen, input));
		}
	}
}

void TitleScene::Render()
{
	// Frame
	screen.Write(0, 0, L"忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

	for (int y = 1; y <= 28; ++y)
	{
		screen.Write(0, y, L"弛");
		screen.Write(126, y, L"弛");
	}
	screen.Write(0, 27, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");
	screen.Write(0, 29, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");
	screen.Write(0, 30, L"弛");
	screen.Write(126, 30, L"弛");
	screen.Write(0, 31, L"戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

	// Title
	const short titlePosX = 22;
	screen.Write(titlePosX, 5, L"::::::::::: :::::::::: :::    ::: :::::::::::  :::::::::  :::::::::   ::::::::  ");
	screen.Write(titlePosX, 6, L"    :+:     :+:        :+:    :+:     :+:      :+:    :+: :+:    :+: :+:    :+:  ");
	screen.Write(titlePosX, 7, L"    +:+     +:+         +:+  +:+      +:+      +:+    +:+ +:+    +:+ +:+        ");
	screen.Write(titlePosX, 8, L"    +#+     +#++:++#     +#++:+       +#+      +#++:++#:  +#++:++#+  :#:        ");
	screen.Write(titlePosX, 9, L"    +#+     +#+         +#+  +#+      +#+      +#+    +#+ +#+        +#+   +#+# ");
	screen.Write(titlePosX, 10, L"    #+#     #+#        #+#    #+#     #+#      #+#    #+# #+#        #+#    #+# ");
	screen.Write(titlePosX, 11, L"    ###     ########## ###    ###     ###      ###    ### ###         ########  ");

	// Command List
	screen.Write(2, 28, L"Command List : Start, End");
	screen.Write(2, 30, L"Command > " + input.GetInputBuffer());
}