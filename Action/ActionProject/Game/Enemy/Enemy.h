#pragma once
#include "../Character.h"
#include <vector>

class Player;
class Spawner;
class Camera;
class Enemy : public Character
{
	friend Spawner;
protected:
	const std::shared_ptr<Player>& player_;
	// 敵の体力0以下は死んでいる
	int life_ = 0;
	// 消えるかどうか
	bool isDeletable_ = false;
	// 現在の速度
	Vector2f velocity_;
	std::vector<Circle>circles_;

	// 自分のクローンを返す
	virtual Enemy* MakeClone() = 0;
	virtual void AimPlayer();
	
public:
	Enemy(const std::shared_ptr<Player>& p, std::shared_ptr<Camera> c);
	virtual ~Enemy() = default;

	/// <summary>
	/// 攻撃を受けた
	/// </summary>
	/// <param name="damage">ダメージの値</param>
	virtual void OnDamage(int damage) = 0;

	virtual void OnDead() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	///座標アクセス 
	virtual void SetPosition(const Vector2f& vel);

	///速度アクセス 
	virtual const Vector2f& GetVelocity()const;
	virtual void SetVelocity(const Vector2f& vel);

	virtual bool IsDead()const;
	virtual bool IsDeletable()const;
	virtual const std::vector<Circle>& GetCircles()const = 0;

	void OnHit(CollisionInfo& c)override;
};

