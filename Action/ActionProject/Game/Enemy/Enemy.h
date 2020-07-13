#pragma once
#include "../Character.h"

class Player;
class Spawner;
class Enemy : public Character
{
	friend Spawner;
protected:
	const std::shared_ptr<Player>& player_;
	// �G�̗̑�0�ȉ��͎���ł���
	int life_ = 0;
	// �����邩�ǂ���
	bool isDeletable_ = false;
	// ���݂̑��x
	Vector2f velocity_;

	// �����̃N���[����Ԃ�
	virtual Enemy* MakeClone() = 0;
	virtual void AimPlayer();
public:
	Enemy(const std::shared_ptr<Player>& p);
	virtual ~Enemy() = default;

	/// <summary>
	/// �U�����󂯂�
	/// </summary>
	/// <param name="damage">�_���[�W�̒l</param>
	virtual void OnDamage(int damage) = 0;

	virtual void OnDead() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	///���W�A�N�Z�X 
	virtual const Position2f& GetPosition()const;
	virtual void SetPosition(const Vector2f& vel);

	///���x�A�N�Z�X 
	virtual const Vector2f& GetVelocity()const;
	virtual void SetVelocity(const Vector2f& vel);

	virtual bool IsDead()const;
	virtual bool IsDeletable()const;
};

