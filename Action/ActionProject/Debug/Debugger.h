#pragma once

/// <summary>
/// �f�o�b�O�p�N���X(�V���O���g��)
/// </summary>
class Debugger
{
private:
	bool isDebug_;	// �f�o�b�O���[�h�p
public:
	static Debugger& Instance()
	{
		static Debugger app;
		return app;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// fps�ƕ\���I�u�W�F�N�g�̐�����ʂɕ\������
	/// </summary>
	void DisplayPerformance();

	/// <summary>
	/// �f�o�b�O���[�h��
	/// </summary>
	/// <returns>true: �f�o�b�O���[�h</returns>
	bool IsDebugMode();
};

