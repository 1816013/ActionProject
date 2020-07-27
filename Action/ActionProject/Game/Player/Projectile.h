#pragma once
#include "../Character.h"
class Camera;
class Projectile : public Character
{
protected:
	Vector2f vel_;	// 速度
	bool isActive_ = false;	// 生きているか
	std::shared_ptr<Camera> camera_;
public:
	Projectile(std::shared_ptr<Camera> c);
	virtual ~Projectile() = default;
	///<summary>
	/// 現在座標に速度を加算する
	/// </summary>
	virtual void Update()override;
	///<summary>
	/// Drawは最後の派生クラスで実装する
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 死んだかどうか
	/// </summary>
	/// <returns>true: 死んでいる false 生きている</returns>
	bool IsDead()const;
};

