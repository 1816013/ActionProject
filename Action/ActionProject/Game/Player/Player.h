#pragma once
#include "../Character.h"
#include <memory>
#include <vector>

// �v���C���[�N���X
class GamePlayingScene;
class Equipment;
class CollisionManager;
class Player : public Character
{
private:
	std::vector<std::shared_ptr<Equipment>>equipments_;
	size_t currentEquipmentNo_ = 0;
	Direction direction_;
	std::shared_ptr<CollisionManager>collisionManager_;
public:
	Player(GamePlayingScene* g);
	Player() = default;
	~Player();
	/// <summary>
	/// �����Ă��镐��ōU������
	/// </summary>
	/// <param name="input">���͎Q��</param>
	void Attack(const Input& input);
	void ExtendAttack(const Input& input);
	/// <summary>
	/// �v���C���[�̍��W��ݒ肷��
	/// </summary>
	/// <param name="pos">�V���ȍ��W</param>
	void SetPosition(const Position2f& pos);
	/// <summary>
	/// �v���C���[���ړ�������
	/// </summary>
	/// <param name="v">�ړ��x�N�g��</param>
	void Move(const Vector2f& v);
	void NextEquip();
	void Update()override;
	void Draw()override;
	//const Position2f Position()const;
	size_t CurrentEquipmentNo()const;
	Direction Direction()const;

	void OnHit(CollisionInfo& c);
};

