#include "ShopScene.h"
#include "../GameInstance.h"
#include "MainScene.h"

ShopScene::ShopScene(Screen& screen, Input& input)
	:Scene(screen, input), m_textPrompt(screen, 34, 3)
{
	m_sellingItems.reserve(4);
	m_sellingItems.push_back(L"최하급 검");
	m_sellingItems.push_back(L"하급 검");
	m_sellingItems.push_back(L"일반 검");
	m_sellingItems.push_back(L"최하급 갑옷");

	m_currentSceneState = EShopSceneState::Default;
}

ShopScene::~ShopScene()
{
	
}

void ShopScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"시스템 : 상점에 입장합니다.");
	m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
	m_textPrompt.Enqueue(L"시스템 : 1.구매 2.판매 3.나가기");
}

void ShopScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void ShopScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand())
	{
		std::wstring cmd = m_input.GetCommand();

		if (m_currentSceneState == EShopSceneState::Default)
		{
			if (cmd == L"1" || cmd == L"구매" || cmd == L"1.구매" || cmd == L"1구매")
			{
				m_currentSceneState = EShopSceneState::Buy;
			}
			else if (cmd == L"2" || cmd == L"판매" || cmd == L"2.판매" || cmd == L"2판매")
			{
				m_currentSceneState = EShopSceneState::Sell;
			}
			else if (cmd == L"3" || cmd == L"나가기" || cmd == L"3.나가기" || cmd == L"3나가기")
			{
				Scene* mainScene = new MainScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
			}
		}

		if (m_currentSceneState == EShopSceneState::Buy)
		{
			
		}

		if (m_currentSceneState == EShopSceneState::Sell)
		{
			
		}
	}
}

void ShopScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"│");
		m_screen.Write(32, y, L"│");
		m_screen.Write(126, y, L"│");
	}

	m_screen.Write(13, 1, L"[ 능력치 ]");
	m_screen.Write(73, 1, L"<< 상점 >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────");
	m_screen.Write(2, 3, L"이름: " + player.GetName());
	m_screen.Write(2, 4, L"정보: " + player.GetDescription());
	m_screen.Write(2, 5, L"골드: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 6, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 7, L"공격력: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 8, L"방어력: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 9, L"민첩: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 11, L"장착 아이템:");
	m_screen.Write(2, 12, L"무기: " + (player.GetEquipment().GetWeapon() == nullptr ? L"미장착" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 13, L"방어구: " + (player.GetEquipment().GetArmor() == nullptr ? L"미장착" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 15, L"인벤토리: ");
	m_screen.Write(2, 16, L"최하급 검"); // TODO: 아이템 목록 출력

	m_screen.Write(0, 29, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	m_screen.Write(0, 30, L"│"); m_screen.Write(2, 30, L"명령 > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"│");
	m_screen.Write(0, 31, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");

	m_textPrompt.Render();
}
