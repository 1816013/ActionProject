#pragma once
#include "Collider.h"
#include "../../Geometry.h"
class FanCollider :
	public Collider
{
private:
	FanShape fanShape_;
	bool isAttack_;
public:
	FanCollider(std::shared_ptr<Character> owner, const char* tag = "", bool immortal = false);
	/// <summary>
	/// ��`�̏Փˏ������
	/// </summary>
	/// <param name="owner">�Փˏ���ێ����Ă���L�����N�^�[</param>
	/// <param name="cap">��`���</param>
	/// <param name="tag">�^�O</param>
	/// <param name="immortal">�s�����ǂ���</param>
	FanCollider(std::shared_ptr<Character> owner, const FanShape& fan, const char* tag = "", bool immortal = false);
	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="col">�R���C�_�[</param>
	/// <returns>true:��������</returns>
	bool IsHit(std::shared_ptr<Collider> col)override;

	/// <summary>
	/// �f�o�b�O�`��
	/// �J�����͍��W�̃I�t�Z�b�g���擾���邽��
	/// </summary>
	/// <param name="c">�J����</param>
	void Draw(std::shared_ptr<Camera>c)override;

	/// <summary>
	/// ���ۂ̍��W��Ԃ�
	/// </summary>
	/// <returns>���S���W</returns>
	const Vector2f AcutualPosition();

	/// <summary>
	/// �O���炢�����悤�ɎQ�Ƃ�Ԃ�
	/// </summary>
	/// <returns>�Փˏ��̐�`�̎Q��</returns>
	/// <example></example>
	FanShape& GetFanShape();

	/// <summary>
	/// �U�������ǂ���
	/// </summary>
	/// <returns></returns>
	void SetIsAttack(bool isAttack);
};

