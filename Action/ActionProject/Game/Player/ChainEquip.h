#pragma once
#include "Equipment.h"
#include "../../Geometry.h"

class CollisionManager;
class CapsuleCollider;
/// <summary>
/// ����
/// </summary>
class ChainEquip : public Equipment
{
private:
	int frame_;
	int extensionFrame_;
	//const Player& player_;
	Vector2f direction_;
	std::shared_ptr<Player>& player_;
	CapsuleCollider* capsuleCollider_ = nullptr;
	float angle = 0.0f;
	float variationAngle = 0.0f;
	using func_t = void(ChainEquip::*)();
	func_t updater_;
	int chainH = -1;

	void NomalUpdate();
	void ExtensionUpdate();
	void SetDirection(const Input& input, const Player& player);
public:
	/// <summary>
	/// �����C���X�^���X
	/// </summary>
	/// <param name="p">�v���C���[</param>
	/// <param name="cm">�R���W�����Ǘ��p</param>
	/// <param name="c">�J����</param>
	ChainEquip(std::shared_ptr<Player>& p, std::shared_ptr<CollisionManager>cm, std::shared_ptr<Camera> c);

	/// <summary>
	/// �U��
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="input">���͏��</param>
	void Attack(const Player& player, const Input& input)override;

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

