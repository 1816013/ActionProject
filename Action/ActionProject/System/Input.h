#pragma once
#include <vector>
#include <utility>
#include <string>
#include <array>
#include <unordered_map>

constexpr int inputRecordSize = 2;	// ���̓o�b�t�@�i�[��

enum class PeripheralType
{
	keyboard,
	gamepad
};

struct PeripheralInfo
{
	PeripheralType type;
	int index;
};

using PeripheralReferenceTable_t = std::unordered_map<std::string, std::vector<PeripheralInfo>>;
class KeyConfigScene;
class Input
{
friend KeyConfigScene;
private:
	//PeripheralReferenceTable_t peripheralReferenceTable_;
	int currentInputIndex = 0;	// ���݂̓��̓o�b�t�@���w���C���f�b�N�X
	using InputStateTable_t = std::unordered_map<std::string, bool>;
	std::array <InputStateTable_t, inputRecordSize>_inputStateTable;	// ���͊i�[�e�[�u��
	mutable bool isRawMode_ = false;	// �����[�h
	mutable std::vector<char> rawKeyState_;	// ���L�[�{�[�h���
	mutable int rawPadState_;	//���p�b�h�X�e�[�g(1�R���̂�)
	mutable PeripheralReferenceTable_t peripheralReferenceTable_;///�O�����炢�����p

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

	/// <summary>
	/// �C�x���g�ɑΉ�����@����͂�o�^����
	/// </summary>
	/// <param name="eventname">���̓C�x���g�̖��O</param>
	/// <param name="peri">���͏��</param>
	void RegistAcceptPeripheral(const char* eventname, const std::vector<PeripheralInfo>& peri);
	bool CheckPressed(const char* eventname, const char* keystate = 0, int padstate = 0);
	
	
	/// <summary>
	/// ���L�[�{�[�h�����擾����
	/// ���b�N���͒��g����
	/// </summary>
	/// <returns>���L�[�{�[�h���z��</returns>
	const std::vector<char>& GetRawKeyboardState()const;

	/// <summary>
	/// ���p�b�h�����擾
	/// ��񂾂�
	/// </summary>
	/// <returns>���p�b�h���</returns>
	const int GetRawPadState()const;

	/// <summary>
	/// �����[�h���A�����b�N����
	/// ���L�[�{�[�h�A���p�b�h��񂪕ێ�����Q�Ƃł���悤�ɂȂ�
	/// </summary>
	void UnLockRawMode()const;

	/// <summary>
	/// �����[�h�����b�N����
	/// ���̃��[�h�Ő��f�[�^�ɃA�N�Z�X���悤�Ƃ���ƃA�T�[�V�������N����
	/// </summary>
	void LockRawMode()const;

	void SetPeripheralReferenceTable(const PeripheralReferenceTable_t& prt)const;
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
