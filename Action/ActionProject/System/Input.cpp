#include "Input.h"
#include <DxLib.h>
#include <unordered_map>
#include <cassert>
#include <array>

using namespace std;

namespace
{
	constexpr int keyBufferSize = 256;	// �L�[�o�b�t�@�傫��
	wstring vkeyname[keyBufferSize];
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
Input::Input()
{
	const char* eventname = "OK";
	RegistAcceptPeripheral("OK", { {PeripheralType::keyboard,KEY_INPUT_RETURN}, {PeripheralType::gamepad,PAD_INPUT_R} });
	RegistAcceptPeripheral("pause", { {PeripheralType::keyboard,KEY_INPUT_P}, {PeripheralType::gamepad,PAD_INPUT_L} });
	RegistAcceptPeripheral("cancel", { {PeripheralType::keyboard,KEY_INPUT_BACK}, {PeripheralType::gamepad,PAD_INPUT_Z} });
	RegistAcceptPeripheral("up", { {PeripheralType::keyboard,KEY_INPUT_UP}, {PeripheralType::gamepad,PAD_INPUT_UP} });
	RegistAcceptPeripheral("down", { {PeripheralType::keyboard,KEY_INPUT_DOWN}, {PeripheralType::gamepad,PAD_INPUT_DOWN} });
	RegistAcceptPeripheral("left", { {PeripheralType::keyboard,KEY_INPUT_LEFT}, {PeripheralType::gamepad,PAD_INPUT_LEFT} });
	RegistAcceptPeripheral("right", { {PeripheralType::keyboard,KEY_INPUT_RIGHT}, {PeripheralType::gamepad,PAD_INPUT_RIGHT} });
	RegistAcceptPeripheral("shot", { {PeripheralType::keyboard,KEY_INPUT_LSHIFT}, {PeripheralType::gamepad,PAD_INPUT_A} });
	RegistAcceptPeripheral("jump", { {PeripheralType::keyboard,KEY_INPUT_SPACE}, {PeripheralType::gamepad,PAD_INPUT_B} });
	RegistAcceptPeripheral("change", { {PeripheralType::keyboard,KEY_INPUT_C}, {PeripheralType::gamepad,PAD_INPUT_X} });
	currentInputIndex = 0;
	/*"OK",PAD_INPUT_M;
	"pause",PAD_INPUT_START;
	"cancel",PAD_INPUT_H;
	"up",PAD_INPUT_UP;
	"down",PAD_INPUT_DOWN;
	"left",PAD_INPUT_LEFT;
	"right", PAD_INPUT_RIGHT;
	"shot", PAD_INPUT_B;
	"jump",PAD_INPUT_C;
	"change",PAD_INPUT_A;*/
	for (auto& currentTbl : _inputStateTable)
	{
		for (auto& refTbl : peripheralReferenceTable_)
		{
			currentTbl[refTbl.first] = false;
		}
	}
}

void Input::Update()
{
	// �t���b�v�����F����܂ŗ����������̂ɐ؂�ւ���
	currentInputIndex = GetNextIndexBufferIndex();
	int pad = 0;
	if (GetJoypadNum() > 0)
	{
		pad = GetJoypadInputState(DX_INPUT_PAD1);
	}
	char keyState[keyBufferSize];
	GetHitKeyStateAll(keyState);
	for (auto& refTbl : peripheralReferenceTable_)
	{
		CurrentInput(refTbl.first) = CheckPressed(refTbl.first.c_str(), keyState, pad);
	}
	if (isRawMode_)
	{
		if (GetJoypadNum() > 0)
		{
			rawPadState_ = pad;
		}
		copy(begin(keyState), end(keyState), rawKeyState_.begin());
	}

	
}

bool Input::IsPressed(const char * cmd) const
{
	return GetCurrentInput(cmd);
}

bool Input::IsReleased(const char * cmd) const
{
	return (!IsPressed(cmd) && LastIndex(cmd));
}

bool Input::IsTriggered(const char * cmd) const
{
	return (IsPressed(cmd) && !LastIndex(cmd));
}

int Input::GetNextIndexBufferIndex()
{
	return (static_cast<int>(currentInputIndex + 1)) % static_cast<int>(_inputStateTable.size());
}

bool& Input::CurrentInput(const std::string& cmd)
{
	auto& currentTbl = _inputStateTable[currentInputIndex];
	auto it = currentTbl.find(cmd);
	assert(it != currentTbl.end());
	return it->second;
}

bool Input::GetCurrentInput(const std::string& cmd) const
{
	auto& currentTbl = _inputStateTable[currentInputIndex];
	auto it = currentTbl.find(cmd);
	assert(it != currentTbl.end());
	return it->second;
}

size_t Input::GetLastInputBufferIndex()const
{
	return (static_cast<int>((currentInputIndex - 1 + _inputStateTable.size())) % static_cast<int>(_inputStateTable.size()));
}

bool Input::LastIndex(const std::string& cmd)const
{
	auto lastIndex = GetLastInputBufferIndex();
	auto& lastTbl = _inputStateTable[lastIndex];
	return lastTbl.at(cmd);
}

void Input::RegistAcceptPeripheral(const char* eventname, const vector<PeripheralInfo>& peri)
{
	peripheralReferenceTable_.try_emplace(eventname, peri);
}

bool Input::CheckPressed(const char* eventname, const char* keystate, int padstate)
{
	bool ret = false;
	for (auto& p : peripheralReferenceTable_[eventname])
	{
		if (p.type == PeripheralType::keyboard)
		{
			ret = ret || keystate[p.index];
		}
		else if (p.type == PeripheralType::gamepad)
		{
			ret = ret || (padstate&p.index);
		}
	}
	return ret;
}

const std::vector<char>& Input::GetRawKeyboardState() const
{
	//assert(isRawMode_);
	return rawKeyState_;
}

const int Input::GetRawPadState() const
{
//	assert(isRawMode_);
	return rawPadState_;
}

void Input::UnLockRawMode() const
{
	// ���̊֐���const����mutable�ϐ��݂͕̂ύX�\
	isRawMode_ = true;
	rawKeyState_.resize(keyBufferSize);
}

void Input::LockRawMode() const
{
	rawPadState_ = 0;
	rawKeyState_.clear();
	isRawMode_ = false;
}

void Input::SetPeripheralReferenceTable(const PeripheralReferenceTable_t& prt) const
{
	for (auto& p : prt)
	{
		peripheralReferenceTable_[p.first] = p.second;
	}
	
}