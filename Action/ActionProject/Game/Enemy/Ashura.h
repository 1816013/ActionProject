#pragma once
#include "Boss.h"
#include <vector>
#include <array>

class EffectManager;
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
	std::vector<Circle>circles_;	// �~�Փˏ��̉~
	/// <summary>
	/// �{�X�U���N�_
	/// </summary>
	struct EnergyBall
	{
		Vector2f pos;
		int frame;
		EnergyBall(Vector2f pos) : pos(pos), frame(0) {};
	};
	std::array<EnergyBall, 4>energyBalls_ = {
		EnergyBall({-128.0f, -420.0f}),
		EnergyBall({128, -420}),
		EnergyBall({-100, -300}),
		EnergyBall({100, -300}) };

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

