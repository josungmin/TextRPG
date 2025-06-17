#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include "../TextPrompt.h"

using namespace std;

class ShopScene : public Scene
{
public:
	enum class EShopSceneState : uint8
	{
		None,
		Default,
		Sell,
		Buy,
		Max,
	};

public:
	ShopScene(Screen& screen, Input& input, TextPrompt& textPrompt);
	virtual ~ShopScene() = default;

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	void EnableShopMenu();
	void EnableBuyMenu();
	void EnableSellMenu();
	void HandleBuyCommand(const uint8 shopItemIndex);
	void HandleSellCommand(const wstring& cmd);

private:
	vector<wstring> m_shopItemList;
	EShopSceneState m_currentSceneState;
};