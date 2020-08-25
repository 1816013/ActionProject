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
	/// 何かが当たった
	/// </summary>
	/// <param name="colInfo">衝突情報</param>
	virtual void OnHit(CollisionInfo& mine, CollisionInfo& another) = 0;

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

	/// <summary>
	/// クローンを作成
	/// </summary>
	/// <returns>クローン</returns>
	virtual Enemy* MakeClone() = 0;

	/// <summary>
	/// ボスが持っている衝突情報の円をすべて取得する
	/// </summary>
	/// <returns>衝突情報の円の配列</returns>
	virtual const std::vector<Circle>& GetCircles()const = 0;
};

