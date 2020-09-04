#include "KeyConfigScene.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "SceneController.h"
#include "../Arithmetic.h"


namespace
{
	const wchar_t* titleName = L"Key Config";
	constexpr int keyBufferSize = 256;	// キーバッファ大きさ
	std::wstring vkeyname[keyBufferSize];
	void InitVkeyName() {
		vkeyname[KEY_INPUT_RETURN] = L"ENTERキー";
		vkeyname[KEY_INPUT_ESCAPE] = L"ESCキー";
		vkeyname[KEY_INPUT_0] = L"０キー";
		vkeyname[KEY_INPUT_1] = L"１キー";
		vkeyname[KEY_INPUT_2] = L"２キー";
		vkeyname[KEY_INPUT_3] = L"３キー";
		vkeyname[KEY_INPUT_4] = L"４キー";
		vkeyname[KEY_INPUT_5] = L"５キー";
		vkeyname[KEY_INPUT_6] = L"６キー";
		vkeyname[KEY_INPUT_7] = L"７キー";
		vkeyname[KEY_INPUT_8] = L"８キー";
		vkeyname[KEY_INPUT_9] = L"９キー";
		vkeyname[KEY_INPUT_A] = L"Ａキー";
		vkeyname[KEY_INPUT_B] = L"Ｂキー";
		vkeyname[KEY_INPUT_C] = L"Ｃキー";
		vkeyname[KEY_INPUT_D] = L"Ｄキー";
		vkeyname[KEY_INPUT_E] = L"Ｅキー";
		vkeyname[KEY_INPUT_F] = L"Ｆキー";
		vkeyname[KEY_INPUT_G] = L"Ｇキー";
		vkeyname[KEY_INPUT_H] = L"Ｈキー";
		vkeyname[KEY_INPUT_I] = L"Ｉキー";
		vkeyname[KEY_INPUT_J] = L"Ｊキー";
		vkeyname[KEY_INPUT_K] = L"Ｋキー";
		vkeyname[KEY_INPUT_L] = L"Ｌキー";
		vkeyname[KEY_INPUT_M] = L"Ｍキー";
		vkeyname[KEY_INPUT_N] = L"Ｎキー";
		vkeyname[KEY_INPUT_O] = L"Ｏキー";
		vkeyname[KEY_INPUT_P] = L"Ｐキー";
		vkeyname[KEY_INPUT_Q] = L"Ｑキー";
		vkeyname[KEY_INPUT_R] = L"Ｒキー";
		vkeyname[KEY_INPUT_S] = L"Ｓキー";
		vkeyname[KEY_INPUT_T] = L"Ｔキー";
		vkeyname[KEY_INPUT_U] = L"Ｕキー";
		vkeyname[KEY_INPUT_V] = L"Ｖキー";
		vkeyname[KEY_INPUT_W] = L"Ｗキー";
		vkeyname[KEY_INPUT_X] = L"Ｘキー";
		vkeyname[KEY_INPUT_Y] = L"Ｙキー";
		vkeyname[KEY_INPUT_Z] = L"Ｚキー";
		vkeyname[KEY_INPUT_BACK] = L"BackSpaceキー";
		vkeyname[KEY_INPUT_TAB] = L"Tabキー";
		vkeyname[KEY_INPUT_LSHIFT] = L"左Shiftキー";
		vkeyname[KEY_INPUT_RSHIFT] = L"右Shiftキー";
		vkeyname[KEY_INPUT_LCONTROL] = L"左Ctrlキー";
		vkeyname[KEY_INPUT_RCONTROL] = L"右Ctrlキー";
		vkeyname[KEY_INPUT_ESCAPE] = L"Escキー";
		vkeyname[KEY_INPUT_SPACE] = L"スペースキー";
		vkeyname[KEY_INPUT_PGUP] = L"PageUpキー";
		vkeyname[KEY_INPUT_PGDN] = L"PageDownキー";
		vkeyname[KEY_INPUT_END] = L"Endキー";
		vkeyname[KEY_INPUT_HOME] = L"Homeキー";
		vkeyname[KEY_INPUT_LEFT] = L"左キー";
		vkeyname[KEY_INPUT_UP] = L"上キー";
		vkeyname[KEY_INPUT_RIGHT] = L"右キー";
		vkeyname[KEY_INPUT_DOWN] = L"下キー";
		vkeyname[KEY_INPUT_INSERT] = L"Insertキー";
		vkeyname[KEY_INPUT_DELETE] = L"Deleteキー";
		vkeyname[KEY_INPUT_F1] = L"Ｆ１キー";
		vkeyname[KEY_INPUT_F2] = L"Ｆ２キー";
		vkeyname[KEY_INPUT_F3] = L"Ｆ３キー";
		vkeyname[KEY_INPUT_F4] = L"Ｆ４キー";
		vkeyname[KEY_INPUT_F5] = L"Ｆ５キー";
		vkeyname[KEY_INPUT_F6] = L"Ｆ６キー";
		vkeyname[KEY_INPUT_F7] = L"Ｆ７キー";
		vkeyname[KEY_INPUT_F8] = L"Ｆ８キー";
		vkeyname[KEY_INPUT_F9] = L"Ｆ９キー";
		vkeyname[KEY_INPUT_F10] = L"Ｆ１０キー";
		vkeyname[KEY_INPUT_F11] = L"Ｆ１１キー";
		vkeyname[KEY_INPUT_F12] = L"Ｆ１２キー";
	}
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
	InitVkeyName();
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
				auto& rawKeyState = input.GetRawKeyboardState();
				for (int i = 0; i < input.rawKeyState_.size(); ++i) {
					if (rawKeyState[i]) {
						p.index = i;
						break;
					}
				}
			}
			else if (p.type == PeripheralType::gamepad) {
				const auto& rawPadState = input.GetRawPadState();
				if (rawPadState != 0) {
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
	DrawBoxAA(frameRect.Left(), frameRect.Top(), frameRect.Right(), frameRect.Bottom(), 0xbb00aa, true);
	DrawBoxAA(frameRect.Left(), frameRect.Top(), frameRect.Right(), frameRect.Bottom(), 0xffffff, false);
	int titleW = GetDrawStringWidth(titleName, static_cast<int>(wcslen(titleName)));
	DrawStringF(frameRect.pos.x - titleW / 2, frameRect.Top() + 32, titleName, 0xffffff);
	int offset_x = 50;
	auto offset_y = frameRect.Top() + 64;
	uint32_t col = 0xffffff;
	for (auto p : peripheralReferenceTable_)
	{		
		auto str = GetWideStringFromString(p.first);
		DrawStringF(frameRect.Left() + offset_x, offset_y, str.c_str(), col);
		offset_x += 100;
		if (p.first == menuItems_[currentSelectNo_])
		{
			if (updater_ == &KeyConfigScene::EditUpdate)
			{
				offset_x += 20;
				col = 0x0000ff;
			}
			else
			{
				col = 0x00aaff;
			}
		}	
		auto i = vkeyname[p.second[static_cast<int>(PeripheralType::keyboard)].index];
		DrawFormatStringF(frameRect.Left() + offset_x, offset_y, col,(L"keybord=" +vkeyname[p.second[static_cast<int>(PeripheralType::keyboard)].index]).c_str());
		offset_x += 200;
		DrawFormatStringF(frameRect.Left() + offset_x, offset_y, col, L"gamepad=%05x", p.second[static_cast<int>(PeripheralType::gamepad)].index);
		offset_y += 32;

		offset_x = 50;
		col = 0xffffff;
	}
	if (menuItems_[currentSelectNo_] == "commit")
	{
		col = 0x00aaff;
	}
	DrawStringF(frameRect.Left() + offset_x, offset_y,L"決定", col);

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
