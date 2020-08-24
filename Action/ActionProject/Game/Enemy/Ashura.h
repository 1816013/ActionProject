#pragma once
#include "Boss.h"
#include <vector>
#include <array>

class EffectManager;
/// <summary>
/// 1面ボス
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
	std::vector<Circle>circles_;	// 円衝突情報の円
	/// <summary>
	/// ボス攻撃起点
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

	// 更新
	void EnteringUpdate();
	void NomalUpdate();
	void DamageUpdate();
	void ExitingUpdate();
	void DeadUpdate();

	// 描画
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
	/// 何かが当たった
	/// </summary>
	/// <param name="colInfo">当たり判定情報</param>
	void OnHit(CollisionInfo& colInfo)override;

	/// <summary>
	/// ダメージを受けた
	/// </summary>
	/// <param name="damage">ダメージ値</param>
	void OnDamage(int damage)override;

	/// <summary>
	/// 死んだ
	/// </summary>
	void OnDead()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;
};

