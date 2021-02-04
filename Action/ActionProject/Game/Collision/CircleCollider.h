#pragma once
#include "Collider.h"
#include "../../Geometry.h"

/// <summary>
/// �~�Փˏ��̃N���X
/// </summary>
class CircleCollider : public Collider
{
public:
	/// <summary>
	/// �~�Փˏ������(���a1,���W(0, 0) )
	/// </summary>
	/// <param name="owner">�~�Փˏ��������Ă���L�����N�^�[</param>
	/// <param name="tag">�^�O</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag = "");

	/// <summary>
	/// �~��񂩂�~�Փˏ������
	/// </summary>
	/// <param name="owner">�~�Փˏ��������Ă���L�����N�^�[</param>
	/// <param name="tag">�^�O</param>
	/// <param name="c">�~���</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Circle& c);

	/// <summary>
	/// ���S���W�Ɣ��a��񂩂�~�Փˏ������
	/// </summary>
	/// <param name="c">���S���W</param>
	/// <param name="r">���a</param>
	CircleCollider(std::shared_ptr<Character> owner, const char* tag, const Position2f& p, const float r);
	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="col">�Փˏ��</param>
	/// <returns>true:��������</returns>
	bool IsHit(std::shared_ptr<Collider> col)override;

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="c">�J����(��ʃI�t�Z�b�g�p)</param>
	void Draw(std::shared_ptr<Camera>c)override;

	/// <summary>
	/// �~�Փˏ��̉~���擾����
	/// </summary>
	/// <returns>�~�Փˏ��̉~</returns>
	const Circle& GetCircle()const;

	/// <summary>
	/// ���ۂ̍��W��Ԃ�
	/// </summary>
	/// <returns>���S���W</returns>
	const Vector2f AcutualPosition();
private:
	Circle circle_;
	

	
};

