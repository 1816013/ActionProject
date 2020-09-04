#include "Input.h"
#include <DxLib.h>
#include <unordered_map>
#include <cassert>
#include <array>

using namespace std;

namespace
{
	constexpr int keyBufferSize = 256;	// キーバッファ大きさ
}
Input::Input()
{
	//const char* eventname = "OK";
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