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
	// 敵の体力0以下は死んでいる
	//int life_ = 0;
	// 消えるかどうか
	bool isDeletable_ = false;
	// 現在の速度
	Vector2f velocity_;
	std::vector<Circle>circles_;
	std::shared_ptr<Stage>stage_;

	// 自分のクローンを返す
	virtual Enemy* MakeClone() = 0;
	virtual void AimPlayer();
	
public:
	Enemy(const std::shared_ptr<Player>& p, std::shared_ptr<Camera> c, std::shared_ptr<Stage> stage);
	virtual ~Enemy() = default;

	/// <summary>
	/// 攻撃を受けた
	/// </summary>
	/// <param name="damage">ダメージの値</param>
	virtual void OnDamage(int damage) = 0;

	virtual void OnDead() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <param name="pos">座標</param>
	virtual void SetPosition(const Position2f& pos);

	/// <summary>
	/// 速度取得
	/// </summary>
	/// <returns>速度</returns>
	virtual const Vector2f& GetVelocity()const;

	/// <summary>
	/// 速度設定
	/// </summary>
	/// <param name="vel">速度</param>
	virtual void SetVelocity(const Vector2f& vel);

	/// <summary>
	/// 死んでいるか
	/// </summary>
	/// <returns>true:死んだ</returns>
	virtual bool IsDead()const;

	/// <summary>
	/// 消えてよいか
	/// </summary>
	/// <returns>true:消えて良い</returns>
	virtual bool IsDeletable()const;

	/// <summary>
	/// キャラが持っている円衝突情報をすべて取得する(1キャラ)
	/// </summary>
	/// <returns></returns>
	virtual const std::vector<Circle>& GetCircles()const = 0;

	/// <summary>
	/// 何かが当たった
	/// </summary>
	/// <param name="c"></param>
	void OnHit(CollisionInfo& mine, CollisionInfo& another)override;
};

