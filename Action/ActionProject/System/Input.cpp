#include "Input.h"
#include <DxLib.h>
#include <unordered_map>
#include <cassert>
#include <array>

using namespace std;

namespace
{
	constexpr int keyBufferSize = 256;	// キーバッファ大きさ
	wstring vkeyname[keyBufferSize];
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
	// フリップ処理：それまで裏だったものに切り替える
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
	// この関数はconstだがmutable変数のみは変更可能
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