#include "Input.h"
#include <DxLib.h>
#include <unordered_map>
#include <cassert>
#include <array>

using namespace std;

namespace
{
	constexpr int inputRecordSize = 2;	// ���̓o�b�t�@�i�[��
	constexpr int keyBufferSize = 256;	// �L�[�o�b�t�@�傫��
	int currentInputIndex = 0;	// ���݂̓��̓o�b�t�@���w���C���f�b�N�X
	using InputStateTable_t = array<unordered_map<string, bool>, inputRecordSize>;
	InputStateTable_t _inputStateTable;	// ���͊i�[�e�[�u��

	/// <summary>
/// ���̓��̓o�b�t�@�C���f�b�N�X��Ԃ�
/// </summary>
	int GetNextIndexBufferIndex()
	{
		return  (static_cast<int>(currentInputIndex + 1)) % static_cast<int>(_inputStateTable.size());

	}
	/// <summary>
	/// ���̓��͏���Ԃ�
	/// </summary>
	/// <param name = "cmd">�R�}���h������</param>
	bool& CurrentInput(const std::string &cmd)
	{
		auto& currentTbl = _inputStateTable[currentInputIndex];
		auto it = currentTbl.find(cmd);
		assert(it != currentTbl.end());
		return it->second;
	}

	/// <summary>
	/// 1�t���[���O�̓��̓o�b�t�@�C���f�b�N�X��Ԃ�
	/// </summary>
	size_t GetLastInputBufferIndex()
	{
		return (static_cast<int>((currentInputIndex - 1 + _inputStateTable.size())) % static_cast<int>(_inputStateTable.size()));
	}
	/// <summary>
	/// ���O�̓��͏���Ԃ�
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
	keyPair_.emplace_back(make_pair("OK", KEY_INPUT_RETURN));
	keyPair_.emplace_back(make_pair("pause", KEY_INPUT_P));
	keyPair_.emplace_back(make_pair("up", KEY_INPUT_UP));
	keyPair_.emplace_back(make_pair("down", KEY_INPUT_DOWN));
	keyPair_.emplace_back(make_pair("left", KEY_INPUT_LEFT));
	keyPair_.emplace_back(make_pair("right", KEY_INPUT_RIGHT));
	keyPair_.emplace_back(make_pair("shot", KEY_INPUT_LSHIFT));
	keyPair_.emplace_back(make_pair("change", KEY_INPUT_C));
	//auto& currentTbl = _inputStateTable[currentInputIndex];
	for (auto& currentTbl : _inputStateTable)
	{
		for (auto& keycode : keyPair_)
		{
			currentTbl[keycode.first] = false;
		}
		/*currentTbl["OK"] = false;
		currentTbl["pause"] = false;
		currentTbl["up"] = false;
		currentTbl["down"] = false;
		currentTbl["left"] = false;
		currentTbl["right"] = false;
		currentTbl["shot"] = false;*/
	}
	//currentTbl["OK"] = false;
}

void Input::Update()
{
	// �t���b�v�����F����܂ŗ����������̂ɐ؂�ւ���
	currentInputIndex = GetNextIndexBufferIndex();

	char keyState[keyBufferSize];
	GetHitKeyStateAll(keyState);
	//auto& currentTbl = _inputStateTable[currentInputIndex];
	for (auto& keycode : keyPair_)
	{
		CurrentInput(keycode.first) = keyState[keycode.second];
	}
	/*CurrentInput("OK") = keyState[KEY_INPUT_RETURN];
	CurrentInput("pause") = keyState[KEY_INPUT_P];
	CurrentInput("up") = keyState[KEY_INPUT_UP];
	CurrentInput("down") = keyState[KEY_INPUT_DOWN];
	CurrentInput("left") = keyState[KEY_INPUT_LEFT];
	CurrentInput("right") = keyState[KEY_INPUT_RIGHT];
	CurrentInput("shot") = keyState[KEY_INPUT_LSHIFT];*/
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