#include "KeyConfigScene.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "SceneController.h"
#include "../Arithmetic.h"


namespace
{
	const wchar_t* titleName = L"Key Config";

}
KeyConfigScene::KeyConfigScene(SceneController& controller) : 
	Scene(controller),
	updater_(&KeyConfigScene::InUpdate),
	drawer_(&KeyConfigScene::NomalDraw)
{
}

KeyConfigScene::~KeyConfigScene()
{
}

void KeyConfigScene::Update(const Input& input)
{
	(this->*updater_)(input);
}

void KeyConfigScene::Draw()
{
	(this->*drawer_)();
}

void KeyConfigScene::InUpdate(const Input& input)
{
	if (peripheralReferenceTable_.empty())
	{
		std::string removeEvents[] = { "up", "down", "left", "right" };
		for (const auto& ref : input.peripheralReferenceTable_)
		{
			if (std::count(begin(removeEvents), end(removeEvents), ref.first) == 0)
			{
				peripheralReferenceTable_.insert(ref);
			}
		}
		for (const auto& ref : peripheralReferenceTable_)
		{
			menuItems_.push_back(ref.first);
		}
		menuItems_.push_back("commit");
	}
	updater_ = &KeyConfigScene::NomalUpdate;
}

void KeyConfigScene::NomalUpdate(const Input& input)
{
	if (input.IsTriggered("down"))
	{
		currentSelectNo_ = ModuloIncrement(currentSelectNo_, menuItems_.size());
	}
	if (input.IsTriggered("up"))
	{
		currentSelectNo_ = ModuloDecrement(currentSelectNo_, menuItems_.size());
	}
	if (input.IsTriggered("OK"))
	{
		if (menuItems_[currentSelectNo_] == "commit")
		{
			CommitCurrentKeyConfig(input);
			CloseMenu();
		}
		else
		{
			input.UnLockRawMode();
			beforeKeyState_ = peripheralReferenceTable_;
			updater_ = &KeyConfigScene::EditUpdate;
		}	
	}

	if (input.IsTriggered("cancel"))
	{
		updater_ = &KeyConfigScene::CloseUpdate;
	}
}

void KeyConfigScene::EditUpdate(const Input& input)
{
	if (input.IsTriggered("OK"))
	{
		updater_ = &KeyConfigScene::NomalUpdate;
		input.LockRawMode();
	}
	else if(input.IsTriggered("cancel"))
	{
		// エディットする前に戻す
		peripheralReferenceTable_ = beforeKeyState_;
		input.LockRawMode();
		updater_ = &KeyConfigScene::NomalUpdate;
	}
	else
	{
		auto& ref = peripheralReferenceTable_[menuItems_[currentSelectNo_]];
		for (auto& p : ref) {
			if (p.type == PeripheralType::keyboard) {
				for (int i = 0; i < input.rawKeyState_.size(); ++i) {
					if (input.rawKeyState_[i]) {
						p.index = i;
						break;
					}
				}
			}
			else if (p.type == PeripheralType::gamepad) {
				if (input.rawPadState_ != 0) {
					p.index = input.rawPadState_;
				}
			}
		}
	}
}

void KeyConfigScene::OpenUpdate(const Input& input)
{
}

void KeyConfigScene::CloseUpdate(const Input& input)
{
	controller_.PopScene();
}



void KeyConfigScene::NomalDraw()
{
	// 枠の描画
	DrawBox(frameRect.Left(), frameRect.Top(), frameRect.Right(), frameRect.Bottom(), 0xbb00aa, true);
	DrawBox(frameRect.Left(), frameRect.Top(), frameRect.Right(), frameRect.Bottom(), 0xffffff, false);
	int titleW = GetDrawStringWidth(titleName, static_cast<int>(wcslen(titleName)));
	DrawString(frameRect.pos.x - titleW / 2, frameRect.Top() + 32, titleName, 0xffffff);
	int offset_x = 0;
	auto offset_y = frameRect.Top() + 64;
	uint32_t col = 0xffffff;
	for (auto ref : peripheralReferenceTable_)
	{
		offset_x = 100;
		col = 0xffffff;
		if (ref.first == menuItems_[currentSelectNo_])
		{
			if (updater_ == &KeyConfigScene::EditUpdate)
			{
				offset_x += 20;
				col = 0x00ffff;
			}
			else
			{
				col = 0x00aaff;
			}
		}	
		auto str = GetWideStringFromString(ref.first);
		DrawString(frameRect.Left() + offset_x, offset_y, str.c_str(), col);
		offset_x += 100;
		DrawFormatString(frameRect.Left() + offset_x, offset_y, col,L"keybord=%04x", ref.second[0].index);
		offset_x += 150;
		DrawFormatString(frameRect.Left() + offset_x, offset_y, col, L"gamepad=%04x", ref.second[1].index);
		offset_y += 32;
	}
	offset_x = 100;
	offset_y += 32;
	col = 0xffffff;
	if (menuItems_[currentSelectNo_] == "commit")
	{
		col = 0x00aaff;
	}
	DrawString(frameRect.Left() + offset_x, offset_y,L"決定", col);

}

void KeyConfigScene::OpenCloseDraw()
{
}

void KeyConfigScene::CloseMenu()
{
	controller_.PopScene();
}

std::wstring KeyConfigScene::GetWideStringFromString(const std::string str)
{
	// 文字列数取得
	auto num1 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
		str.c_str(), -1, nullptr, 0);
	std::wstring wstr;
	wstr.resize(num1);	// 文字数でリサイズ

	// wstrに変換文字列をコピー
	auto num2 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
		str.c_str(), -1, &wstr[0], num1);
	assert(num1 == num2);
	return wstr;
}

void KeyConfigScene::CommitCurrentKeyConfig(const Input& input)
{
	input.SetPeripheralReferenceTable(peripheralReferenceTable_);
}
