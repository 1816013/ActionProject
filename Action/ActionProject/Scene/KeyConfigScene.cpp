#include "KeyConfigScene.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "SceneController.h"
#include "../Arithmetic.h"


namespace
{
	const wchar_t* titleName = L"Key Config";
	constexpr int keyBufferSize = 256;	// �L�[�o�b�t�@�傫��
	std::wstring vkeyname[keyBufferSize];
	void InitVkeyName() {
		vkeyname[KEY_INPUT_RETURN] = L"ENTER�L�[";
		vkeyname[KEY_INPUT_ESCAPE] = L"ESC�L�[";
		vkeyname[KEY_INPUT_0] = L"�O�L�[";
		vkeyname[KEY_INPUT_1] = L"�P�L�[";
		vkeyname[KEY_INPUT_2] = L"�Q�L�[";
		vkeyname[KEY_INPUT_3] = L"�R�L�[";
		vkeyname[KEY_INPUT_4] = L"�S�L�[";
		vkeyname[KEY_INPUT_5] = L"�T�L�[";
		vkeyname[KEY_INPUT_6] = L"�U�L�[";
		vkeyname[KEY_INPUT_7] = L"�V�L�[";
		vkeyname[KEY_INPUT_8] = L"�W�L�[";
		vkeyname[KEY_INPUT_9] = L"�X�L�[";
		vkeyname[KEY_INPUT_A] = L"�`�L�[";
		vkeyname[KEY_INPUT_B] = L"�a�L�[";
		vkeyname[KEY_INPUT_C] = L"�b�L�[";
		vkeyname[KEY_INPUT_D] = L"�c�L�[";
		vkeyname[KEY_INPUT_E] = L"�d�L�[";
		vkeyname[KEY_INPUT_F] = L"�e�L�[";
		vkeyname[KEY_INPUT_G] = L"�f�L�[";
		vkeyname[KEY_INPUT_H] = L"�g�L�[";
		vkeyname[KEY_INPUT_I] = L"�h�L�[";
		vkeyname[KEY_INPUT_J] = L"�i�L�[";
		vkeyname[KEY_INPUT_K] = L"�j�L�[";
		vkeyname[KEY_INPUT_L] = L"�k�L�[";
		vkeyname[KEY_INPUT_M] = L"�l�L�[";
		vkeyname[KEY_INPUT_N] = L"�m�L�[";
		vkeyname[KEY_INPUT_O] = L"�n�L�[";
		vkeyname[KEY_INPUT_P] = L"�o�L�[";
		vkeyname[KEY_INPUT_Q] = L"�p�L�[";
		vkeyname[KEY_INPUT_R] = L"�q�L�[";
		vkeyname[KEY_INPUT_S] = L"�r�L�[";
		vkeyname[KEY_INPUT_T] = L"�s�L�[";
		vkeyname[KEY_INPUT_U] = L"�t�L�[";
		vkeyname[KEY_INPUT_V] = L"�u�L�[";
		vkeyname[KEY_INPUT_W] = L"�v�L�[";
		vkeyname[KEY_INPUT_X] = L"�w�L�[";
		vkeyname[KEY_INPUT_Y] = L"�x�L�[";
		vkeyname[KEY_INPUT_Z] = L"�y�L�[";
		vkeyname[KEY_INPUT_BACK] = L"BackSpace�L�[";
		vkeyname[KEY_INPUT_TAB] = L"Tab�L�[";
		vkeyname[KEY_INPUT_LSHIFT] = L"��Shift�L�[";
		vkeyname[KEY_INPUT_RSHIFT] = L"�EShift�L�[";
		vkeyname[KEY_INPUT_LCONTROL] = L"��Ctrl�L�[";
		vkeyname[KEY_INPUT_RCONTROL] = L"�ECtrl�L�[";
		vkeyname[KEY_INPUT_ESCAPE] = L"Esc�L�[";
		vkeyname[KEY_INPUT_SPACE] = L"�X�y�[�X�L�[";
		vkeyname[KEY_INPUT_PGUP] = L"PageUp�L�[";
		vkeyname[KEY_INPUT_PGDN] = L"PageDown�L�[";
		vkeyname[KEY_INPUT_END] = L"End�L�[";
		vkeyname[KEY_INPUT_HOME] = L"Home�L�[";
		vkeyname[KEY_INPUT_LEFT] = L"���L�[";
		vkeyname[KEY_INPUT_UP] = L"��L�[";
		vkeyname[KEY_INPUT_RIGHT] = L"�E�L�[";
		vkeyname[KEY_INPUT_DOWN] = L"���L�[";
		vkeyname[KEY_INPUT_INSERT] = L"Insert�L�[";
		vkeyname[KEY_INPUT_DELETE] = L"Delete�L�[";
		vkeyname[KEY_INPUT_F1] = L"�e�P�L�[";
		vkeyname[KEY_INPUT_F2] = L"�e�Q�L�[";
		vkeyname[KEY_INPUT_F3] = L"�e�R�L�[";
		vkeyname[KEY_INPUT_F4] = L"�e�S�L�[";
		vkeyname[KEY_INPUT_F5] = L"�e�T�L�[";
		vkeyname[KEY_INPUT_F6] = L"�e�U�L�[";
		vkeyname[KEY_INPUT_F7] = L"�e�V�L�[";
		vkeyname[KEY_INPUT_F8] = L"�e�W�L�[";
		vkeyname[KEY_INPUT_F9] = L"�e�X�L�[";
		vkeyname[KEY_INPUT_F10] = L"�e�P�O�L�[";
		vkeyname[KEY_INPUT_F11] = L"�e�P�P�L�[";
		vkeyname[KEY_INPUT_F12] = L"�e�P�Q�L�[";
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
		// �G�f�B�b�g����O�ɖ߂�
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
	// �g�̕`��
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
	DrawStringF(frameRect.Left() + offset_x, offset_y,L"����", col);

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
	// �����񐔎擾
	auto num1 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
		str.c_str(), -1, nullptr, 0);
	std::wstring wstr;
	wstr.resize(num1);	// �������Ń��T�C�Y

	// wstr�ɕϊ���������R�s�[
	auto num2 = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
		str.c_str(), -1, &wstr[0], num1);
	assert(num1 == num2);
	return wstr;
}

void KeyConfigScene::CommitCurrentKeyConfig(const Input& input)
{
	input.SetPeripheralReferenceTable(peripheralReferenceTable_);
}
