#pragma once
#include "Enemy.h"
class GamePlayingScene;
class EffectManager;
class Boss : public Enemy
{
protected:
	GamePlayingScene* gameScene_;
	std::shared_ptr<EffectManager>effectManager_;
public:
	Boss(GamePlayingScene* gs);
	virtual ~Boss() = default;

	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="colInfo">�Փˏ��</param>
	virtual void OnHit(CollisionInfo& mine, CollisionInfo& another) = 0;

	/// <summary>
	/// �U�����󂯂�
	/// </summary>
	/// <param name="damage">�_���[�W�l</param>
	virtual void OnDamage(int damage) = 0;

	/// <summary>
	/// ����
	/// </summary>
	virtual void OnDead() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �N���[�����쐬
	/// </summary>
	/// <returns>�N���[��</returns>
	virtual Enemy* MakeClone() = 0;

	/// <summary>
	/// �{�X�������Ă���Փˏ��̉~�����ׂĎ擾����
	/// </summary>
	/// <returns>�Փˏ��̉~�̔z��</returns>
	virtual const std::vector<Circle>& GetCircles()const = 0;
};

