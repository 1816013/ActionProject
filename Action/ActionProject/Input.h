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

	// ���݉����Ă��邩 
	/// <param name= "cmd">�R�}���h������</param>
	/// <returns>������Ă�����true
	/// </returns>
	bool IsPressed(const char* cmd)const;

	// �����ꂽ�u�ԂȂ̂�
	bool IsReleased(const char* cmd)const;

	// �����ꂽ�u�ԂȂ̂�
	bool IsTriggered(const char* cmd)const;
};

//bool& CurrentInput(const std::string &cmd);
