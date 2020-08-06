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
	currentInputIndex = 0;
	keyPair_.emplace_back(make_pair("OK", KEY_INPUT_RETURN));
	keyPair_.emplace_back(make_pair("pause", KEY_INPUT_P));
	keyPair_.emplace_back(make_pair("up", KEY_INPUT_UP));
	keyPair_.emplace_back(make_pair("down", KEY_INPUT_DOWN));
	keyPair_.emplace_back(make_pair("left", KEY_INPUT_LEFT));
	keyPair_.emplace_back(make_pair("right", KEY_INPUT_RIGHT));
	keyPair_.emplace_back(make_pair("shot", KEY_INPUT_LSHIFT));
	keyPair_.emplace_back(make_pair("change", KEY_INPUT_C));
	keyPair_.emplace_back(make_pair("jump", KEY_INPUT_SPACE));

	for (auto& currentTbl : _inputStateTable)
	{
		for (auto& keycode : keyPair_)
		{
			currentTbl[keycode.first] = false;
		}
	}
}

void Input::Update()
{
	// フリップ処理：それまで裏だったものに切り替える
	currentInputIndex = GetNextIndexBufferIndex();

	char keyState[keyBufferSize];
	GetHitKeyStateAll(keyState);
	for (auto& keycode : keyPair_)
	{
		CurrentInput(keycode.first) = keyState[keycode.second];
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
