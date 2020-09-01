#pragma once
#include "Equipment.h"

class CapsuleCollider;
class ShadowClone;
class SwordEquip :
	public Equipment
{
private:
	int frame_;
	int extensionFrame_;
	Vector2f direction_;
	std::shared_ptr<Player>& player_;
	CapsuleCollider* capsuleCollider_ = nullptr;
	float angle_ = 0.0f;
	float variationAngle = 0.0f;
	using func_t = void(SwordEquip::*)();
	ShadowClone* shadow_;
	Vector2f offset_ = Vector2f::ZERO;
	bool extensionF_ = false;
	func_t updater_;
	int chainH = -1;

	void NomalUpdate();
	/// <summary>
	/// ������L�΂����������߂�
	/// </summary>
	/// <param name="input">���͏��</param>
	/// <param name="player">�v���C���[</param>
	void SetDirection(const Input& input, const Player& player);
public:
	/// <summary>
	/// �����C���X�^���X
	/// </summary>
	/// <param name="p">�v���C���[</param>
	/// <param name="cm">�R���W�����Ǘ��p</param>
	/// <param name="c">�J����</param>
	SwordEquip(std::shared_ptr<Player>& p,
		std::shared_ptr<CollisionManager>cm,
		std::shared_ptr<Camera> c,
		ShadowClone* shadow = nullptr);

	/// <summary>
	/// �U��
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="input">���͏��</param>
	void Attack(const Player& player, const Input& input, Vector2f offset = Vector2f::ZERO)override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};

