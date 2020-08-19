#pragma once
#include "Boss.h"
#include <vector>

/// <summary>
/// 1�ʃ{�X
/// </summary>
class Ashura : public Boss
{
private:
	int ashuraH_ = -1;
	int frame_ = 0;
	using Update_t = void(Ashura::*)();
	Update_t updater_;
	using Draw_t = void (Ashura::*)();
	Draw_t drawer_;
	std::vector<Circle>circles_;

	// �X�V
	void EnteringUpdate();
	void NomalUpdate();
	void DamageUpdate();
	void ExitingUpdate();
	void DeadUpdate();

	// �`��
	void NormalDraw();
	void DamageDraw();
	void ExitingDraw();
	void DeadDraw();

	Enemy* MakeClone()override;
	const std::vector<Circle>& GetCircles()const override;

public:
	Ashura(GamePlayingScene* gs);
	~Ashura() = default;

	/// <summary>
	/// ��������������
	/// </summary>
	/// <param name="colInfo">�����蔻����</param>
	void OnHit(CollisionInfo& colInfo)override;

	/// <summary>
	/// �_���[�W���󂯂�
	/// </summary>
	/// <param name="damage">�_���[�W�l</param>
	void OnDamage(int damage)override;

	/// <summary>
	/// ����
	/// </summary>
	void OnDead()override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;
};

