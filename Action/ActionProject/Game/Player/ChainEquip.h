#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class Player;
class CollisionManager;
class CapsuleCollider;
class ShadowClone;
/// <summary>
/// ����
/// </summary>
class ChainEquip : public Equipment
{
private:
	int frame_;
	int extensionFrame_;
	Vector2f direction_;
	std::shared_ptr<Player>& player_;
	CapsuleCollider* capsuleCollider_ = nullptr;
	float angle_ = 0.0f;
	float variationAngle = 0.0f;
	using func_t = void(ChainEquip::*)();
	ShadowClone* shadow_;
	Vector2f offset_ = Vector2f::ZERO;
	bool extensionF_ = false;
	func_t updater_;
	int chainH = -1;


	void NomalUpdate();
	void ExtensionUpdate();
	/// <summary>
	/// ������L�΂����������߂�
	/// </summary>
	/// <param name="input">���͏��</param>
	/// <param name="player">�v���C���[</param>
	void SetDirection(const Input& input, const Player& player);
	/// <summary>
	/// ���݂̃t���[�����獽���̒������擾����
	/// </summary>
	/// <returns>�����̒���</returns>
	int ExpandWidth();
public:
	/// <summary>
	/// �����C���X�^���X
	/// </summary>
	/// <param name="p">�v���C���[</param>
	/// <param name="cm">�R���W�����Ǘ��p</param>
	/// <param name="c">�J����</param>
	ChainEquip(std::shared_ptr<Player>& p,
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
	/// �ǉ��U��
	/// �U�����ɐL�т�������ŏ��̍U���ƕʃx�N�g���ɃL�[����ꂽ��ǉ��U��
	/// ������U���
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="input">���͏��</param>
	void ExtensionAttack(const Player& player, const Input& input)override;
	
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
};

