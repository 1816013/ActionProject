#pragma once
#include "../Character.h"
#include <vector>

class Player;
class Spawner;
class Camera;
class Stage;
class Enemy : public Character
{
	friend Spawner;
protected:
	const std::shared_ptr<Player>& player_;
	// �G�̗̑�0�ȉ��͎���ł���
	//int life_ = 0;
	// �����邩�ǂ���
	bool isDeletable_ = false;
	// ���݂̑��x
	Vector2f velocity_;
	std::vector<Circle>circles_;
	std::shared_ptr<Stage>stage_;

	// �����̃N���[����Ԃ�
	virtual Enemy* MakeClone() = 0;
	virtual void AimPlayer();
	
public:
	Enemy(const std::shared_ptr<Player>& p, std::shared_ptr<Camera> c, std::shared_ptr<Stage> stage);
	virtual ~Enemy() = default;

	/// <summary>
	/// �U�����󂯂�
	/// </summary>
	/// <param name="damage">�_���[�W�̒l</param>
	virtual void OnDamage(int damage) = 0;

	virtual void OnDead() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// ���W�擾
	/// </summary>
	/// <param name="pos">���W</param>
	virtual void SetPosition(const Position2f& pos);

	/// <summary>
	/// ���x�擾
	/// </summary>
	/// <returns>���x</returns>
	virtual const Vector2f& GetVelocity()const;

	/// <summary>
	/// ���x�ݒ�
	/// </summary>
	/// <param name="vel">���x</param>
	virtual void SetVelocity(const Vector2f& vel);

	/// <summary>
	/// ����ł��邩
	/// </summary>
	/// <returns>true:����</returns>
	virtual bool IsDead()const;

	/// <summary>
	/// �����Ă悢��
	/// </summary>
	/// <returns>true:�����ėǂ�</returns>
	virtual bool IsDeletable()const;

	/// <summary>
	/// �L�����������Ă���~�Փˏ������ׂĎ擾����(1�L����)
	/// </summary>
	/// <returns></returns>
	virtual const std::vector<Circle>& GetCircles()const = 0;

	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="c"></param>
	void OnHit(CollisionInfo& mine, CollisionInfo& another)override;
};

