#pragma once
#include "Scene.h"
#include <vector>

#include "../TextPrompt.h"

using namespace std;

enum class EShopSceneState : uint8_t
{
	Default,
	Sell,
	Buy,
};


class ShopScene : public Scene
{
public:
	ShopScene(Screen& screen, Input& input);
	~ShopScene();

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	TextPrompt m_textPrompt;
	vector<wstring> m_sellingItems; //TODO: 변수명 변경?
	EShopSceneState m_currentSceneState;
};