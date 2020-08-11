#pragma once
#include <memory>
#include "../Geometry.h"

class Player;
class Camera
{
private:
	std::shared_ptr<Player> player_;
	Position2f pos_;	// �J�����̒��S���W
	Size stageSize_;	// �X�e�[�W�̑傫��
	bool isLocked = false;
public:
	Camera();
	void SetPlayer(std::shared_ptr<Player> player);
	
	/// <summary>
	/// �X�e�[�W�̌��E�T�C�Y���Z�b�g����
	/// </summary>
	/// <param name="size">�X�e�[�W�S�̂̃T�C�Y</param>
	void SetStageSize(const Size& size);
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �J�����̌��ݍ��W��Ԃ�
	/// </summary>
	/// <returns>�J�����̌��ݍ��W</returns>
	const Position2f& GetPosition()const;

	/// <summary>
	/// �J�����̎B�e�͈͂�Ԃ�
	/// </summary>
	/// <returns>�J�����̎B�e�͈�</returns>
	const Rect GetViewRange()const;
	
	/// <summary>
	/// �J�����̌��ݍ��W��Ԃ�
	/// </summary>
	/// <returns>�J�����̌��ݍ��W</returns>
	const Vector2f ViewOffset()const;

	/// <summary>
	/// �X�N���[�����~�߂邩�ǂ�����Ԃ�
	/// </summary>
	/// <returns>true:��~</returns>
	bool Lock();
};

