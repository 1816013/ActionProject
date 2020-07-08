#pragma once
#include "Character.h"
#include <memory>
#include <vector>

// �v���C���[�N���X
class GamePlayingScene;
class Equipment;
class Player : public Character
{
private:
	std::vector<std::shared_ptr<Equipment>>equipments_;
	size_t currentEquipmentNo_ = 0;
public:
	Player(GamePlayingScene* g);
	Player();
	~Player();
	/// <summary>
	/// �����Ă��镐��ōU������
	/// </summary>
	/// <param name="input">���͎Q��</param>
	void Attack(const Input& input);
	/// <summary>
	/// �v���C���[�̍��W��ݒ肷��
	/// </summary>
	/// <param name="pos">�V���ȍ��W</param>
	void SetPosition(const Position2& pos);
	/// <summary>
	/// �v���C���[���ړ�������
	/// </summary>
	/// <param name="v">�ړ��x�N�g��</param>
	void Move(const Vector2& v);
	void NextEquip();
	void Update()override;
	void Draw()override;
	const Position2 Position()const;
	size_t CurrentEquipmentNo()const;

};

