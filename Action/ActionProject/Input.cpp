#include "Input.h"
#include <DxLib.h>
#include <unordered_map>
#include <cassert>
#include <array>

using namespace std;

namespace
{
	constexpr int inputRecordSize = 2;	// 入力バッファ格納数
	constexpr int keyBufferSize = 256;	// キーバッファ大きさ
	int currentInputIndex = 0;	// 現在の入力バッファを指すインデックス
	using InputStateTable_t = array<unordered_map<string, bool>, inputRecordSize>;
	InputStateTable_t _inputStateTable;	// 入力格納テーブル

	/// <summary>
/// 次の入力バッファインデックスを返す
/// </summary>
	int GetNextIndexBufferIndex()
	{
		return  (static_cast<int>(currentInputIndex + 1)) % static_cast<int>(_inputStateTable.size());

	}
	/// <summary>
	/// 次の入力情報を返す
	/// </summary>
	/// <param name = "cmd">コマンド文字列</param>
	bool& CurrentInput(const std::string &cmd)
	{
		auto& currentTbl = _inputStateTable[currentInputIndex];
		auto it = currentTbl.find(cmd);
		assert(it != currentTbl.end());
		return it->second;
	}

	/// <summary>
	/// 1フレーム前の入力バッファインデックスを返す
	/// </summary>
	size_t GetLastInputBufferIndex()
	{
		return (static_cast<int>((currentInputIndex - 1 + _inputStateTable.size())) % static_cast<int>(_inputStateTable.size()));
	}
	/// <summary>
	/// 直前の入力情報を返す
	/// </summary>
	bool& LastIndex(const std::string &cmd)
	{
		auto lastIndex = GetLastInputBufferIndex();
		auto& lastTbl = _inputStateTable[lastIndex];
		return lastTbl[cmd];
	}
}
Input::Input()
{
	currentInputIndex = 0;
	//auto& currentTbl = _inputStateTable[currentInputIndex];
	for (auto& currentTbl : _inputStateTable)
	{
		currentTbl["OK"] = false;
		currentTbl["pause"] = false;
		currentTbl["up"] = false;
		currentTbl["down"] = false;
	}
	//currentTbl["OK"] = false;
}

void Input::Update()
{
	// フリップ処理：それまで裏だったものに切り替える
	currentInputIndex = GetNextIndexBufferIndex();

	char keyState[keyBufferSize];
	GetHitKeyStateAll(keyState);
	//auto& currentTbl = _inputStateTable[currentInputIndex];	
	CurrentInput("OK") = keyState[KEY_INPUT_RETURN];
	CurrentInput("pause") = keyState[KEY_INPUT_P];
	CurrentInput("up") = keyState[KEY_INPUT_UP];
	CurrentInput("down") = keyState[KEY_INPUT_DOWN];
}

bool Input::IsPressed(const char * cmd) const
{
	return CurrentInput(cmd);
}

bool Input::IsReleased(const char * cmd) const
{
	return (!IsPressed(cmd) && LastIndex(cmd));
}

bool Input::IsTriggered(const char * cmd) const
{
	return (IsPressed(cmd) && !LastIndex(cmd));
}