#pragma once
#include "Collider.h"
#include "../../Geometry.h"
class CapsuleCollider : public Collider
{
private:
	Capsule capsule_;
public:
	CapsuleCollider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	/// <summary>
	/// �J�v�Z����̏Փˏ������
	/// </summary>
	/// <param name="owner">�Փˏ���ێ����Ă���L�����N�^�[</param>
	/// <param name="cap">�J�v�Z�����</param>
	/// <param name="tag">�^�O</param>
	/// <param name="immortal">�s�����ǂ���</param>
	CapsuleCollider(std::shared_ptr<Character> owner, const Capsule& cap,  const char* tag = "", bool immortal = false);
	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="col">�R���C�_�[</param>
	/// <returns>true:��������</returns>
	bool IsHit(std::shared_ptr<Collider> col)override;

	/// <summary>
	/// �`��
	/// �J�����͍��W�̃I�t�Z�b�g���擾���邽��
	/// </summary>
	/// <param name="c">�J����</param>
	void Draw(std::shared_ptr<Camera>c)override;
	/// <summary>
	/// ���ۂ̍��W��Ԃ�
	/// </summary>
	/// <returns>�N�_���W</returns>
	const Vector2f AcutualPosition();

	/// <summary>
	/// �O���炢�����悤�ɎQ�Ƃ�Ԃ�
	/// </summary>
	/// <returns>�J�v�Z���̎Q��</returns>
	/// <example></example>
	Capsule& GetCapsule();
};

