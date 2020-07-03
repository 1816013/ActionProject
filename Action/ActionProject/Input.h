#pragma once
class Input
{
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
