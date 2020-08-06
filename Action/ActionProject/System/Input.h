#pragma once
#include <vector>
#include <utility>
#include <string>
#include <array>
#include <unordered_map>

constexpr int inputRecordSize = 2;	// ���̓o�b�t�@�i�[��
enum class PeriphiralType
{
	keybord,
	pad
};
struct PeriphiralInfo
{
	PeriphiralType type;
	int index;
};
class Input
{
private:
	std::unordered_map<std::string, std::vector<PeriphiralType>>inputRefarenceTable_;
	int currentInputIndex = 0;	// ���݂̓��̓o�b�t�@���w���C���f�b�N�X
	using InputStateTable_t = std::unordered_map<std::string, bool>;
	std::array <InputStateTable_t, inputRecordSize>_inputStateTable;	// ���͊i�[�e�[�u��
	/// <summary>
	/// ���̓��̓o�b�t�@�C���f�b�N�X��Ԃ�
	/// </summary>
	int GetNextIndexBufferIndex();
	/// <summary>
	/// ���̓��͏���Ԃ�
	/// </summary>
	/// <param name = "cmd">�R�}���h������</param>
	bool& CurrentInput(const std::string& cmd);
	bool GetCurrentInput(const std::string& cmd)const;

	/// <summary>
	/// 1�t���[���O�̓��̓o�b�t�@�C���f�b�N�X��Ԃ�
	/// </summary>
	size_t GetLastInputBufferIndex()const;

	/// <summary>
	/// ���O�̓��͏���Ԃ�
	/// </summary>
	bool LastIndex(const std::string& cmd)const;

	
	std::vector<std::pair<std::string, unsigned int>>keyPair_; // <keyname, keycode>
public:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;
	~Input() = default;

	//���͓��e�̍X�V
	void Update();
	/// <summary>
	///   ���݉����Ă��邩 
	/// </summary>
	/// <param name= "cmd">�R�}���h������</param>
	/// <returns>������Ă�����true
	/// </returns>
	bool IsPressed(const char* cmd)const;

	/// <summary>
	/// �����ꂽ�u�ԂȂ̂�
	/// </summary>
	/// <param name= "cmd">�R�}���h������</param>
	/// <returns>�O�񉟂��Ă��Ęb����Ă�����true
	/// </returns>
	
	bool IsReleased(const char* cmd)const;

	// �����ꂽ�u�ԂȂ̂�
	bool IsTriggered(const char* cmd)const;
};

// ���͒ʒm���󂯎��(�C���^�[�t�F�[�X)
class InputListner
{
public:
	virtual ~InputListner() = default;
	virtual void Notify(const Input& input) = 0;
};

//bool& CurrentInput(const std::string &cmd);
