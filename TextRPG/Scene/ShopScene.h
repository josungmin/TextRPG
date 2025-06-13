#pragma once
#include "Scene.h"
#include <vector>
#include <string>
#include "../TextPrompt.h"

using namespace std;

enum class EShopSceneState : uint8
{
	Default,
	Sell,
	Buy,
};

class ShopScene : public Scene
{
public:
	ShopScene(Screen& screen, Input& input, TextPrompt& textPrompt);
	~ShopScene();

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	void ShowShopMenu();
	void ShowBuyMenu();
	void ShowSellMenu();
	void HandleBuyCommand(const wstring& cmd);
	void HandleSellCommand(const wstring& cmd);

private:
	vector<wstring> m_sellingItems;
	EShopSceneState m_currentSceneState;
};