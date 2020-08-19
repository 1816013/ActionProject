#pragma once
#include "Enemy.h"
class GamePlayingScene;
class Boss : public Enemy
{
protected:
	GamePlayingScene* gameScene_;
public:
	Boss(GamePlayingScene* gs);
	virtual ~Boss() = default;
	virtual void OnHit(CollisionInfo& colInfo) = 0;

	/// <summary>
	/// 攻撃を受けた
	/// </summary>
	/// <param name="damage">ダメージ値</param>
	virtual void OnDamage(int damage) = 0;

	/// <summary>
	/// 死んだ
	/// </summary>
	virtual void OnDead() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;

	virtual Enemy* MakeClone() = 0;

	virtual const std::vector<Circle>& GetCircles()const = 0;
};

