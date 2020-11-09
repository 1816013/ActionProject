#pragma once
#include "Equipment.h"

class FanCollider;
class ShadowClone;
class SwordEquip :
	public Equipment
{
private:
	int frame_;
	std::shared_ptr<Player>& player_;
	FanCollider* fanCollider_ = nullptr;
	using func_t = void(SwordEquip::*)();
	ShadowClone* shadow_;
	Vector2f offset_ = Vector2f::ZERO;
	func_t updater_;
	SlashShape slash_;
	bool isRight_;

	void NomalUpdate();
public:
	/// <summary>
	/// ���C���X�^���X
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

