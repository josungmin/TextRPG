#include "ShopScene.h"
#include "../GameInstance.h"
#include "MainScene.h"

ShopScene::ShopScene(Screen& screen, Input& input)
	:Scene(screen, input), m_textPrompt(screen, 34, 3)
{
	m_sellingItems.reserve(4);
	m_sellingItems.push_back(L"���ϱ� ��");
	m_sellingItems.push_back(L"�ϱ� ��");
	m_sellingItems.push_back(L"�Ϲ� ��");
	m_sellingItems.push_back(L"���ϱ� ����");

	m_currentSceneState = EShopSceneState::Default;
}

ShopScene::~ShopScene()
{
	
}

void ShopScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");
	m_textPrompt.Enqueue(L"�ý��� : � �ൿ�� �Ͻðڽ��ϱ�?");
	m_textPrompt.Enqueue(L"�ý��� : 1.���� 2.�Ǹ� 3.������");
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
			if (cmd == L"1" || cmd == L"����" || cmd == L"1.����" || cmd == L"1����")
			{
				m_currentSceneState = EShopSceneState::Buy;
			}
			else if (cmd == L"2" || cmd == L"�Ǹ�" || cmd == L"2.�Ǹ�" || cmd == L"2�Ǹ�")
			{
				m_currentSceneState = EShopSceneState::Sell;
			}
			else if (cmd == L"3" || cmd == L"������" || cmd == L"3.������" || cmd == L"3������")
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
	m_screen.Write(0, 0, L"����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"��");
		m_screen.Write(32, y, L"��");
		m_screen.Write(126, y, L"��");
	}

	m_screen.Write(13, 1, L"[ �ɷ�ġ ]");
	m_screen.Write(73, 1, L"<< ���� >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(2, 3, L"�̸�: " + player.GetName());
	m_screen.Write(2, 4, L"����: " + player.GetDescription());
	m_screen.Write(2, 5, L"���: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 6, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 7, L"���ݷ�: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 8, L"����: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 9, L"��ø: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 11, L"���� ������:");
	m_screen.Write(2, 12, L"����: " + (player.GetEquipment().GetWeapon() == nullptr ? L"������" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 13, L"��: " + (player.GetEquipment().GetArmor() == nullptr ? L"������" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 15, L"�κ��丮: ");
	m_screen.Write(2, 16, L"���ϱ� ��"); // TODO: ������ ��� ���

	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"��� > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	m_textPrompt.Render();
}
