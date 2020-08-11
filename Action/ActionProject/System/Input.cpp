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
	const char* eventname = "OK";
	RegistAcceptPeripheral("OK", { {PeripheralType::keyboard,KEY_INPUT_RETURN}, {PeripheralType::gamepad,PAD_INPUT_M} });
	RegistAcceptPeripheral("pause", { {PeripheralType::keyboard,KEY_INPUT_P}, {PeripheralType::gamepad,PAD_INPUT_START} });
	RegistAcceptPeripheral("cancel", { {PeripheralType::keyboard,KEY_INPUT_BACK}, {PeripheralType::gamepad,PAD_INPUT_H} });
	RegistAcceptPeripheral("up", { {PeripheralType::keyboard,KEY_INPUT_UP}, {PeripheralType::gamepad,PAD_INPUT_UP} });
	RegistAcceptPeripheral("down", { {PeripheralType::keyboard,KEY_INPUT_DOWN}, {PeripheralType::gamepad,PAD_INPUT_DOWN} });
	RegistAcceptPeripheral("left", { {PeripheralType::keyboard,KEY_INPUT_LEFT}, {PeripheralType::gamepad,PAD_INPUT_LEFT} });
	RegistAcceptPeripheral("right", { {PeripheralType::keyboard,KEY_INPUT_RIGHT}, {PeripheralType::gamepad,PAD_INPUT_RIGHT} });
	RegistAcceptPeripheral("shot", { {PeripheralType::keyboard,KEY_INPUT_LSHIFT}, {PeripheralType::gamepad,PAD_INPUT_B} });
	RegistAcceptPeripheral("jump", { {PeripheralType::keyboard,KEY_INPUT_SPACE}, {PeripheralType::gamepad,PAD_INPUT_C} });
	RegistAcceptPeripheral("change", { {PeripheralType::keyboard,KEY_INPUT_C}, {PeripheralType::gamepad,PAD_INPUT_A} });
	currentInputIndex = 0;
	//keyPair_.emplace_back(make_pair("OK", KEY_INPUT_RETURN));
	//keyPair_.emplace_back(make_pair("pause", KEY_INPUT_P));
	//keyPair_.emplace_back(make_pair("cancel", KEY_INPUT_BACK));
	//keyPair_.emplace_back(make_pair("up", KEY_INPUT_UP));
	//keyPair_.emplace_back(make_pair("down", KEY_INPUT_DOWN));
	//keyPair_.emplace_back(make_pair("left", KEY_INPUT_LEFT));
	//keyPair_.emplace_back(make_pair("right", KEY_INPUT_RIGHT));
	//keyPair_.emplace_back(make_pair("shot", KEY_INPUT_LSHIFT));
	//keyPair_.emplace_back(make_pair("change", KEY_INPUT_C));
	//keyPair_.emplace_back(make_pair("jump", KEY_INPUT_SPACE));

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
